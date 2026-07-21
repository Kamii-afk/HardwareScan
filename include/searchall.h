#ifndef SEARCHALL_H
#define SEARCHALL_H

#include "check.h"

typedef enum {
    SEARCH_NAME,
    SEARCH_SN,
    SEARCH_CPU,
    SEARCH_GPU
}searchTypes;

int searchAll(const char *value, searchTypes type);

#endif