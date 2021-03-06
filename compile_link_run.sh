#!/usr/bin/env bash

# remove any previous results to avoid confusion
rm ./bin//3dsimulations.a

# compile
gcc -I./include -c ./src/lapack_shell.c -o ./bin/lapack_shell.o 
gcc -I./include -c ./src/3dsimulations.c -o ./bin/3dsimulations.o 
gcc -I./include -c ./src/bars.c -o ./bin/bars.o 

# link
gcc -L ./lib -o ./bin/3dsimulations.a ./bin/lapack_shell.o ./bin/3dsimulations.o  ./bin/bars.o -lm -lblas -llapack -llapacke

# clean
rm ./bin/lapack_shell.o 
rm ./bin/3dsimulations.o
rm ./bin/bars.o

# run
./bin//3dsimulations.a