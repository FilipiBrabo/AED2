#include<stdio.h>
#include<stdlib.h>

#include "../include/util.h"
#include "../include/ext_sort.h"

int main(int argc, char** argv) {
    int page_size = 4000;
    
    merge_files("../out/o0.txt","../in/r0.txt", "../in/r1.txt", page_size);
    merge_files("../out/o1.txt","../in/r2.txt", "../in/r3.txt", page_size);
    merge_files("../out/o2.txt","../in/r4.txt", "../in/r5.txt", page_size);
    merge_files("../out/o3.txt","../in/r6.txt", "../in/r7.txt", page_size);
    merge_files("../out/o4.txt","../in/r8.txt", "../in/r9.txt", page_size);
    merge_files("../out/o5.txt","../in/r10.txt", "../in/r11.txt", page_size);
    
    // merge_files("../out/o6.txt","../out/o0.txt", "../out/o1.txt", page_size);
    // merge_files("../out/o7.txt","../out/o2.txt", "../out/o3.txt", page_size);
    // merge_files("../out/o8.txt","../out/o4.txt", "../out/o5.txt", page_size);
    
    // merge_files("../out/o9.txt","../out/o6.txt", "../out/o7.txt", page_size);
    // merge_files("../out/arqfinal.txt","../out/o9.txt", "../out/o8.txt", page_size);
    
    return 0;
}