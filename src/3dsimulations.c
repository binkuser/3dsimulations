#include "lapack_shell.h"
#include "bars.h"


int main(int argc, char** argv)
{
    
    bars brs;


            lapack_complex_double inputs[] =
        {

                lapack_make_complex_double(1.0,1.0),
                lapack_make_complex_double(1.0,-1.0),
                lapack_make_complex_double(-1.0,0.0),
                lapack_make_complex_double(1.0,1.0)

                };
        lapack_complex_double righthands_outputs[]={
                lapack_make_complex_double(0.0,1.0),
                lapack_make_complex_double(1.0,0.0)
        };

    
    int input_size = 2;
    int info;
    info = calc_square_colmajor(inputs, input_size, righthands_outputs);
    printf("Result info code: %d\n", info);
    print_matrix_colmajor( "Solution should be: \n0.5+j0.5 \n0.0+j0.0\n\n", input_size, 1, righthands_outputs, input_size );

    return 0;
    }