//
// Created by kkyse on 9/15/2017.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define NUM_PROBLEMS 599

typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned long long ull;

typedef long long answer_t;

typedef answer_t (*const SolutionFunc)();

typedef struct Solution {
    const SolutionFunc solution;
    const uint num;
    const char *const name;
} Solution;

typedef struct Euler {
    uint num_solutions;
    Solution *const solutions;
} Euler;

Euler *new_euler() {
    Euler local_euler = {0, (Solution *) malloc(sizeof(Solution) * NUM_PROBLEMS)};
    Euler *euler = (Euler *) malloc(sizeof(Euler));
    memcpy(euler, &local_euler, sizeof(Euler));
    return euler;
}

void free_euler(Euler *const euler) {
    free(euler->solutions);
    free(euler);
}

void register_solution(Euler *const euler, const uint problem_num, const SolutionFunc solution_func,
                       const char *const name) {
    if (euler->num_solutions == NUM_PROBLEMS) {
        printf("too many solutions");
        exit(1);
    }
    const Solution solution = {solution_func, problem_num, name};
    memcpy(euler->solutions + euler->num_solutions++, &solution, sizeof(Solution));
}

static inline int solution_cmp(const Solution *const s1, const Solution *const s2) {
    return s1->num - s2->num;
}

/*
 * FIXME
 * I was planning on sorting the solutions based on their problem number,
 * but qsort messes up the function pointers somehow and causes seg faults.
 */
void sort_solutions(Euler *const euler) {
    qsort(euler->solutions, sizeof(Solution), euler->num_solutions, (const void *) solution_cmp);
}

char *answer_to_string(answer_t answer) {
    const uint buffer_len = 20;
    char *s = (char *) malloc(buffer_len * sizeof(char));
    if (answer < 0) {
        strcpy(s, "unfinished or wrong");
    } else {
        sprintf(s, "%llu", answer);
    }
    return s;
}

static inline double elapsed(clock_t start) {
    return (clock() - start) / (double) CLOCKS_PER_SEC;
}

void run_solutions(Euler *const euler) {
    //sort_solutions(Euler);
    const uint num_solutions = euler->num_solutions;
    clock_t total_start = clock();
    for (uint i = 0; i < num_solutions; i++) {
        Solution solution = euler->solutions[i];
        clock_t start = clock();
        const answer_t answer = solution.solution();
        double time = elapsed(start);
        const char *const answer_str = answer_to_string(answer);
        printf("Euler #%u: %s: %s (%f sec)\n", solution.num, solution.name, answer_str, time);
        free((char *) answer_str);
    }
    double total_time = elapsed(total_start);
    printf("\n%u Euler solutions (%f sec)\n", num_solutions, total_time);
}

// Multiples of 3 and 5
answer_t euler1() {
    const uint MAX = 1000;
    uint sum = 0;
    for (uint i = 0; i < MAX; i++) {
        if (i % 3 == 0 || i % 5 == 0) {
            sum += i;
        }
    }
    return sum;
}

// Even Fibonacci Numbers
answer_t euler2() {
    const uint MAX = 10000000;
    uint sum = 0;
    uint a = 0;
    uint b = 1;
    uint temp;
    while (a < MAX) {
        if ((a & 1) == 0) {
            sum += a;
        }
        temp = a;
        a = b;
        b += temp;
    }
    return sum;
}

// Largest Prime Factor
answer_t euler3() {
    ull n = 600851475143ULL;
    for (ull i = 2ULL; i < n; i++) {
        while (n % i == 0) {
            n /= i;
        }
    }
    return n;
}

static inline bool is_palindrome(uint i) {
    uint temp = i;
    uint reversed = 0;
    while (temp) {
        reversed = 10 * reversed + (temp % 10);
        temp /= 10;
    }
    return reversed == i;
}

