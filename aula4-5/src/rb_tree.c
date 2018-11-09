#include "rb_tree.h"

/* Valor de sentinela, indica que chegamos em alguma folha ou entao
 a raiz da arvore */
Node NIL_NODE;

/* Ponteiro para o valor de sentinela */
Node *NIL_PTR = &NIL_NODE;

/** Funcao auxiliar que cria um novo Node, alocando memoria,
* para um valor de chave passado como parametro.
* Note que os valores dos ponteiros left/right/parent sao
* mantidos como NIL_PTR
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
    ret_val->left = NIL_PTR;
    ret_val->right = NIL_PTR;
    ret_val->parent = NIL_PTR;
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
    if (*T == NIL_PTR) {                
        *T = new_node(key);
        return *T;
    }
    
    Node *new = NIL_PTR;

    if (key > (*T)->key) {
        if ((*T)->right == NIL_PTR) {
            new = new_node(key);
            (*T)->right = new;
            //atualiza o pai
            new->parent = *T;
        
        } else {        
            new = tree_insert(&((*T)->right), key);
        }
    } else if (key < (*T)->key){
        if ((*T)->left == NIL_PTR) {
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
    Node *y = NIL_PTR;
    Node *x = *T;
    
    while (x != NIL_PTR) {
        y = x;
        if (z->key < y->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    
    z->parent = y;
    
    if (y == NIL_PTR) {
        *T = z;
        
    } else {
        if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }
    }
    
    rb_insert_fixup(T, z);
}

void rb_insert_fixup(Node **T, Node *z) {
    while (par(z) != NIL_PTR && par(z)->color == RED 
            && gpar(z) != NIL_PTR) {
        if (par(z) == gpar(z)->left) {

            Node *y = gpar(z)->right;
            
            if (y != NIL_PTR && y->color == RED) { //Tio de z é vermelho
                par(z)->color = BLACK;
                y->color = BLACK;
                gpar(z)->color = RED;
                z = gpar(z);

            } else {
                if (z == par(z)->right) {
                    z = par(z);
                    left_rotate(T, z);
                }
                
                par(z)->color = BLACK;
                gpar(z)->color = RED;
                right_rotate(T, gpar(z));          
            }
        
        } else {
           
            Node *y = gpar(z)->left;
            
            if (y != NIL_PTR && y->color == RED) { //Tio de z é vermelho
                par(z)->color = BLACK;
                y->color = BLACK;
                gpar(z)->color = RED;
                z = gpar(z);
            
            } else {
                if (z == par(z)->left) {
                    z = par(z);
                    right_rotate(T, z);
                }
                
                par(z)->color = BLACK;
                gpar(z)->color = RED;
                left_rotate(T, gpar(z));
            }
        } 
    }
    
    (*T)->color = BLACK;
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
    y->parent = x->parent;
    if (x->right != NIL_PTR)
        x->right->parent = x;
    
    // Se o X é a raiz
    if (x->parent == NIL_PTR) {
        *T = y;
        x->parent = y;
    
    // Se X é o filho direito do seu pai    
    } else if (x->parent->right == x) {
        x->parent->right = y;
        x->parent = y;

    //Se X é o filho esquerdo do seu pai
    } else {
        x->parent->left = y;
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
    y->parent = x->parent;
    if (x-> left != NIL_PTR)
        x->left->parent = x;

    // Se X é a raiz
    if (x->parent == NIL_PTR) {
        *T = y;
        x->parent = y;
    }
    
    // Se X é o filho esquerdo do seu pai    
    else if (x->parent->left == x) {
        x->parent->left = y;
        x->parent = y;

    //Se X é o filho esquerdo do seu pai
    } else {
        x->parent->right = y;
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
    if (*T == NIL_PTR) return; // Checa se existe arvore
    if (z == NIL_PTR) return; // Checa se existe no z

    Node *pai = z->parent;
    Node *avo = pai != NIL_PTR ? pai->parent : NIL_PTR;
    if (avo == NIL_PTR) return; // Checa se existe avo
    Node *tio = avo->left == pai ? avo->right : avo->left;
    if (tio == NIL_PTR) return; // Checa se existe tio

    if (z->color == RED && pai->color == RED 
        && tio->color == RED && avo->color == BLACK) {
            tio->color = BLACK;
            pai->color = BLACK;
            avo->color = RED;
    }
}

// Imprime a árvore na ordem erd com as cores vermelha e branca (que representa o preto)
void print_rb_tree_erd(Node **T) {
    if (*T == NIL_PTR)
        return;
            
    print_rb_tree_erd(&(*T)->left);
    printf("%s%d "W"", (*T)->color == RED ? R : W, (*T)->key);
    print_rb_tree_erd(&(*T)->right);    
}

// Retorna a altura negra de um nó(contagem de todos os nós pretos até um nó folha)
int rb_black_height(Node *T) {
    if (T == NIL_PTR || T == NULL) return -1;
    
    if (T->color == RED) {
        return rb_black_height(T->left);
    }
    return rb_black_height(T->left) + 1;
}

int max(int a, int b) {
    return a > b ? a : b;
}

// Calcula a altura do nó
int rb_height(Node *T) {
    if (T == NIL_PTR || T == NULL) return -1;
    
    return max(rb_height(T->left), rb_height(T->right)) + 1;
}
