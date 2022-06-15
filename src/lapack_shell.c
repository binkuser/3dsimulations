/* 
        Copyright (C) 2021 Gérard Binkhorst, Copyright (c) 2006-2013 The University of Colorado Denver.  All rights
        reserved.
        This program is free software: you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation, either version 3 of the License, or
        (at your option) any later version.

        This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.

        You should have received a copy of the GNU General Public License
        along with this program.  If not, see <https://www.gnu.org/licenses/>. 

        For LAPACKE:

        Redistribution and use in source and binary forms, with or without
        modification, are permitted provided that the following conditions are
        met:

        - Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

        - Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer listed
        in this license in the documentation and/or other materials
        provided with the distribution.

        - Neither the name of the copyright holders nor the names of its
        contributors may be used to endorse or promote products derived from
        this software without specific prior written permission.

        The copyright holders provide no reassurances that the source code
        provided does not infringe any patent, copyright, or any other
        intellectual property rights of third parties.  The copyright holders
        disclaim any liability to any recipient for claims brought against
        recipient by any third party for infringement of that parties
        intellectual property rights.

        THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
        "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
        LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
        A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
        OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
        SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
        LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
        DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
        THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
        (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
        OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

/* installing LAPACKE on Ubuntu:
sudo apt-get install liblapack-dev
sudo apt-get install libopenblas-base
sudo apt-get install libopenblas-dev
sudo apt-get install liblapacke-dev
sudo apt-get install libcblas-base
sudo apt-get install libcblas
sudo apt-get install cblas
*/

/* Compiling and running with GCC in shell script:
#!/usr/bin/env bash
gcc lapack_test.c -o lapack_test.a -lm -lblas -llapack -llapacke
./lapack_test.a


installing LAPACKE on MinGW:
install MSYS / MinGW
Make sure Windows PATH includes C:\msys64\usr\bin (which contains pacman.exe)
Execute: pacman -S mingw-w64-x86_64-lapack

*/

#include "lapack_shell.h"


/* Auxiliary routine: printing a rowmajor matrix */
 void print_matrix_rowmajor( char* desc, lapack_int m, lapack_int n, lapack_complex_double* mat, lapack_int ldm ) {
         lapack_int i, j;
         printf( "\n %s\n", desc );

         for( i = 0; i < m; i++ ) {
                 for( j = 0; j < n; j++ ) printf( " %6.4f + j%6.4f", crealf(mat[i*ldm+j]),cimagf(mat[i*ldm+j]) );
                 printf( "\n" );
         }
 }


 /* Auxiliary routine: printing a colmajor matrix */
 void print_matrix_colmajor( char* desc, lapack_int m, lapack_int n, lapack_complex_double* mat, lapack_int ldm ) {
         lapack_int i, j;
         printf( "\n %s\n", desc );

         for( i = 0; i < m; i++ ) {
                 for( j = 0; j < n; j++ ) printf( " %6.4f + j%6.4f", crealf(mat[i+j*ldm]),cimagf(mat[i+j*ldm]) );
                 printf( "\n" );
         }
 }

int calc_square_colmajor(lapack_complex_double inputs[], int input_size, lapack_complex_double righthands_outputs[])
/*The results will be written in the same array as the right hand side values.*/
{
    lapack_int info,n,nrhs,lda,ldb;
    n = input_size;
    nrhs = 1;
    lda = n;
    ldb = n;
    lapack_int ipiv[n];
    info = LAPACKE_zgesv(LAPACK_COL_MAJOR,n,nrhs,inputs,lda,ipiv,righthands_outputs,ldb);
    return info;

}


int main_old (int argc, const char * argv[])
{
        /*
           Equation example:
           (1+j)*p1 + (-1)*p2 = j
           (1-j)*p1 + (1+j)*p2 = 1

           Solution:
           p1 = 0.5 + 0.5 j
           p2 = 0

           The rowmajor array should look like:
           (1+j),(-1),(1-j),(1+j)

           The colmajor array should look like:
           (1+j),(1-j),(-1),(1+j)

           The rowmajor format is more familiar to read algabraically.
           However lapack will run faster on colmajor matrices because it has been designed for FORTAN..

           Meaning of variables in the example:
           n is the order of matrix A and the number of rows of B in AxS=B.
           Array a is the input co-efficient representing matrix A of size lda by n (lda: leading dimension of A).
           Array b is the input co-efficient representing matrix of size ldb by nrhs (number of right hand sides).
           For a single circuit square matrix equation normally nrhs=1 and lda=ldb=n.
           The return number generated by LAPACKE_zgsv() indicates any problems, info=0 means OK, otherwise it is the index where the inverse could not be computed.
           The solutions S will be written in b, overwriting the original input of right hand sides.
           The internally used transform matrix will be written in a.
           The internally used pivot indices will be written in the ipvt array.

         */
        lapack_complex_double a[] =
        {
/*              // rowmajor
                lapack_make_complex_double(1.0,1.0), lapack_make_complex_double(-1.0,0.0),
                lapack_make_complex_double(1.0,-1.0),lapack_make_complex_double(1.0,1.0)
*/
                // colmajor
                lapack_make_complex_double(1.0,1.0),
                lapack_make_complex_double(1.0,-1.0),
                lapack_make_complex_double(-1.0,0.0),
                lapack_make_complex_double(1.0,1.0)

                };
        lapack_complex_double b[]={
                lapack_make_complex_double(0.0,1.0),
                lapack_make_complex_double(1.0,0.0)
        };
        lapack_int info,n,nrhs,lda,ldb;
        n=2;
        nrhs=1;
        lda=n; /* square matrix */
        ldb=n; /* for colmajor: n, for rowmajor: nrhs */
        lapack_int ipiv[n];
        info=LAPACKE_zgesv(LAPACK_COL_MAJOR,n,nrhs,a,lda,ipiv,b,ldb);
/*      info=LAPACKE_zgesv(LAPACK_ROW_MAJOR,n,nrhs,a,lda,ipiv,b,ldb); */
        printf("The value of info: %d\n",info);
/*      print_matrix_rowmajor( "Solution should be: \n0.5+j0.5 \n0.0+j0.0\n\n", n, nrhs, b, ldb ); */
        print_matrix_colmajor( "Solution should be: \n0.5+j0.5 \n0.0+j0.0\n\n", n, nrhs, b, ldb );
}