int largest_palindrome_product(uint min, uint max) {
    uint answer = 0;
    for (uint i = max; i >= min; i--) {
        for (uint j = max; j >= min; j--) {
            const uint p = i * j;
            //printf("%d\n", p);
            if (p > answer && is_palindrome(p)) {
                answer = p;
            }
        }
    }
    return answer == 0 ? -1 : (int) answer;
}

// Largest Palindrome Product
answer_t euler4() {
    return largest_palindrome_product(100, 999);
}

static inline bool all_divisible(uint i) {
    const uint divisible_up_to = 20;
    for (uint j = 1; j <= divisible_up_to; ++j) {
        if (i % j) {
            return false;
        }
    }
    return true;
}

// very slow, TODO optimize
// Smallest Multiple
answer_t euler5_slow() {
    for (uint i = 1;; ++i) {
        if (all_divisible(i)) {
            return i;
        }
    }
}

uint gcd(uint a, uint b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    int shift = __builtin_ctz(a | b);
    a >>= shift;
    b >>= shift;
    a >>= __builtin_ctz(a);
    do {
        b >>= __builtin_ctz(b);
        if (a > b) {
            a ^= b;
            b ^= a;
            a ^= b;
        }
        b -= a;
    } while (b != 0);
    return a << shift;
    // normal Euclid GCD algorithm, about 3x slower than
    // above binary GCD algorithm with CTZ instruction
//    uint c;
//    while (a != 0) {
//        c = a;
//        a = b % a;
//        b = c;
//    }
//    return b;
}

uint lcm(const uint a, const uint b) {
    return a / gcd(a, b) * b;
}

// optimized
// Smallest Multiple
answer_t euler5() {
    const uint divisible_up_to = 20; //20000000; // 20 mil takes 1 sec
    uint all_lcm = 1;
    for (uint i = 1; i < divisible_up_to; ++i) {
        all_lcm = lcm(i, all_lcm);
    }
    return all_lcm;
}

static inline uint sum_squares(uint n) {
    return (n * (n + 1) * ((n << 1) + 1)) / 6;
}

static inline uint square_sums(uint n) {
    const uint sum = (n * (n + 1)) >> 1;
    return sum * sum;
}

// Sum Square Difference
answer_t euler6() {
    const uint n = 100;
    return square_sums(n) - sum_squares(n);
}

// TODO finish
// 10001st Prime
answer_t euler7() {
    const uint n = 10001;
    uint i;
    uint prime;
    for (prime = 3, i = 0; i <= n; ++i, prime += 2) {
    
    }
    
    return -1;
}

ull parse_ull(const char *bits, const uint from, const uint to) {
    ull n = 0;
    for (uint i = from; i < to; ++i) {
        n = n * 10 + bits[i];
    }
    return n;
}

// Largest Product in a Series
answer_t euler8() {
    const char *num_str = ""
            "73167176531330624919225119674426574742355349194934"
            "96983520312774506326239578318016984801869478851843"
            "85861560789112949495459501737958331952853208805511"
            "12540698747158523863050715693290963295227443043557"
            "66896648950445244523161731856403098711121722383113"
            "62229893423380308135336276614282806444486645238749"
            "30358907296290491560440772390713810515859307960866"
            "70172427121883998797908792274921901699720888093776"
            "65727333001053367881220235421809751254540594752243"
            "52584907711670556013604839586446706324415722155397"
            "53697817977846174064955149290862569321978468622482"
            "83972241375657056057490261407972968652414535100474"
            "82166370484403199890008895243450658541227588666881"
            "16427171479924442928230863465674813919123162824586"
            "17866458359124566529476545682848912883142607690042"
            "24219022671055626321111109370544217506941658960408"
            "07198403850962455444362981230987879927244284909188"
            "84580156166097919133875499200524063689912560717606"
            "05886116467109405077541002256983155200055935729725"
            "71636269561882670428252483600823257530420752963450";
    const uint num_adjacent = 13;
    const uint num_digits = (uint) strlen(num_str);
    char *const num = (char *) malloc(num_digits * sizeof(char));
    for (uint i = 0; i < num_digits; ++i) {
        num[i] = num_str[i] - (char) '0';
    }
    
    // could keep running product and divide last and multiply new digit
    // but then have to deal with zeroes
    // since the number isn't that long, this is simpler
    ull max = 0;
    for (uint i = 0; i < num_digits - num_adjacent; ++i) {
        ull n = 1;
        for (uint j = 0; j < num_adjacent; ++j) {
            n *= num[i + j];
        }
        if (n > max) {
            max = n;
        }
    }
    
    return max;
}

