#include "akinator_func.h"
#include "dump.h"
#include "file_work.h"

int main()
{
    tree_t ak = {};
    ak_creator(&ak);
    
    char* ptr = tree_read(&ak, "KHL.txt");

    tree_fprint(ak, "test.txt");

    ak_destructor(ak.root);
    free(ptr);
    return OK;
}

