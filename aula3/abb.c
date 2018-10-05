#include "abb.h"

void erd (no *r) {
    if (r != NULL) {
        erd(r->esq);
        printf("%d ", r->conteudo);
        erd(r->dir);
    }
}

void imprimir_folhas (no *r) {
    if (r != NULL) {
        imprimir_folhas(r->esq);
        if ((r->esq==NULL) && (r->dir==NULL))
            printf("%d ", r->conteudo);
        imprimir_folhas(r->dir);
    }    
}

int altura (no *r) {
    if (r == NULL)
        return -1;
    else {
        int he = altura(r->esq);
        int hd = altura(r->dir);
        if (he<hd)
            return hd+1;
        else
            return he+1;
    }
}

no* primeiro_erd(no *r) {
    while (r->esq != NULL)
        r = r->esq;
    return r;
}

no* ultimo_erd(no *r) {
    while (r->dir != NULL)
        r = r->dir;
    return r;
}

no* busca(no* r, int chave) {
    if (r == NULL || r->conteudo==chave)
        return r;
    if (r->conteudo > chave)
        return busca(r->esq, chave);
    else
        return busca(r->dir, chave);
}

void preenche_pai(no *r) {
    if (r == NULL) {
        return;
    } else if (r->pai == NULL){
        r->pai = r; 
    }

    if (r->esq) {
        r->esq->pai = r;
        preenche_pai(r->esq);
    }
    if (r->dir) {
        r->dir->pai = r;
        preenche_pai(r->dir);
    }    
}

no* inserir_no_na_arvore(no* r, int valor) {
    if (r == NULL) {
        r = cria_no(valor);
        return r;
    }

    /* Se já tem esse nó, retorna o original */
    if (r->conteudo == valor)
        return r;

    // Vai p/ esquerda
    if (valor < r->conteudo) {
        r->esq = inserir_no_na_arvore(r->esq, valor);
    // Vai p/ dirireita
    } else {
        r->dir = inserir_no_na_arvore(r->dir, valor);
    }

    return r;        
}

no* cria_no(int valor) {
    no* novo_no;
    novo_no = (struct cel*) malloc(sizeof(struct cel));
    novo_no->conteudo = valor;
    novo_no->esq = NULL;
    novo_no->dir = NULL;
    novo_no->pai = NULL;
    
    return novo_no;
}