// Special Pythagorean Triplet
answer_t euler9() {
    const uint SUM = 1000;
    const uint MAX_MN = 100;
    for (uint n = 1; n < MAX_MN; ++n) {
        for (uint m = n + 1; m < MAX_MN; ++m) {
            const uint mm = m * m;
            const uint nn = n * n;
            const uint a = mm - nn;
            const uint b = (m * n) << 1;
            const uint c = mm + nn;
            if (a + b + c == SUM) {
                //printf("%u, %u\n", n, m);
                //printf("%u, %u, %u\n", a, b, c);
                return a * b * c;
            }
        }
    }
    return -1;
}

// TODO finish
// Summation of Primes
answer_t euler10() {
    return -1;
}

typedef enum Month {
    January = 1, February, March, April, May, June, July, August, September, October, November, December
} Month;

typedef enum DayOfWeek {
    Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday
} DayOfWeek;

static inline DayOfWeek day_of_week(const byte d, const Month m, uint y) {
    y -= m < 3;
    return (DayOfWeek) ((y + y / 4 - y / 100 + y / 400 + "-bed=pen+mad."[m] + d) % 7);
}

typedef struct Date {
    const byte day;
    const byte month;
    const uint year;
} Date;

uint num_sundays_on_first_of_month(Date start, Date end) {
    uint num_sundays = 0;
    for (uint year = start.year; year < end.year; ++year) {
        for (Month month = January; month < December; ++month) {
            if (day_of_week(1, month, year) == Sunday) {
                num_sundays++;
            }
        }
    }
    return num_sundays;
}

