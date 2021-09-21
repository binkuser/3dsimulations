#include "lapack_shell.h"
#include "bars.h"


int main(int argc, char** argv)
{
    /* all sizes in meters, outputs in H */
    bars* brs = bars_new();
    double width = 1e-6; 
    double length = 2.0 * width;
    double height = width;
    double apart = (1.0 + 1e-7) * width; /*includes width of bar 1, for 64 bit: (1 + 1e-7) times width seems minumum achievable distance*/
    double length_shift = 0.0; /*includes length of bar 1 */
    double height_shift = 0.0; /* includes height of bar 1 */
    brs->a = width;
    brs->b = height;
    brs->l1 = length;
    brs->d = width;
    brs->c = height;
    brs->l2 = length;
    brs->E = apart;
    brs->l3 = length_shift;
    brs->P = height_shift;

    
printf("L1: %.8e L2: %.8e M: %.8e\n\n",Lb(brs, 1),Lb(brs, 2), Mb(brs));
free(brs);

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