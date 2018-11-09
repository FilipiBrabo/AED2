#include <stdio.h>
#include "rb_tree.h"

extern Node* NIL_PTR;
void print_test(Node **T);

int main() {

    Node* root = NIL_PTR;
    
    int key;
    while (scanf("%d", &key) != EOF) {
        rb_insert(&root, key);
        //print_test(&root);
    }
    
    printf("RB TREE ERD:\n");
    print_rb_tree_erd(&root);
    //print_test(&root);
    printf("\n\n");
    printf("RB TREE BLACK HEIGHT: %d\n", rb_black_height(root));
    printf("RB TREE HEIGHT: %d\n", rb_height(root));
    return 0;
}

// Imprime todos os nós da árvore com seus filhos e pai, e suas cores
void print_test(Node **T) {
    if (*T == NIL_PTR)
        return;
    Node *x = *T;
    printf("%s%d"W" <-- %s%d"W"(%s%p"W")  --> %s%d"W"  // parent: %s%d"W"\n", 
            x->left   == NIL_PTR ? "" : (x->left->color == RED ? R : W), 
            x->left   == NIL_PTR ? -9999 : x->left->key, 
            x->color  == RED  ? R     : "", x->key,
            x->color  == RED  ? R     : "", x,
            x->right  == NIL_PTR ? ""    : (x->right->color == RED ? R : W),
            x->right  == NIL_PTR ? -9999 : x->right->key, 
            x->parent == NIL_PTR ? ""    : (x->parent->color == RED ? R : W),
            x->parent == NIL_PTR ? -9999 : x->parent->key
            );
            
    print_test(&(*T)->left);
    print_test(&(*T)->right);    
}
