/* Definicao de funcoes sobre arvores binarias de busca */
#ifndef __ABB_H__
#define __ABB_H__

#include <stdio.h>
#include <stdlib.h>

/* Estrutura de no para uma arvore binaria de busca que guarda um numero inteiro */
struct cel {
    int conteudo;
    struct cel *pai;
    struct cel *esq;
    struct cel *dir;
};
typedef struct cel no;

/* Percorre uma arvore na ordem esquerda-raiz-direita */
void erd(no *r);

/* */
void imprimir_folhas(no *r);

/* Calcula a altura de uma arvore, dado o no raiz */
int altura(no *r);

/* Devolve menor valor da arvore, dado o no raiz */
no* primeiro_erd(no *r);

/* Devolve maior valor da arvore, dado o no raiz */
no* ultimo_erd(no *r);

/* Preenche o ponteiro pai de todos nos da arvore, dado o no raiz */
void preenche_pai(no *r);

/* Busca por um valor (chave) na arvore e devole o no correspodente, caso exista.
   Do contrario, devolve NULL
*/
no* busca(no* r, int chave);

/* Insere um novo valor inteiro na arvore.
   Caso o valor ja exista na arvore, deve devolver NULL. Caso contrario,
   deve devolver no raiz da arvore */
no* inserir_no_na_arvore(no* r, int valor);

/* Cria um no com o valor passado e retorna */
no* cria_no(int valor);

#endif



