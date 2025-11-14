#include "dump.h"


ak_errors edges(const node_t* node, FILE* fp)
{
    assert(node != NULL);
    assert(fp != NULL);

    if (node->left != NULL)
    {
        create_edge(node, node->left, fp);
        edges(node->left, fp);
    }

    if (node->right != NULL)
    {
        create_edge(node, node->right, fp);
        edges(node->right, fp);
    }
    
    return OK;
}

ak_errors create_edge(const node_t* node1, const node_t* node2, FILE* fp)
{
    assert(node1 != NULL);
    assert(node2 != NULL);
    assert(fp != NULL);

    fprintf(fp, "n%p->n%p[color=\"green\"]\n", node1, node2);

    return OK;
}

ak_errors blocks(const node_t* node, FILE* fp)
{
    assert(node != NULL);
    assert(fp != NULL);

    if (node->left != NULL)
        blocks(node->left, fp);

    create_block(node, fp);
    
    if (node->right != NULL)
        blocks(node->right, fp);

    return OK;
}

ak_errors create_block(const node_t* node, FILE*  fp)
{
    assert(node != NULL);
    assert(fp != NULL);


    fprintf(fp, "n%p [shape=Mrecord, label =\"{pointer = %p | %s |{ left = %p | right = %p }}\", style=filled, fontcolor=\"black\", fillcolor=\"white\"];\n",
                     node, node, node->answer, node->left, node->right);
    return OK;
}

ak_errors create_file (FILE* fp, const node_t* node)
{
    assert(fp);
    assert(node);
    fprintf(fp, "digraph G {\n"
                "splines=ortho\n"
                "node [style=filled, fillcolor=red, fontcolor=white, shape=octagon]\n"
            );
    blocks(node ,fp);
    edges(node, fp);
    
    fprintf(fp, "}\n");
    return OK;
}

ak_errors graph_dump(const tree_t* tree)
{
    printf("tree size is %lu\n", tree->size);

    FILE* fp = open_file("graph.dot");
    create_file(fp, tree->root);
    fclose(fp);

    system_graph();
    return OK;
}

FILE* open_file(const char* file_name)
{
    FILE* fp = fopen(file_name, "w");
    assert(fp != 0);
    return fp;
}

ak_errors system_graph()
{
    system("mkdir -p /mnt/c/Users/boris/projects/Akinator/photo");
    static size_t file_number = 0;
    char str[STRSIZE] = {};
    sprintf(str, "dot graph.dot -T png -o /mnt/c/Users/boris/projects/Akinator/photo/graph%lu.png", file_number);
    system(str);
    file_number++;
    printf("graph set\n");
    return OK;
}

void create_html(char* new_answer, char* question)
{
    FILE* fp = fopen("ak_dump.html", "a");
    static size_t file_number = 0;
    fprintf(fp, "<pre>\n");
    
    if (new_answer == NULL || question == NULL)
        fprintf(fp, "Start tree\n");
    else
        fprintf(fp, "Tree after insert %s with new question %s?\n", new_answer, question);

    
    char path[70] = {};

    sprintf(path, "/mnt/c/Users/boris/projects/Akinator/photo/graph%lu.png", file_number);    
    fprintf(fp, "<img src=\" %s \">\n\n\n", path);
    
    file_number++;
    fclose(fp);
}

void free_file(const char* name)
{
    FILE* fp = fopen(name, "w");
    fclose(fp);
}