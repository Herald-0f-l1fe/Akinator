#ifndef LIBS
#define LIBS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../common/COLORS.h"
#define DEBUG
#include "../common/DEBUG.h"
#include <assert.h>

struct  node_t
{
    char* answer;
    node_t* left;
    node_t* right;
};


struct  tree_t
{
    int canary_l;
    node_t* root;
    size_t size;
    int canary_r;
};

enum ak_errors
{
    OK = 0,
    ERROR = 1,
    CANARY_DIED,
    NO_VALID_SIZE,
    NO_ROOT,
};

#define CANARY_L 0xB055
#define CANARY_R 0xDEAD

#endif
