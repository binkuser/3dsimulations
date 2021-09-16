#!/usr/bin/env bash

# remove any previous results to avoid confusion
rm ./bin//3dsimulations.a

# compile
gcc -I./include -c ./src/lapack_shell.c -o ./bin/lapack_shell.o 
gcc -I./include -c ./src/3dsimulations.c -o ./bin/3dsimulations.o 

# link
gcc -o ./bin/3dsimulations.a ./bin/lapack_shell.o ./bin/3dsimulations.o -lm -lblas -llapack -llapacke 

# clean
rm ./bin/lapack_shell.o 
rm ./bin/3dsimulations.o

# run
./bin//3dsimulations.a