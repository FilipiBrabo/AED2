#include "rb_tree.h"

/* Valor de sentinela, indica que chegamos em alguma folha ou entao
 a raiz da arvore */
Node NIL_NODE;

/* Ponteiro para o valor de sentinela */
Node *NIL_PTR = &NIL_NODE;

/** Funcao auxiliar que cria um novo Node, alocando memoria,
* para um valor de chave passado como parametro.
* Note que os valores dos ponteiros left/right/parent sao
* mantidos como NULL
*
* Parametros:
* key: a chave para o novo Node
*
* Devolve:
* Um novo Node em caso de sucesso, NULL caso nao consiga alocar
* a memoria para o novo Node
*/
Node* new_node(int key) {
    Node *ret_val = (Node*) malloc(sizeof(Node));
    if(NULL == ret_val) return NULL;
    ret_val->key = key;
    ret_val->color = RED;
    ret_val->left = NULL;
    ret_val->right = NULL;
    ret_val->parent = NULL;
    return ret_val;
}

/**
* A funcao abaixo insere uma nova chave em uma arvore RB
* sem realizar o balanceamento.
*
* Parametros:
* T: aponta para a raiz da arvore onde devemos inserir a chave
* key: valor da nova chave
*
* Devolve:
* O novo Node inserido em caso de sucesso, NULL caso nao
* seja possivel inserir o novo valor
*/
Node* tree_insert(Node** T, int key){
    Node *new = NULL;

    if (*T == NULL) {                
        *T = new_node(key);
        return *T;
    }

    if (key > (*T)->key) {
        if ((*T)->right == NULL) {
            new = new_node(key);
            (*T)->right = new;
            //atualiza o pai
            new->parent = *T;
        
        } else {        
            new = tree_insert(&((*T)->right), key);
        }
    } else if (key < (*T)->key){
        if ((*T)->left == NULL) {
            Node *new = new_node(key);
            (*T)->left = new;
            //atualiza o pai
            new->parent = *T;
        
        } else {
            new = tree_insert(&((*T)->left), key);
        }
    }

    return new;    
}

void rb_insert(Node** T, int key) {
    Node *z = new_node(key);
    Node *y = NULL;
    Node *x = *T;

    while (x != NULL) {
        y = x;
        if (z->key < y->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    
    z->parent = y;
    
    if (y == NULL) {
        *T = z;
    } else {
        if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }
    }

    z->left = NULL;
    z->right = NULL;
    z->color = RED;
    
    rb_insert_fixup(T, z);
}

void rb_insert_fixup(Node **T, Node *z) {
    while (z->parent != NULL && z->parent->color == RED 
            && z->parent->parent != NULL) {
        
        Node *pai = z->parent;
        Node *avo = pai->parent;
        
        if (pai == avo->left) {
            Node *y = avo->right;
            
            if (y->color == RED) { //Tio de z é vermelho
                pai->color = BLACK;
                y->color = BLACK;
                avo->color = RED;            
            
            } else {
                if (z == pai->right) {
                    z = pai;
                    left_rotate(T, z);
                }
                
                pai->color = BLACK;
                avo->color = RED;
                right_rotate(T, avo);            }
        
        } else {           
            Node *y = avo->left;
            
            if (y->color == RED) { //Tio de z é vermelho
                pai->color = BLACK;
                y->color = BLACK;
                avo->color = RED;
            
            } else {
                if (z == pai->left) {
                    z = pai;
                    right_rotate(T, z);
                }
                
                pai->color = BLACK;
                avo->color = RED;
                left_rotate(T, avo);
            }
        } 
    }
}

/**
* Realiza uma rotacao simples para a esquerda
*
* Parametros:
* T: aponta para a raiz da arvore onde a rotacao sera realizada
* x: Node pertencente a arvore em torno do qual faremos a rotacao
*
*/
void left_rotate(Node** T, Node* x) {
    
    // Y is the right child of x
    Node *y = x->right;   
    x->right = y->left;
    y->left = x;

    printf("%d", x->parent->key);   
    // Se o pai de X é a raiz
    if (x->parent == NULL)
        *T = y;
    
    // Se X é o filho direito do seu pai    
    else if (x->parent->right == x) {
        x->parent->right = y;
        y->parent = x->parent->right;
        x->parent = y;

    //Se X é o filho esquerdo do seu pai
    } else {
        x->parent->left = y;
        y->parent = x->parent->left;
        x->parent = y;
    }
}

/**
* Realiza uma rotacao simples para a direita
*
* Parametros:
* T: aponta para a raiz da arvore onde a rotacao sera realizada
* x: Node pertencente a arvore em torno do qual faremos a rotacao
*
*/
void right_rotate(Node** T, Node* x) {
     // Y is the left child of x
    Node *y = x->left;   
    x->left = y->right;
    y->right = x;

    printf("%d", x->parent->key);   
    // Se o pai de X é a raiz
    if (x->parent == NULL)
        *T = y;
    
    // Se X é o filho esquerdo do seu pai    
    else if (x->parent->left == x) {
        x->parent->left = y;
        y->parent = x->parent->left;
        x->parent = y;

    //Se X é o filho esquerdo do seu pai
    } else {
        x->parent->right = y;
        y->parent = x->parent->right;
        x->parent = y;
    }
}


/**
* Realiza a troca de cor em alguns nos, caso esses satisfacam
* algumas condicoes.
*
* Parametros:
* T: aponta para a raiz da arvore onde a rotacao sera realizada
* x: Node pertencente a arvore em torno do qual faremos a rotacao
*
*/
void flip_color(Node** T, Node* z) {
    if (*T == NULL) return; // Checa se existe arvore
    if (z == NULL) return; // Checa se existe no z

    Node *pai = z->parent;
    Node *avo = pai != NULL ? pai->parent : NULL;
    if (avo == NULL) return; // Checa se existe avo
    Node *tio = avo->left == pai ? avo->right : avo->left;
    if (tio == NULL) return; // Checa se existe tio

    if (z->color == RED && pai->color == RED 
        && tio->color == RED && avo->color == BLACK) {
            tio->color = BLACK;
            pai->color = BLACK;
            avo->color = RED;
    }
}

void print_rb_tree_erd(Node **T) {
    if (*T == NULL)
        return;
            
    print_rb_tree_erd(&(*T)->left);
    printf("%d ", (*T)->key);
    print_rb_tree_erd(&(*T)->right);    
}
