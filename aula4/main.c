#include <stdio.h>
#include "rb_tree.h"

extern Node* NIL_PTR;

int main() {

    Node* root = NIL_PTR;

    tree_insert(&root, 5);
    tree_insert(&root, 2);
    Node *x = tree_insert(&root, 7);
    tree_insert(&root, 6);
    tree_insert(&root, 8);

    left_rotate(&root, x);

    print_rb_tree_erd(&root);
    printf("\n");
    return 0;
}