// Large Sum
answer_t euler13() {
    const uint num_nums = 100;
    const uint num_digits = 50;
    const char *num_strings[] = {
            "37107287533902102798797998220837590246510135740250",
            "46376937677490009712648124896970078050417018260538",
            "74324986199524741059474233309513058123726617309629",
            "91942213363574161572522430563301811072406154908250",
            "23067588207539346171171980310421047513778063246676",
            "89261670696623633820136378418383684178734361726757",
            "28112879812849979408065481931592621691275889832738",
            "44274228917432520321923589422876796487670272189318",
            "47451445736001306439091167216856844588711603153276",
            "70386486105843025439939619828917593665686757934951",
            "62176457141856560629502157223196586755079324193331",
            "64906352462741904929101432445813822663347944758178",
            "92575867718337217661963751590579239728245598838407",
            "58203565325359399008402633568948830189458628227828",
            "80181199384826282014278194139940567587151170094390",
            "35398664372827112653829987240784473053190104293586",
            "86515506006295864861532075273371959191420517255829",
            "71693888707715466499115593487603532921714970056938",
            "54370070576826684624621495650076471787294438377604",
            "53282654108756828443191190634694037855217779295145",
            "36123272525000296071075082563815656710885258350721",
            "45876576172410976447339110607218265236877223636045",
            "17423706905851860660448207621209813287860733969412",
            "81142660418086830619328460811191061556940512689692",
            "51934325451728388641918047049293215058642563049483",
            "62467221648435076201727918039944693004732956340691",
            "15732444386908125794514089057706229429197107928209",
            "55037687525678773091862540744969844508330393682126",
            "18336384825330154686196124348767681297534375946515",
            "80386287592878490201521685554828717201219257766954",
            "78182833757993103614740356856449095527097864797581",
            "16726320100436897842553539920931837441497806860984",
            "48403098129077791799088218795327364475675590848030",
            "87086987551392711854517078544161852424320693150332",
            "59959406895756536782107074926966537676326235447210",
            "69793950679652694742597709739166693763042633987085",
            "41052684708299085211399427365734116182760315001271",
            "65378607361501080857009149939512557028198746004375",
            "35829035317434717326932123578154982629742552737307",
            "94953759765105305946966067683156574377167401875275",
            "88902802571733229619176668713819931811048770190271",
            "25267680276078003013678680992525463401061632866526",
            "36270218540497705585629946580636237993140746255962",
            "24074486908231174977792365466257246923322810917141",
            "91430288197103288597806669760892938638285025333403",
            "34413065578016127815921815005561868836468420090470",
            "23053081172816430487623791969842487255036638784583",
            "11487696932154902810424020138335124462181441773470",
            "63783299490636259666498587618221225225512486764533",
            "67720186971698544312419572409913959008952310058822",
            "95548255300263520781532296796249481641953868218774",
            "76085327132285723110424803456124867697064507995236",
            "37774242535411291684276865538926205024910326572967",
            "23701913275725675285653248258265463092207058596522",
            "29798860272258331913126375147341994889534765745501",
            "18495701454879288984856827726077713721403798879715",
            "38298203783031473527721580348144513491373226651381",
            "34829543829199918180278916522431027392251122869539",
            "40957953066405232632538044100059654939159879593635",
            "29746152185502371307642255121183693803580388584903",
            "41698116222072977186158236678424689157993532961922",
            "62467957194401269043877107275048102390895523597457",
            "23189706772547915061505504953922979530901129967519",
            "86188088225875314529584099251203829009407770775672",
            "11306739708304724483816533873502340845647058077308",
            "82959174767140363198008187129011875491310547126581",
            "97623331044818386269515456334926366572897563400500",
            "42846280183517070527831839425882145521227251250327",
            "55121603546981200581762165212827652751691296897789",
            "32238195734329339946437501907836945765883352399886",
            "75506164965184775180738168837861091527357929701337",
            "62177842752192623401942399639168044983993173312731",
            "32924185707147349566916674687634660915035914677504",
            "99518671430235219628894890102423325116913619626622",
            "73267460800591547471830798392868535206946944540724",
            "76841822524674417161514036427982273348055556214818",
            "97142617910342598647204516893989422179826088076852",
            "87783646182799346313767754307809363333018982642090",
            "10848802521674670883215120185883543223812876952786",
            "71329612474782464538636993009049310363619763878039",
            "62184073572399794223406235393808339651327408011116",
            "66627891981488087797941876876144230030984490851411",
            "60661826293682836764744779239180335110989069790714",
            "85786944089552990653640447425576083659976645795096",
            "66024396409905389607120198219976047599490197230297",
            "64913982680032973156037120041377903785566085089252",
            "16730939319872750275468906903707539413042652315011",
            "94809377245048795150954100921645863754710598436791",
            "78639167021187492431995700641917969777599028300699",
            "15368713711936614952811305876380278410754449733078",
            "40789923115535562561142322423255033685442488917353",
            "44889911501440648020369068063960672322193204149535",
            "41503128880339536053299340368006977710650566631954",
            "81234880673210146739058568557934581403627822703280",
            "82616570773948327592232845941706525094512325230608",
            "22918802058777319719839450180888072429661980811197",
            "77158542502016545090413245809786882778948721859617",
            "72107838435069186155435662884062257473692284509516",
            "20849603980134001723930671666823555245252804609722",
            "53503534226472524250874054075591789781264330331690",
    };
    double *const nums = (double *const) malloc(num_nums * sizeof(double));
    for (uint i = 0; i < num_nums; ++i) {
        nums[i] = strtod(num_strings[i], NULL);
    }
    double sum = 0;
    for (uint i = 0; i < num_nums; ++i) {
        sum += nums[i];
    }
    const uint num_first_digits = 10;
    char *const first_digits = (char *const) malloc((num_first_digits + 1) * sizeof(char));
    snprintf(first_digits, num_first_digits + 1, "%.11f", sum);
    return strtoll(first_digits, NULL, 10);
}

