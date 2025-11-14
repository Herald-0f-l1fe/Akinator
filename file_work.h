#ifndef FILE_WORK
#define FILE_WORK

#include "libs.h"
#include "../Onegin/read_from_file_to_buffer.h"
#include "supportive_func.h"


char* read_from_file_to_buffer(long int* size, const char* str);
long int finding_file_size(const char* str);
char* filling_the_buffer_with_text(long int size, FILE* fp);
ak_errors node_fprint(node_t* node, FILE* fp);
ak_errors tree_fprint(tree_t ak, const char* file_name);
char* tree_read (tree_t* ak, const char* file_name);
char* get_name(char** cur_pos);
node_t* node_read(char** cur_pos);
void skip_spaces(char** cur_pos);

#endif