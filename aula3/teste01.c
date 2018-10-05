#include <stdio.h>
#include <stdlib.h>
#include "abb.h"


int main(int argc, char *argv[]) 
{
    int i;
    int v[] = {-1,10,20,30,40,50,60,70,80,90,100};	
    int n = sizeof(v)/sizeof(v[0]); /* numero de elementos de v */
    no *(pv[n]);
    
    // criacao dos nos/vertices
    for (i=0; i<n; i++) {
        no* celula = (no *)malloc(sizeof(no));
        celula->conteudo = v[i];
        celula->esq = NULL;
        celula->dir = NULL;
        pv[i] = celula;
    }
    
    // cricao da arvore (no modo heap)
    for (i=1; i<=n/2; i++) {
        no* celula = pv[i];
        if (2*i<n)
            celula->esq = pv[2*i];
        if (2*i+1<n)
            celula->dir = pv[2*i+1];
    }

    // raiz da arvore eh o elemento na posicao 1 do vetor de ponteiros    
    no *raiz = pv[1];
    printf("\nRaiz: %d\n", raiz->conteudo);
    
    // Varredura e-r-d da árvore
    printf("\nVarredura e-r-d:\n");
    erd(raiz);
    
    // Imprimir as folhas
    printf("\nFolhas da arvore:\n");
    imprimir_folhas(raiz);

    // Altura da arvore
    printf("\nAltura da arvore:%d\n", altura(raiz));


    preenche_pai(raiz);
    no* ultimo = ultimo_erd(raiz);
    printf("\nPai do ultimo no e-r-d: %d\n", ultimo->pai->conteudo);

    printf("\nPai da raiz: %d\n", raiz->pai->conteudo);
}

