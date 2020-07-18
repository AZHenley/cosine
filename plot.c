#include <stdio.h>
#include <math.h>
#include "cosine.c"

// Generate plot data to be used by gnuplot.
int main(void)
{
    printf("Plot cosine data\n\n");

    FILE *f = fopen("plots/math.h.dat", "w");
    for(double x = 0.0000; x < 4 * CONST_PI; x += 0.0001) {
        fprintf(f, "%lf\t%lf\n", x, cos(x));
    }

    printf("Done.\n");
    return 0;
}