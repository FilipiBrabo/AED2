#ifndef __EXT_SORT_H__
#define __EXT_SORT_H__

#include<stdio.h>
#include<string.h>
#include "util.h"

/**
 * Faz a intercalacao entre dois subarrays contiguos ordenados.
 * Primeiro array: buffer[left]... buffer[median-1] 
 * Segundo array: buffer[median]... buffer[right-1] 
 * 
 * Ao final da execucao, o conteudo ordenado estara guardado
 * em buffer[left]...buffer[right-1]
 */
void merge(int* buffer, int left, int median, int right);

/**
 * Aplica o algoritmo mergesort aos elementos de buffer
 * que estejam nas posicoes left ate (right -1)
 * 
 * Para ordenar um buffer inteiro, chamar com o seguintes
 * parametros:
 * 
 * merge_sort(buffer, 0, BUFFER_LENGTH)
 * 
 * em que BUFFER_LENGTH é o numero de elementos guardados em
 * buffer
 */ 
void merge_sort(int* buffer, int left, int right);

/**
 * Escreve o conteudo de buffer no arquivo de saida
 */ 
int write_buffer(FILE* output, int* buffer, int num_items);


int create_runs(char* input_file, int page_size);

#endif