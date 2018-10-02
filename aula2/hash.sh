#!/bin/bash

mkdir resultados
gcc -Wall main.c hash.c -o hash -lm
./hash