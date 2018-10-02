#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

#define PATH "./resultados/"
#define ARQ_TYPE ".csv"

void test_div_hash(int m, int range, int num);
void write_file(int *collisions, char* file_name, int m);
void create_file();
void test_mul_hash(int m, int range, float a);
char* float_to_char(float a);
char* int_to_char(int num);
char* concat(char *s1, char *s2, char *s3, char *s4);

int main(){

    test_div_hash(12, 100, 3);  
    
    test_div_hash(11, 100, 3);   
    
    test_div_hash(97, 10000, 0);   

    test_mul_hash(200, 500000, 0.620); 

    test_mul_hash(200, 500000, 0.61803398875);

    test_div_hash(200, 500000, 0);  

    return 0;
}

//Testa o método da divisão para gerar o hash e salva as colisões em um arq
void test_div_hash(int m, int range, int num) {
    printf("\nDIV_HASH\nTeste com m = %d\n", m);

    //inicialização do vetor de m posições 
    int *collisions = calloc(m, sizeof(int));

    for (int i = 1; i < range; i++) {
        int h = div_hash(i, m);
        collisions[h] ++;

        if (num != 0 && h == num)
            printf("%d ", i);
    } 
    printf("\n");

    //cria o nome do arquivo que vai ser gerado
    char *arq_name = concat(PATH, "div_test_m_", int_to_char(m), ARQ_TYPE);
    
    //chama a função para gerar/escrever no arquivo
    write_file(collisions, arq_name, m);
    printf("Resultado das colisões estão no arquivo: %s\n", arq_name);

    //libera a memória
    free(collisions);
    free(arq_name);
}

// Testa o método da multiplicação para gerar o hash e salva as colisões em um arq
void test_mul_hash(int m, int range, float a) {
    printf("\nMUL_HASH\nTeste executado com m = %d e a = %.3f\n", m, a);
    
    // inicialização do vetor de m posições
    int *collisions = calloc(m, sizeof(int));
    for (int i = 1; i < range; i++) {
        int h = mult_hash(i, m, a);
        collisions[h] ++;
    }

    // cria o nome do arquivo que vai ser gerado
    char *arq_name = concat(PATH, "mul_test_", float_to_char(a), ARQ_TYPE);
  
    // chama a função para gerar/escrever no arquivo
    write_file(collisions, arq_name, m);    
    printf("Resultado das colisões estão no arquivo: %s\n", arq_name);
    
    // libera memória
    free(collisions);
    free(arq_name);
}

//Concatenação de 4 strings
char* concat(char *s1, char *s2, char *s3, char *s4) {
    // Alocação da memória p/ a nova string
    char *s = malloc((strlen(s1) + strlen(s2) + strlen(s3) + strlen(s4) + 1) * sizeof(char));
    strcpy(s, s1);
    strcat(s, s2);
    strcat(s, s3);
    strcat(s, s4);
    
    // libera a memória do vetor "buffer" que é criado nos métodos int_to_char e float_to_char
    free(s3);
    return s;
}

// Cria/Escreve os hashs e as colisões em um arquivo .csv
void write_file(int *collisions, char* file_name, int m) {
    FILE *fp = fopen(file_name, "w");

    fprintf(fp, "Hash,Colisões\n");
    for (int i = 1; i < m; i++) {        
        fprintf(fp, "%d,%d\n", i, collisions[i]);   
    }
    
    fclose(fp);
}

// Converte um float para string
char* float_to_char(float num) {
    char *buffer = malloc(10 * sizeof(char));
    snprintf(buffer, 7, "%.4f", num); 

    return buffer;
}

// Converte um int para string
char* int_to_char(int num) {
    char *buffer = malloc(10 * sizeof(char));
    sprintf(buffer, "%d", num);

    return buffer;
}
