#include <stdio.h>
#include "search.h"
#include <time.h>

int test_search(int array[], int array_size, int key, int search_type);
void line();

int main() {
    int v1[5] = {1, 2, 3, 4, 5};
    int v2, v3[50], v4[0];
    

    for (int i = 0; i < 50; i ++) {
        v3[i] = i*2;
    }
    line();
    printf("Posicao:%d\n", test_search(v1, 5, 5, 1));
    line();
    printf("Posicao:%d\n", test_search(v1, 5, 5, 2));
    line();
    printf("Posicao:%d\n", test_search(v3, 50, 5, 1));
    line();
    printf("Posicao:%d\n", test_search(v3, 50, 5, 2));
    line();
    printf("Posicao:%d\n", test_search(v3, 50, 40, 1));
    line();
    printf("Posicao:%d\n", test_search(v3, 50, 40, 2));
    
    return 0;
}

int test_search(int array[], int array_size, int key, int search_type) {
    time_t t_inicio, t_fim;
    double delta;
    int result;
    
    if (search_type == 0) {
        t_inicio = clock();
        result = seq_search(array, array_size, key);
        t_fim = clock();
        delta = 1e6*(double)(t_fim - t_inicio)/CLOCKS_PER_SEC;
    } else {
        t_inicio = clock();
        result = binary_search(array, array_size, key);
        t_fim = clock();
        delta = 1e6*(double)(t_fim - t_inicio)/CLOCKS_PER_SEC;
    }
    
    if (search_type == 1) {
        printf("Time of seq_search: %lf\n", (double)delta);
    }else { 
        printf("Time of binary_search: %lf\n", (double)delta);
    }
    return result;
}

void line() {
    printf("-------------------------------------\n");
}
