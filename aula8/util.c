#include "util.h"

FILE *open_file(char* file_name, char* mode) {
    FILE *fd = fopen(file_name, mode);
    if(fd == NULL) {
        perror("Could not open file.");
    }
    return fd;
}