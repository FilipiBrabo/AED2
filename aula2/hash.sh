#!/bin/bash

mkdir resultados
gcc main.c hash.c -o hash.exe -lm
./hash.exe