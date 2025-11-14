#include "akinator_func.h"
#include "dump.h"
#include "file_work.h"
#include "supportive_func.h"

ak_errors ak_creator(tree_t* ak)
{   
    ak->canary_l = CANARY_L;
    ak->canary_r = CANARY_R;
    ak->size = 0;
    ak->root = (node_t*) calloc(1, sizeof(node_t));
    ak->root->answer = (char*) calloc(50, sizeof(char));
    
    strcat(ak->root->answer, "It is unknown who?");

    free_file("ak_dump.html");
    create_html(0, 0);
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

    if (root->hold != 0)
        free(root->answer);
    free(root);

    return OK;
}

ak_errors ak_find(tree_t* ak)
{
    stack_t ret = {};
    stack_creator(&ret, STACK_SIZE);
    stack_push(&ret, ak->root);
    node_find(ak->root, &ret);

    stack_destructor(&ret);
    graph_dump(ak);
    return OK;
}

ak_errors ak_dump()
{

    return OK;
}

ak_errors node_find(node_t* node, stack_t* ret)
{
    stack_push(ret, node);
    printf("%s\n", node->answer);
    char c = (char) getchar();
    buffer_cleaner();
    while (c != 'y' && c != 'n')
    {
        printf("Try again\n");
        c = (char) getchar();
        buffer_cleaner();
    }
    
    if (c == 'y')
        if (node->left == NULL)
            printf(CYAN "I'm the best\n\n" RESET);
        else 
            node_find(node->left, ret);
    else
        if (node->right == NULL)
        {
            node_insert(node);
        }
        else
            node_find(node->right, ret);

    return OK;
}

ak_errors node_insert(node_t* node)
{
    node_t* left_leaf = (node_t*) calloc(1, sizeof(node_t));
    printf("What is it?\n");
    get_str(&(left_leaf->answer)); 
    left_leaf->hold = 1;
    ON_DEBUG(printf("answer is %s\n", left_leaf->answer);)
    //buffer_cleaner();
    printf("What is the difference between" GREEN " %s " RESET "and " RED "%s" RESET ", he (enter the difference without not)\n", left_leaf->answer, node->answer);
    node_t* right_leaf = (node_t*) calloc(1, sizeof(node_t));  
    
    char* question = NULL;
    get_str(&question);
    node->hold = 1;
    //buffer_cleaner();

    right_leaf->answer = node->answer;
    node->answer = question;
    node->right = right_leaf;
    node->left = left_leaf;

    printf("I will be better((\n\n");
    create_html(left_leaf->answer, question);
    return OK;
}


void buffer_cleaner()
{   
    while(getchar() != '\n');
    //printf("Please try again.\n");
}

ak_errors tree_definition(tree_t tree)
{
    printf(BLUE "Enter node name\n" RESET);
    stack_t ret = {};
    char* name = 0;
    stack_creator(&ret, STACK_SIZE);

    get_str(&name);

    if (node_definition(name, tree.root, &ret) != OK)
        printf("No such node\n");

    else 
    {
        printf("Definition\n");
        node_describe(&ret);
    }

    free(name);
    stack_destructor(&ret);
    return OK;
}


ak_errors node_definition(char* name, node_t* node, stack_t* ret)
{
    path* path1 = (path*) calloc (1, sizeof(path));

    if (!strcmp(name, node->answer))
    {
        path1->node = node;
        path1->c = '\0';
        stack_push(ret, path1);
        ON_DEBUG(printf(MAGENTA "FIND NODE\n" RESET);) 

        return OK;
    }

    if (node->left != 0)
    {
        if (node_definition(name, node->left, ret) == OK)
        {       
            path1->node = node;
            path1->c = 'y';
            stack_push(ret, path1);
            ON_DEBUG(printf("stack size in poisk\n");)
            return OK;
        }
    }

    if (node->right != 0)
    {
        if (node_definition(name, node->right, ret) == OK)
        {
            path1->node = node;
            path1->c = 'n';
            stack_push(ret, path1);
            ON_DEBUG(printf("stack size in poisk %ld\n", ret->size);)
            return OK;    
        }
    }
    free(path1);
    return ERROR;
}

