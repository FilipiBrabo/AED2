#include <stdio.h>
#include "rb_tree.h"

#define R    "\x1b[31m"
#define W    "\x1b[0m"

extern Node* NIL_PTR;
void print_test(Node **T);

int main() {

    Node* root = NULL;
    int key;
    while (scanf("%d", &key) != EOF) {
        rb_insert(&root, key);
        //print_test(&root);
    }

    print_test(&root);
    printf("\n");
    printf("%d\n", rb_black_height(root));
    printf("\n");
    return 0;
}


void print_test(Node **T) {
    if (*T == NULL)
        return;
    Node *x = *T;
    printf("%s%d"W" <-- %s%d"W"(%s%p"W")  --> %s%d"W"  :: pai = %s%d"W"\n", 
            x->left   == NULL ? "" : (x->left->color == RED ? R : W), 
            x->left   == NULL ? -9999 : x->left->key, 
            x->color  == RED  ? R     : "", x->key,
            x->color  == RED  ? R     : "", x,
            x->right  == NULL ? ""    : (x->right->color == RED ? R : W),
            x->right  == NULL ? -9999 : x->right->key, 
            x->parent == NULL ? ""    : (x->parent->color == RED ? R : W),
            x->parent == NULL ? -9999 : x->parent->key
            );
            
    print_test(&(*T)->left);
    print_test(&(*T)->right);    
}
