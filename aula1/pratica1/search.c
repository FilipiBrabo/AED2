#include "search.h"

int seq_search(int array[], int array_size, int key) {
    if (!array)
        return -1;

    for (int i = 0; i < array_size; i++)
        if (array[i] == key)
            return i;

    return -1;
}

int binary_search(int array[], int array_size, int key) {
    if (!array)
        return -1;
    
    int first = 0, last = array_size - 1;

    while (first <= last) {
        int middle = (last + first)/2;

        if (array[middle] == key){
            return middle;
        } else if (array[middle] < key) {
            first = middle + 1;
        } else {
            last = middle - 1;
        }
    }

    return -1;
}