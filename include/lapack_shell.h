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
#ifndef LAPACK_SHELL_H
#define LAPACK_SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <lapacke.h>
/* #include <cblas.h> */

/* Auxiliary routine: printing a rowmajor matrix */
 void print_matrix_rowmajor( char* desc, lapack_int m, lapack_int n, lapack_complex_double* mat, lapack_int ldm );

  /* Auxiliary routine: printing a colmajor matrix */
 void print_matrix_colmajor( char* desc, lapack_int m, lapack_int n, lapack_complex_double* mat, lapack_int ldm );


int calc_square_colmajor(lapack_complex_double inputs[], int input_size, lapack_complex_double righthands_outputs[]);

 #endif