uint collatz_chain_length(uint *const restrict cache, const uint cache_size, const uint n);

static inline uint collatz_chain_length_direct(uint *const restrict cache, const uint cache_size, const uint n) {
    if (n == 1) {
        return 1;
    }
    const uint next_num = (n & 1) == 1 ? n + (n << 1) + 1 : n >> 1;
    return collatz_chain_length(cache, cache_size, next_num) + 1;
}

uint collatz_chain_length(uint *const restrict cache, const uint cache_size, const uint n) {
    if (n >= cache_size) {
        return collatz_chain_length_direct(cache, cache_size, n);
    }
    //printf("%u\n", n);
    if (cache[n] == 0) {
        cache[n] = collatz_chain_length_direct(cache, cache_size, n);
    }
    return cache[n];
}

// Longest Collatz Sequence
answer_t euler14() {
    const uint MAX = 1000000;
    const uint cache_size = MAX;
    uint *const cache = (uint *const) calloc(cache_size, sizeof(uint));
    uint max_chain_length = 1;
    uint max_starting_num = 1;
    for (uint i = 1; i < MAX; ++i) {
        //printf("\t%u\n", i);
        const uint chain_length = collatz_chain_length(cache, cache_size, i);
        if (chain_length > max_chain_length) {
            max_chain_length = chain_length;
            max_starting_num = i;
        }
    }
    return max_starting_num;
}

// Counting Sundays
answer_t euler19() {
    Date start = {1, January, 1901};
    Date end = {31, December, 2000};
    return num_sundays_on_first_of_month(start, end);
}

static inline double integral(double x) {
    const double t = x - 1;
    return t - 0.5 * (t * sqrt(1 - t * t) + asin(t));
}

// Concave Triangle
answer_t euler587() {
    const double L_section_area = 1 - M_PI / 4;
    const double inv_L_section_area = 1 / L_section_area;
    const double c = 1;
    const double integral1 = integral(1);
    for (uint i = 1;; ++i) {
        const double slope = 1.0 / i;
        const double a = slope * slope + 1;
        const double b = -2 * (slope + 1);
        const double x = (2 * c) / (-b + sqrt(b * b - 4 * a * c)); // reciprocal quadratic formula
        const double concave_triangle_area = 0.5 * x * (1 - sqrt((-x + 2) * x)) + integral1 - integral(x);
        if (concave_triangle_area * inv_L_section_area < 0.001) {
            return i;
        }
    }
}

#define EULER(n, name) register_solution(euler, n, euler##n, name)

void register_solutions(Euler *const euler) {
    EULER(1, "Multiples of 3 and 5");
    EULER(2, "Even Fibonacci Numbers");
    EULER(3, "Largest Prime Factor");
    EULER(4, "Largest Palindrome Product");
    EULER(5, "Smallest Multiple");
    EULER(6, "Sum Square Difference");
    EULER(7, "10001st Prime");
    EULER(8, "Largest Product in a Series");
    EULER(9, "Special Pythagorean Triplet");
    EULER(10, "Summation of Primes");
    
    EULER(13, "Large Sum");
    EULER(14, "Longest Collatz Sequence");
    
    EULER(19, "Counting Sundays");
    
    EULER(587, "Concave Triangle");
}

int main() {
    Euler *const euler = new_euler();
    register_solutions(euler);
    run_solutions(euler);
    free_euler(euler);
    printf("\nall done\n");
    return 0;
}