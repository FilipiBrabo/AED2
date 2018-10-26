#include <stdio.h>
#include "rb_tree.h"

extern Node* NIL_PTR;

int main() {

    Node* root = NIL_PTR;

    tree_insert(&root, 5);
    tree_insert(&root, 2);
    Node *x = tree_insert(&root, 15);
    tree_insert(&root, 9);
    tree_insert(&root, 18);
    tree_insert(&root, 20);
    tree_insert(&root, 16);

    print_rb_tree_erd(&root);

    Node *y = find_parent(&root, x);
    printf("%d\n", x->key);
    //printf("Pai de x%d\n", y->key);
    left_rotate(&root, x);

    printf("\n\nARVORE ROTACIONADA\n");

    print_rb_tree_erd(&root);
    printf("\n");
    return 0;
}