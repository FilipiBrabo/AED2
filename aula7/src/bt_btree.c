#include "../include/bt_btree.h"
#include <stdio.h>

bt_tree* new_tree(int t){
    /* cria uma arvore vazia, com a raiz inicialmente nula */
    bt_tree* tree = (bt_tree*) malloc(sizeof(bt_tree));
    if(!tree) return NULL;
    tree->t = t;
    tree->root = NULL;
    return tree;
}

bt_node* bt_new_node(int t, bool is_leaf){
    bt_node* node = (bt_node*) malloc(sizeof(bt_node));
    if (!node) return NULL;
    /* 
    O no tem capacidade para ate 2*t filhos e  (2*t - 1) chaves.
    */
    node->keys = (int*) malloc((2*t-1)*sizeof(int));
    if(node->keys == NULL){
        free(node);
        return NULL;
    }
    node->children = (bt_node**) malloc(2*t*sizeof(bt_node*));
    if(!node->children){
        free(node->keys);
        free(node);
        return NULL;
    }
    node->is_leaf = is_leaf;
    node->t = t;
    node->num_keys = 0; /* no inicio o no e vazio */
    return node;
}

int bt_insert(bt_tree* T, int key){
    if(!T) return -1;
    int t = T->t;
    if(T->root == NULL){
        /* se a arvore ainda estiver vazia, vamos criar um novo no
        com a chave e entao esse no torna-se a raiz da arvore*/
        T->root = bt_new_node(t, true);
        if(T->root == NULL) return -1;
        T->root->keys[0] = key;
        T->root->num_keys = 1;
    } else {
        /* a raiz ja esta completa entao e preciso fazer a cisao da raiz
        antes de inserir a nova chave */
        if((2*t - 1) == T->root->num_keys){
            /* cria-se um no para ser a nova raiz */
            bt_node* n = bt_new_node(T->t, false);
            /* a antiga raiz torna-se o unico filho da nova raiz */
            n->children[0] = T->root;
            T->root = n;
            /* agora particionamos o no que estava completo (antiga raiz) */
            bt_split_child(n, 0, n->children[0]);
            /* finalmente inserimos a nova chave */
            bt_insert_non_full(n, key);
        } else {
            /* a raiz nao esta completa, entao usamos a funcao de insercao
               apropriada */
            bt_insert_non_full(T->root, key);
        }
    }
    return 0;
}

int bt_insert_non_full(bt_node* N, int key){
    if(!N) return -1;
    int i = N->num_keys - 1; /* indice da maior chave de N */
    if(N->is_leaf){
        /* se o no atual e uma folha, apenas deslocamos as chaves
        maiores, criando o espaco para inserir a chave diretamente
        no no atual.
        */
        while(key < N->keys[i] && i >= 0) {
            /* desloca as chaves enquanto localiza o ponto
             de insercao */
            N->keys[i+1] = N->keys[i];
            i--;
        }
        i++;
        /* inserimos a chave e incrementamos o contador de chaves */
        N->keys[i] = key;
        N->num_keys += 1;
        return 0;
    }
    else{
        /* o no atual nao e folha; localiza o no filho em que devemos
        prosseguir com a insercao */
        while(key < N->keys[i] && i >= 0) {
            i--;
        }
        i++;
        /* no filho em baixo do qual devemos inserir a chave */
        bt_node* child = N->children[i];
        if(2*(child->t) - 1 == child->num_keys) {
            /* se o filho esta completo, devemos fazer a cisao e 
            prosseguir */
            bt_split_child(N, i, child);
            if(key > N->keys[i]) i++;
        }
        return bt_insert_non_full(N->children[i], key);
    }
}

int bt_split_child(bt_node *parent, int index, bt_node *child) {
    /* Faz a cisao de child, criando um novo no.
    As chaves superiores de child são copiadas no novo no.*/
    bt_node *new_child = bt_split(child);
    int t = parent->t;
    /* desloca os filhos, abrindo espaco para o novo no */
    for(int j = parent->num_keys; j >= index + 1; j--){
        parent->children[j + 1] = parent->children[j];
    }
    /* acrescenta o no recem criado em parent */
    parent->children[index + 1] = new_child;
    /* desloca as chaves existentes em parent para criar espaco para
    a chave mediana de child */
    for(int j = parent->num_keys-1; j >= index + 1; j--){
        parent->keys[j + 1] = parent->keys[j];
    }
    /* a chave mediana de child e transportada para o pai */
    parent->keys[index] = child->keys[t - 1];
    /* com acrescimo no novo no e chave, incrementamos o contador de chaves */
    parent->num_keys += 1;
    return 0;
}

bt_node* bt_split(bt_node *x) {
    /*
    Essa funcao recebe um x no completo; isto e, um no contendo (2*t -1) chaves.

    A funcao realiza a cisao de x, criando um novo no y com a mesma capacidade t.
    Caso x seja uma folha, y tambem sera. Se x for um no interno, y sera um no 
    interno.
    As (t-1) maiores chaves de x sao copiadas para y.
    A chave mediana de x (a chave de indice t) sera copiada posteriormente para
    o pai de x. Por isso a chave posicionada no indice t do no x deve manter 
    o mesmo valor que tinha no inicio da funcao.

    Caso x seja um no interno, os t filhos superiores de x devem ser copiados
    para y.

    Ao final da funcao, o numero de chaves (num_keys) tanto de x quanto de y 
    deve ser (t-1).

    A funcao deve devolver o novo no y.
    */
}

bt_node* search(bt_tree *T, int key) {
    //TODO   
    /* Busca o no que contem determinada chave.
    Entrada:
    T: arvore onde sera feita a busca
    key: chave para busca
    Devolve: o no que contem a chave caso ele exista, NULL caso a chave nao seja encontrada.
    */
}
