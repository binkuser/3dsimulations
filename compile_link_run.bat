::@echo off

::remove any previous results to avoid confusion
del /Q .\bin\*

:: compile
gcc -I ./include -c ./src/lapack_shell.c -o ./bin/lapack_shell.o 
gcc -I ./include -c ./src/3dsimulations.c -o ./bin/3dsimulations.o 
gcc -I ./include -c ./src/bars.c -o ./bin/bars.o 

:: link
gcc -L ./lib -o ./bin/3dsimulations.exe ./bin/3dsimulations.o ./bin/lapack_shell.o ./bin/bars.o  -llapacke -llapack -lblas -lm 


:: run
.\bin\3dsimulations.exe