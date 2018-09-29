#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

#define PATH "./resultados/"

void test_div_hash(int m, int range, int num);
void writeFile(int *collisions, char* file_name, int m);
void test_mul_hash(int m, int range, float a);
char* float_to_char(float a);
char* int_to_char(int num);
char* concat(char *s1, char *s2, char *s3, char *s4);

int main() {
    int *collisions;  

    test_div_hash(12, 100, 3);  
    
    test_div_hash(11, 100, 3);   
    
    test_div_hash(97, 10000, 0);   

    test_mul_hash(200, 500000, 0.620); 

    test_mul_hash(200, 500000, 0.61803398875);
  

    return 0;
}

void test_div_hash(int m, int range, int num) {
    printf("\nDIV_HASH\nTeste com m = %d\n", m);

    int *collisions = calloc(m, sizeof(int));
    for (int i = 1; i < range; i++) {
        int h = div_hash(i, m);
        collisions[h] ++;

        if (num != 0 && h == num)
            printf("%d ", i);
    } 
    printf("\n");
    
    char *arq_name = concat(PATH, "div_test_m_", int_to_char(m), ".txt");
    
    writeFile(collisions, arq_name, m);
    printf("Resultado das colisões estão no arquivo: %s\n", arq_name);

}

void test_mul_hash(int m, int range, float a) {
    printf("\nMUL_HASH\nTeste executado com m = %d e a = %.3f\n", m, a);
    
    int *collisions = calloc(m, sizeof(int));
    for (int i = 1; i < range; i++) {
        int h = mult_hash(i, m, a);
        collisions[h] ++;
    }

    char *arq_name = concat(PATH, "mul_test_", float_to_char(a), ".txt");
  
    writeFile(collisions, arq_name, m);
    printf("Resultado das colisões estão no arquivo: %s\n", arq_name);
   
}

char* concat(char *s1, char *s2, char *s3, char *s4) {
    char *s = malloc((strlen(s1) + strlen(s2) + strlen(s3) + strlen(s4) + 1) * sizeof(char));
    strcpy(s, s1);
    strcat(s, s2);
    strcat(s, s3);
    strcat(s, s4);
    //free(s1);
    //free(s2);
    return s;
}

void writeFile(int *collisions, char* file_name, int m) {
    FILE *fp = fopen(file_name, "w");

    for (int i = 1; i < m; i++) {        
        fprintf(fp, "%d %d\n", i, collisions[i]);   
    }
    
    fclose(fp);
}

char* float_to_char(float num) {
    char *buffer = malloc(10 * sizeof(char));
    snprintf(buffer, 7, "%.4f", num); 

    return buffer;
}

char* int_to_char(int num) {
    char *buffer = malloc(10 * sizeof(char));
    sprintf(buffer, "%d", num);

    return buffer;
}
