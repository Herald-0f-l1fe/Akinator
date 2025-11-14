#ifndef FUNC
#define FUNC

#include "libs.h"

ak_errors ak_creator(tree_t* ak);
ak_errors ak_destructor(node_t* root);


ak_errors ak_find(tree_t* ak);
ak_errors node_find(node_t* node_ptr, stack_t* ret);
ak_errors node_insert(node_t* node_ptr);
ak_errors ak_dump();
ak_errors node_describe(stack_t* ret);
ak_errors node_definition(char* name, node_t* node, stack_t* ret);
ak_errors tree_definition(tree_t tree);
ak_errors get_difference(stack_t* ret1, char* name1,  stack_t* ret2, char* name2);
ak_errors tree_difference(tree_t akinator);


void clean_stack(stack_t* stack);
bool print_dif(char* name1, path* info1, char* name2, path* info2);

#endif