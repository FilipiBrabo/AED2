#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"


void printLine();
void test_div_hash(int m, int range, int num);
void writeFile(int *collisions, char* file_name, int m);
void test_mul_hash(int m, int range, float a);
char* float_to_char(float a);
char* concat(char *s1, char *s2);

int main() {
    int *collisions;    
    
    test_div_hash(12, 100, 3);  
    
    test_div_hash(11, 100, 3);   
    
    test_div_hash(97, 10000, 0);   

    test_mul_hash(200, 500000, 0.620); 

    test_mul_hash(200, 500000, 0.61803398875);
  

    return 0;
}

void printLine() {
    printf("\n-----------------------------------------------\n");
}

void test_div_hash(int m, int range, int num) {
    printf("\nDIV_HASH\nTeste com m = %d e h == %d\n", m, num);

    int *collisions = calloc(m, sizeof(int));
    for (int i = 1; i < range; i++) {
        int h = div_hash(i, m);
        collisions[h] ++;

        if (num != 0 && h == num)
            printf("%d ", i);
    }

    //writeFile(collisions, "div_hash", m);  
}

void test_mul_hash(int m, int range, float a) {
    printf("aaaaaa\n");
    int *collisions = calloc(m, sizeof(int));
    for (int i = 1; i < range; i++) {
        int h = mult_hash(i, m, a);
        collisions[h] ++;
    }
    printf("aaaaaa\n");
    char *arq_name = concat("mul_test", float_to_char(a));
    printf("aaaaaa\n");
    arq_name = concat(arq_name, ".txt");
    printf("%s", arq_name);
    writeFile(collisions, arq_name, m); 
}

char* concat(char *s1, char *s2) {
    char *name = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(name, s1);
    strcat(name, s2);
    return name;
}

void writeFile(int *collisions, char* file_name, int m) {
    FILE *fp = fopen(file_name, "w");

    for (int i = 1; i < m; i++) {
        fprintf(fp, "%d %d\n", i, collisions[i]);
    }

    fclose(fp);
}

char* float_to_char(float a) {
    char* nome;
    sprintf(nome, "%.3f", a); 
}