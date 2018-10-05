#include "abb.h"

int main(int argc, char *argv[]) 
{
    int i, valor;
    int n = atoi(argv[1]);
    no *raiz = NULL;

    for (i=0; i<n; i++) {
        scanf("%d", &valor);
        raiz = inserir_no_na_arvore(raiz, valor);
    }

    // Altura da arvore
    printf("\nAltura da arvore:%d\n", altura(raiz));
}