ak_errors node_describe(stack_t* ret)
{
    if (!ret)
        return ERROR;
    path* pth = 0;
    for (; ret->size > 0;)
    {
        ON_DEBUG(printf("stack size is %ld\n", ret->size);)
        stack_pop(ret, (void**) &pth);
        if (pth->c == 'y')
            printf("Is %s\n", pth->node->answer);

        else if (pth->c == 'n')
            printf("Isn't %s", pth->node->answer);

        else if (pth->c == '\0')
            printf("%s\n" "End definition\n", pth->node->answer);

        ON_DEBUG(printf("free %s\n", pth->node->answer);)
        free(pth);
    }
    return OK;
}

void get_str(char** string)
{
    size_t number = 0;
    ssize_t n_to_o = getline(string, &number, stdin);
    (*string)[n_to_o - 1] = '\0';
}

ak_errors tree_difference(tree_t akinator)
{
    printf(BLUE "Enter first node name\n" RESET);
    stack_t ret1 = {};
    char* first = 0;
    stack_creator(&ret1, STACK_SIZE);
    get_str(&first);

    printf(BLUE "Enter second node name\n" RESET);
    stack_t ret2 = {};
    char* second = 0;
    stack_creator(&ret2, STACK_SIZE);
    get_str(&second);

    if (node_definition(first, akinator.root, &ret1) != OK)
        printf("No first node in tree\n");

    else if (node_definition(second, akinator.root, &ret2) != OK)
        printf("No second node in tree\n");

    else
        get_difference(&ret1, first, &ret2, second);
    

        
    stack_destructor(&ret1);
    stack_destructor(&ret2);
    free(first);
    free(second);

    return OK;
}


// ak_errors get_difference(stack_t* ret1, char* name1,  stack_t* ret2, char* name2)
// {
//     assert(ret1);
//     assert(ret2);
//     assert(name1);
//     assert(name2);

//     path* first = 0;
//     path* second = 0;
//     bool dif = false;
//     for (; ret1->size > 0 || ret2->size > 0;)
//     {
//         if (ret1->size > 0)
//             stack_pop(ret1, (void**) &first);
//         else
//             first = 0;

//         if (ret2->size > 0)
//             stack_pop(ret2, (void**) &second);
//         else
//             second = 0;
        
//         if (first != NULL && second != NULL)
//         {
//             if (first->node == second->node && !dif)
//             {
//                 if (first->c == second->c)
//                 {
//                     if (first->c == 'y')
//                         printf("%s and %s are %s\n", name1, name2, first->node->answer);
//                     else
//                         printf("%s and %s aren't %s\n", name1, name2, first->node->answer);
//                 }
//                 else
//                 {   if (first->c == 'y')
//                         printf("%s is %s, but %s isn't\n", name1, first->node->answer, name2);
//                     else
//                         printf("%s is %s, but %s isn't\n", name2, first->node->answer, name1);
//                 }
//             }
//         }
//     }

//     return OK;
// }

ak_errors get_difference(stack_t* ret1, char* name1,  stack_t* ret2, char* name2)
{
    assert(ret1); assert(ret2);
    assert(name1); assert(name2);

    path* inf1 = 0;
    path* inf2 = 0;
    while (ret1->size > 0 && ret2->size > 0)
    {
        stack_pop(ret1, (void**) &inf1);
        stack_pop(ret2, (void**) &inf2);
        if (print_dif(name1, inf1, name2, inf2) == true)
            break;
    }

    clean_stack(ret1);
    clean_stack(ret2);

    return OK;
}

bool print_dif(char* name1, path* info1, char* name2, path* info2)
{
    if (info1->node == info2->node)
    {
        if (info1->c == info2->c)
        {
            printf("%s and %s answer %s \"%c\"\n", name1, name2, info1->node->answer, info1->c);
            free(info1);
            free(info2);
        }
        else
        {
            printf("%s answer \"%s\" %c, but %s answer %c\n", name1, info1->node->answer, info1->c, name2, info2->c);
            free(info1);
            free(info2);
            return true;
        }
    }
    else
        printf(RED "different nodes\n" RESET);

    return false;
}

void clean_stack(stack_t* stack)
{
    assert(stack);
    void* ptr  = 0;
    while(stack->size > 0)
    {
        stack_pop(stack, &ptr);
        free(ptr);
    }
}



