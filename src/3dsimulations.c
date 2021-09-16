#include "lapack_shell.h"


int main(int argc, char** argv)
{
    printf("Test %d\n", 1);

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

    calc_square_colmajor(inputs, input_size, righthands_outputs);

    return 0;
    }