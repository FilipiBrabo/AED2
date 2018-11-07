#include <stdio.h>
#include "rb_tree.h"

extern Node* NIL_PTR;
void print_test(Node **T);

int main() {

    Node* root = NULL;
    int key;
    while (scanf("%d", &key) != 0) {
        tree_insert(&root, key);
    }

    print_test(&root);
   
    left_rotate(&root, root->right);

    printf("\n\nARVORE ROTACIONADA\n");
    print_test(&root);

    printf("\n");
    return 0;
}


void print_test(Node **T) {
    if (*T == NULL)
        return;

    printf("%p <-- %d -- %p  --> %p\n", (*T)->left, (*T)->key, (*T), (*T)->right);
    print_rb_tree_erd(&(*T)->left);
    print_rb_tree_erd(&(*T)->right);    
}
