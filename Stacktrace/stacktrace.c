//
// Created by kkyse on 10/23/2017.
//

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <w32api/winnt.h>
#include <w32api/dbghelp.h>
#include <w32api/processthreadsapi.h>
#include <stdbool.h>

#ifdef _WIN32
    #include <windows.h>
    #include <imagehlp.h>
#endif

#ifdef __linux__
    #include <err.h>
    #include <execinfo.h>
#endif

#define arraylen(array) (sizeof(array) / sizeof(*(array)))

extern const char *global_program_name;

struct string {
    char *ptr;
    size_t size;
};

#define PTR_MAX_STRLEN ((sizeof(addr) * 8) / 4)

#ifdef __APPLE__
    #define addr2line_base "atos -o %s %p"
#else
    #define addr2line_base "addr2line -f -p -e %s %p"
#endif

#define addr2line_cmd_len(program_name_len) \
    (arraylen(addr2line_base) - arraylen("%s%p") + PTR_MAX_STRLEN + (program_name_len))

struct string addr2line_cmd = {0};

int addr2line(const char *const program_name, const void *const addr) {
    const size_t program_name_length = strlen(program_name);
    if (addr2line_cmd.size < addr2line_cmd_len(program_name_length)) {
        addr2line_cmd.size = addr2line_cmd_len(program_name_length);
        addr2line_cmd.ptr = (char *) realloc(addr2line_cmd.ptr, addr2line_cmd_len(program_name_length) * sizeof(char));
    }
    sprintf(addr2line_cmd.ptr, addr2line_base, program_name, addr);
    return system(addr2line_cmd.ptr);
}

int backtrace(void **buffer, int size);

char **backtrace_symbols(void *const *buffer, int size);

#define MAX_STACK_FRAMES 64

static void *stack_traces[MAX_STACK_FRAMES];

void posix_print_stack_trace() {
    const int trace_size = backtrace(stack_traces, MAX_STACK_FRAMES);
    const char **const messages = (const char **) backtrace_symbols(stack_traces, trace_size);
    for (uint i = 0; i < trace_size; ++i) {
        if (addr2line(global_program_name, stack_traces[i]) != 0) {
            fprintf(stderr, "\tstackTrace determining line # for: %s\n", messages[i]);
        }
    }
    free(messages);
}

#define print_signal(signal, message) fputs("Caught "#signal": "#message"\n", stderr); break

#define catch_signal(signal, message) case signal: print_signal(signal, message)
#define catch_sub(signal, subsignal, message) \
    case subsignal: fputs("Caught "#signal" ("#subsignal"): "#message"\n", stderr); break;
#define catch_FPE(subsignal, message) catch_sub(SIGFPE, subsignal, message)
#define catch_ILL(subsignal, message) catch_sub(SIGILL, subsignal, message)

void posix_signal_handler(const int signal, const siginfo_t *const siginfo, const void *const context) {
    switch (signal) {
        catch_signal(SIGSEGV, "Segmentation Fault");
        catch_signal(SIGINT, "Interrupt: Interactive attention signal, usually (Ctrl+C)");
        catch_signal(SIGTERM, "Termination: a termination request was sent to the program");
        catch_signal(SIGABRT, "Abort: usually caused by an abort() or assert()");
        case SIGFPE:
            switch (siginfo->si_code) {
                catch_FPE(FPE_INTDIV, "integer divide by zero");
                catch_FPE(FPE_INTOVF, "integer overflow");
                catch_FPE(FPE_FLTDIV, "floating-point divide by zero");
                catch_FPE(FPE_FLTUND, "floating-point overflow");
                catch_FPE(FPE_FLTRES, "floating-point underflow");
                catch_FPE(FPE_FLTINV, "floating-point inexact result");
                catch_FPE(FPE_FLTSUB, "subscript out of range");
                default:
                print_signal(SIGFPE, "Arithmetic Exception");
            }
            break;
        case SIGILL:
            switch (siginfo->si_code) {
                catch_ILL(ILL_ILLOPC, "illegal opcode");
                catch_ILL(ILL_ILLOPN, "illegal operand");
                catch_ILL(ILL_ILLADR, "illegal addressing mode");
                catch_ILL(ILL_ILLTRP, "illegal trap");
                catch_ILL(ILL_PRVOPC, "privileged opcode");
                catch_ILL(ILL_PRVREG, "privileged register");
                catch_ILL(ILL_COPROC, "coprocessor stackTrace");
                catch_ILL(ILL_BADSTK, "internal stack stackTrace");
                default:
                print_signal(SIGILL, "Illegal Instruction");
            }
            break;
        default:
            break;
    }
    posix_print_stack_trace();
    _Exit(1);
}

#undef catch_ILL
#undef catch_FPE
#undef catch_sub
#undef catch_signal
#undef print_signal

void windows_print_stack_trace(CONTEXT *context) {
    SymInitialize(GetCurrentProcess(), NULL, true);
    STACKFRAME frame = {0};
    
    // setup initial stack frame
    frame.AddrPC.Offset = context->Eip;
    frame.AddrPC.Mode = AddrModeFlat;
    frame.AddrStack.Offset = context->Esp;
    frame.AddrStack.Mode = AddrModeFlat;
    frame.AddrFrame.Offset = context->Ebp;
    frame.AddrFrame.Mode = AddrModeFlat;
    
    while (StackWalk(IMAGE_FILE_MACHINE_I386, GetCurrentProcess(), GetCurrentThread(), &frame, context, 0,
                     SymFunctionTableAccess, SymGetModuleBase, 0)) {
        addr2line(global_program_name, (void *) frame.AddrPC.Offset);
    }
    
    SymCleanup(GetCurrentProcess());
}

#define print_exception(exception) fputs("Error: "#exception"\n", stderr); break
#define catch_exception(exception) case exception: print_exception(exception)

LONG WINAPI windows_exception_handler(const EXCEPTION_POINTERS *const ExceptionInfo) {
    switch (ExceptionInfo->ExceptionRecord->ExceptionCode) {
        catch_exception(EXCEPTION_ACCESS_VIOLATION);
        catch_exception(EXCEPTION_ARRAY_BOUNDS_EXCEEDED);
        default:
            print_exception(Unrecognized Exception);
    }
    fflush(stderr);
    
    // If this is a stack overflow then we can't walk the stack, so just show where the stackTrace happened
    if (ExceptionInfo->ExceptionRecord->ExceptionCode != EXCEPTION_STACK_OVERFLOW) {
        windows_print_stack_trace(ExceptionInfo->ContextRecord);
    } else {
        addr2line(global_program_name, (void *) ExceptionInfo->ContextRecord->Eip);
    }
    
    return EXCEPTION_EXECUTE_HANDLER;
}