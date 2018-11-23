#ifndef __BT_BTREE_H__
#define  __BT_BTREE_H__

#include <stdlib.h>
#include <stdbool.h>

/** Representa um no (celula) de uma arvore B */
typedef struct bt_node {
    /* Cada chave e representada por um numero inteiro
    `keys' guarda a sequencia de chaves para um determinado no */
    int *keys;

    /* `children' guarda a sequencia de filhos de um determinado no */
    struct bt_node** children;

    /* sinaliza se este no e uma folha ou nao */
    bool is_leaf; 

    /* numero atual de chaves armazenadas */
    int num_keys; 

    /* parametro que determina a capacidade de um no;
    cada no pode ter ate (2*t - 1) chaves e ate 
    2*t filhos*/
    int t; 
} bt_node;

/** Representa uma arvore B */
typedef struct bt_tree {
    /* no raiz da arvore */
    bt_node *root;
    /* parametro de capacidade dos nos da arvore */
    int t;
} bt_tree;

/* Cria uma nova arvore, incialmente vazia. 
Entrada:
t: parametro de capacidade dos nos da arvore.
Devolve: ponteiro para a arvore recem criada.
*/
bt_tree* new_tree(int t);

/* Cria um novo no.
Entrada:
t: parametro de capacidade do no.
is_leaf: determina se o novo no sera uma folha ou nao.
Devolve: novo no.
*/
bt_node* bt_new_node(int t, bool is_leaf);

/* Busca o no que contem determinada chave.
Entrada:
T: arvore onde sera feita a busca
key: chave para busca
Devolve: o no que contem a chave caso ele exista, NULL caso a chave nao seja encontrada.
*/
bt_node* search(bt_tree *T, int key);

/* Insere uma nova chave na arvore
Entrada:
T: arvore onde a chave sera inserida.
key: nova chave a ser inserida
Devolve: 0 em caso de sucesso, outro valor caso nao seja possivel inserir a chave
*/
int bt_insert(bt_tree* T, int key);

/* Insere uma nova chave em um no que ainda nao esteja completo.
Entrada: 
N: um no ainda nao completo, abaixo do qual sera inserida a nova chave.
    A insercao nao ocorrera necessariamente em N, a chave pode ser inserida
    em alguma folha que seja descendente de N
key: a chave a ser inserida
Devolve: 0 em caso de sucesso, outro valor caso nao seja possivel inserir a chave.
*/ 
int bt_insert_non_full(bt_node* N, int key);

/* Realiza a cisao de um no (celula) da arvore.
Entrada:
parent: no pai do no que sera particionado
index: indice do no `child' que sera particionado em relacao a sequencia 
    de filhos de `parent'.
child: no a ser particionado em dois.
Devolve: 0 em caso de sucesso, outro valor caso nao seja particionar o no.

Ao final dessa funcao, o no `child' tera sido particionado em dois. No inicio
da funcao, o no `child' deve estar completo (2*t - 1 chaves). As (t-1) chaves
superiores de `child' serao copiadas para um novo no, que sera acrescentado
a arvore. O no original `child' tera (t-1) chaves ao final da execucao.

O novo no resultante sera adicionado a arvore, logo abaixo de `parent'.
*/
int bt_split_child(bt_node *parent, int index, bt_node *child);

/* Funcao auxiliar para particionar (fazer a cisao de) um no.

Entrada:
x: um no que desejamos particionar
Devolve: Um novo no resultante da cisao.
*/
bt_node* bt_split(bt_node *x);

#endif