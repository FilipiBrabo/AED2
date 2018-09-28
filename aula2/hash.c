#include "hash.h"
#include <math.h>

int div_hash(int key, int m) {
    
    return key % m;
}

int mult_hash(int key, int m, float a) {
    
    return (int)floor(m * ((key*a) - floor(key*a)));
}