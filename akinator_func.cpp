#include "akinator_func.h"

ak_errors ak_creator(tree_t* ak)
{   
    ak->canary_l = CANARY_L;
    ak->canary_r = CANARY_R;
    ak->size = 0;
    ak->root = (node_t*) calloc(1, sizeof(node_t));
    ak->root->answer = (char*) calloc(50, sizeof(char));
    strcat(ak->root->answer, "It is unknown who?");
    if (ak->canary_l != CANARY_L || ak->canary_r != CANARY_R)
        return CANARY_DIED;
    if (ak->size != 0)
        return NO_VALID_SIZE;
    if (ak->root == nullptr)
        return NO_ROOT;
    
    return OK;
}

ak_errors ak_destructor(node_t* root)
{
    assert(root);
    if (root->left != NULL)
        ak_destructor(root->left);

    if (root->right != NULL)
        ak_destructor(root->right);
    
    free(root->answer);
    free(root);

    return OK;
}

ak_errors ak_find(tree_t* ak)
{

}

ak_errors ak_dump()
{
    
}