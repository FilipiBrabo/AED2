#include<stdio.h>
#include<string.h>
#include "../include/ext_sort.h"

void merge(int* buffer, int left, int median, int right){
    int *left_buf, *right_buf;
    int i = 0, j = 0, k = 0;
    int left_len, right_len;
    right_len = right - median;
    left_len = median - left;
    left_buf = (int*) malloc(sizeof(int)*left_len);
    right_buf = (int*) malloc(sizeof(int)*right_len);
    for(i = 0; i < left_len; i++){
        left_buf[i] = buffer[left+i];
    }
    for(i = 0; i < right_len; i++){
        right_buf[i] = buffer[median+i];
    }
    i = 0; j = 0; k = left;
    while(i < left_len && j < right_len) {
        if(left_buf[i] < right_buf[j]){
            buffer[k] = left_buf[i];
            i++;
        } else {
            buffer[k] = right_buf[j];
            j++;
        }
        k++;
    }
    while(i < left_len) {
        buffer[k] = left_buf[i];
        i++;
        k++;
    }
    while(j < right_len) {
        buffer[k] = right_buf[j];
        j++;
        k++;
    }
    free(left_buf);
    free(right_buf); 
}

void merge_sort(int* buffer, int left, int right) {
    int median;
    if(left < right-1) {
        median = left + (right - left)/2;
        merge_sort(buffer, left, median);
        merge_sort(buffer, median, right);
        merge(buffer, left, median, right);
    }
}

int write_buffer(FILE* output, int* buffer, int num_items){
    int i = 0;
    if(output == NULL) return 0;
    for(i = 0; i < num_items; i++){
        fprintf(output, "%d\n", *(buffer+i));
    }
    return num_items;
}

int create_runs(char* input_file, int page_size){
    FILE* input;
    FILE* output;
    char output_name[64];

    int *in_buffer;
    int has_data = 1;
    int count = 0;
    int num_pages = 0;
    input = open_file(input_file, "r");
    if(input == NULL) return -1;

    in_buffer = (int*) malloc(page_size*sizeof(int));
    if(in_buffer == NULL) {
        fclose(input);
        return -1;
    }

    has_data = 1;
    num_pages = 0;
    while(has_data) {
        for(count = 0; count < page_size; count++) {
            if(1 != fscanf(input, "%d\n", &in_buffer[count])) {
                has_data = 0;
                break;
            }
        }
        if(count > 0) {
            snprintf(output_name, sizeof(output_name), "r%d.txt", num_pages);
            output = open_file(output_name, "w");
            if(output_name == NULL) {
                fclose(input);
                free(in_buffer);
                return -1;
            }
            merge_sort(in_buffer, 0, count);
            write_buffer(output, in_buffer, count);
            fclose(output);
        }
        num_pages++;
    }
    return num_pages;
}

void merge_files(char* output, char* input1, char* input2, int page_size) {
    FILE* output_file = open_file(output, "w");
    FILE* input_file1 = open_file(input1, "r");
    FILE* input_file2 = open_file(input2, "r");    
    int* buffer_1     = (int*) malloc(page_size*sizeof(int));
    int* buffer_2     = (int*) malloc(page_size*sizeof(int));
    int *buffer_out   = (int*) malloc(page_size*sizeof(int));
    int len_buf_1     = 0;
    int len_buf_2     = 0;
    int has_data      = 1;    
    int ind_buf_1     = 0;
    int ind_buf_2     = 0;
    int ind_buf_out   = 0;
    

    // Enquanto 1 dos buffers tiver dados
    while (has_data) {
        // Preenche buf_1 se ele está vazio
        if (len_buf_1 == 0) {
            ind_buf_1 = 0;
            
            for(int i = 0; i < page_size; i++) {
                if(1 != fscanf(input_file1, "%d\n", &buffer_1[i])) {
                    break;
                }
                len_buf_1++;
            }
        }
    
        // Preenche buf_2 se ele está vazio
        if (len_buf_2 == 0) {
            ind_buf_2 = 0;
            
            for(int i = 0; i < page_size; i++) {
                if(1 != fscanf(input_file2, "%d\n", &buffer_2[i])) {
                    break;
                }
                len_buf_2++;
            }
        } 
        
        // Os dois buffers tem dados, então intercala-os
        if(len_buf_1 > 0 && len_buf_2 > 0) {
            // Enquanto houver dados nos buffers 1 e 2, e o buffer de saida não estiver cheio
            while (len_buf_1 > 0 && len_buf_2 > 0 && ind_buf_out < page_size) { 
                
                // Numero no buffer_1 menor que buffer 2
                if (buffer_1[ind_buf_1] < buffer_2[ind_buf_2]) {
                    buffer_out[ind_buf_out++] = buffer_1[ind_buf_1++];
                    len_buf_1--;
                
                // Numero no buffer 2 menor que buffer 1
                } else {
                    buffer_out[ind_buf_out++] = buffer_2[ind_buf_2++];
                    len_buf_2--;
                }
            }
            
        // Buffer 1 tem dado e buffer 2 não tem    
        } else if (len_buf_1 > 0 && len_buf_2 == 0) {
            
            // Enquanto houver dados no buffer 1, e o buffer de saida não estiver cheio
            while (len_buf_1 > 0 && ind_buf_out < page_size) { 
                buffer_out[ind_buf_out++] = buffer_1[ind_buf_1++];
                len_buf_1--;
            }    
        
        // Buffer 2 tem dado e buffer 1 não tem            
        } else if (len_buf_2 > 0 && len_buf_1 == 0) {
            
            // Enquanto houver dados no buffer 2, e o buffer de saida não estiver cheio
            while (len_buf_2 > 0 && ind_buf_out < page_size) { 
                buffer_out[ind_buf_out++] = buffer_2[ind_buf_2++];
                len_buf_2--;
            }  
        
        // Não tem dado nos dois buffers    
        } else {
            has_data = 0;
        } 
        
        // Buffer de saída cheio
        if (ind_buf_out == page_size) {
            write_buffer(output_file, buffer_out, page_size);
            ind_buf_out = 0;
        } 
    }

    // Verifica se há algum dado no buffer de saída remanescente
    if (ind_buf_out > 0) {
        write_buffer(output_file, buffer_out, ind_buf_out);
    }
}


