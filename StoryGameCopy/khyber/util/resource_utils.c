//
// Created by kkyse on 12/9/2017.
//

#include "resource_utils.h"

#include <assert.h>
#include <errno.h>

bool check_error(const int error, const int id) {
    if (id == -1 && errno == error) {
        return true;
    } else {
        assert(id != -1);
        return false;
    }
}

bool check_eexists(const int id) {
    return check_error(EEXIST, id);
}

bool check_enoent(const int id) {
    return check_error(ENOENT, id);
}
