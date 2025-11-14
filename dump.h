#ifndef DUMP
#define DUMP

#include "libs.h"
#include "supportive_func.h"

ak_errors edges(const node_t* node, FILE* fp);
ak_errors create_edge(const node_t* node1, const node_t* node2, FILE* fp);
ak_errors blocks(const node_t* node, FILE* fp);
ak_errors create_block(const node_t* node, FILE*  fp);
ak_errors create_file (FILE* fp, const node_t* node);
ak_errors graph_dump(const tree_t* tree);
ak_errors system_graph();
void create_html(char* new_answer, char* question);
void free_file(const char* name);

#endif