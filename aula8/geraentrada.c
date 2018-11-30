#include<errno.h>
#include<stdio.h>
#include<stdlib.h>

#include "util.h"
#include "ext_sort.h"

int main(int argc, char** argv) {
    char input_name[] = "./input.txt";
    int page_size = 4000;
    int num_pages = 12;
    int i;
    FILE *fd;

    srand(42);
    fd = open_file(input_name, "w");
    if(fd == NULL){
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < page_size*num_pages; i++) {
        fprintf(fd, "%d\n", rand());
    }
    fclose(fd);

    create_runs(input_name, page_size);
    return 0;
}