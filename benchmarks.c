#include <stdio.h>
#include <time.h>
#include <math.h>
#include "cosine.c"

// Measures the time of many executions in seconds. Smaller number is better.
double runtime(double (*func)(double))
{
    clock_t start = clock();
    for (volatile int i = 0; i < 100000000; i++)
    {
        volatile double c = func(i / 10000.0);
    }
    return (clock() - start) / (double)CLOCKS_PER_SEC;
}

// Finds the worst case for accuracy compared to math.h. Smaller number is better.
double accuracy(double (*func)(double))
{
    double w = -1;
    double start = 0;
    double stop = CONST_PI * 2;
    double step = 0.0000001;
    for (double i = start; i < stop; i += step)
    {
        double c = fabs(func(i) - cos(i));
        if (c > w)
        {
            w = c;
        }
    }
    return w;
}

// Benchmarks the accuracy and time for all of our cosine implementations.
int main(void)
{
    printf("Cosine benchmark\n\n");

    printf("ACCURACY\n");
    printf("cos_taylor_literal_4terms_naive \t%.16f\n", accuracy(cos_taylor_literal_4terms_naive));
    printf("cos_taylor_literal_6terms_naive \t%.16f\n", accuracy(cos_taylor_literal_6terms_naive));
    printf("cos_taylor_literal_6terms_2pi \t\t%.16f\n", accuracy(cos_taylor_literal_6terms_2pi));
    printf("cos_taylor_literal_6terms_pi \t\t%.16f\n", accuracy(cos_taylor_literal_6terms_pi));
    printf("cos_taylor_literal_6terms \t\t%.16f\n", accuracy(cos_taylor_literal_6terms));
    printf("cos_taylor_literal_10terms \t\t%.16f\n", accuracy(cos_taylor_literal_10terms));
    printf("cos_taylor_running_6terms \t\t%.16f\n", accuracy(cos_taylor_running_6terms));
    printf("cos_taylor_running_8terms \t\t%.16f\n", accuracy(cos_taylor_running_8terms));
    printf("cos_taylor_running_10terms \t\t%.16f\n", accuracy(cos_taylor_running_10terms));
    printf("cos_taylor_running_16terms \t\t%.16f\n", accuracy(cos_taylor_running_16terms));
    printf("cos_table_1 \t\t\t\t%.16f\n", accuracy(cos_table_1));
    printf("cos_table_0_1 \t\t\t\t%.16f\n", accuracy(cos_table_0_1));
    printf("cos_table_0_01 \t\t\t\t%.16f\n", accuracy(cos_table_0_01));
    printf("cos_table_0_001 \t\t\t%.16f\n", accuracy(cos_table_0_001));
    printf("cos_table_0_0001 \t\t\t%.16f\n", accuracy(cos_table_0_0001));
    printf("cos_table_1_LERP \t\t\t%.16f\n", accuracy(cos_table_1));
    printf("cos_table_0_1_LERP \t\t\t%.16f\n", accuracy(cos_table_0_1_LERP));
    printf("cos_table_0_01_LERP \t\t\t%.16f\n", accuracy(cos_table_0_01_LERP));
    printf("cos_table_0_001_LERP \t\t\t%.16f\n", accuracy(cos_table_0_001_LERP));
    printf("cos_table_0_0001_LERP \t\t\t%.16f\n", accuracy(cos_table_0_0001_LERP));

    printf("\nTIME\n");
    printf("cos_taylor_literal_4terms_naive \t%.16f\n", runtime(cos_taylor_literal_4terms_naive));
    printf("cos_taylor_literal_6terms_naive \t%.16f\n", runtime(cos_taylor_literal_6terms_naive));
    printf("cos_taylor_literal_6terms_2pi \t\t%.16f\n", runtime(cos_taylor_literal_6terms_2pi));
    printf("cos_taylor_literal_6terms_pi \t\t%.16f\n", runtime(cos_taylor_literal_6terms_pi));
    printf("cos_taylor_literal_6terms \t\t%.16f\n", runtime(cos_taylor_literal_6terms));
    printf("cos_taylor_literal_10terms \t\t%.16f\n", runtime(cos_taylor_literal_10terms));
    printf("cos_taylor_running_6terms \t\t%.16f\n", runtime(cos_taylor_running_6terms));
    printf("cos_taylor_running_8terms \t\t%.16f\n", runtime(cos_taylor_running_8terms));
    printf("cos_taylor_running_10terms \t\t%.16f\n", runtime(cos_taylor_running_10terms));
    printf("cos_taylor_running_16terms \t\t%.16f\n", runtime(cos_taylor_running_16terms));
    printf("cos_table_1 \t\t\t\t%.16f\n", runtime(cos_table_1));
    printf("cos_table_0_1 \t\t\t\t%.16f\n", runtime(cos_table_0_1));
    printf("cos_table_0_01 \t\t\t\t%.16f\n", runtime(cos_table_0_01));
    printf("cos_table_0_001 \t\t\t%.16f\n", runtime(cos_table_0_001));
    printf("cos_table_0_0001 \t\t\t%.16f\n", runtime(cos_table_0_0001));
    printf("cos_table_1_LERP \t\t\t%.16f\n", runtime(cos_table_1));
    printf("cos_table_0_1_LERP \t\t\t%.16f\n", runtime(cos_table_0_1_LERP));
    printf("cos_table_0_01_LERP \t\t\t%.16f\n", runtime(cos_table_0_01_LERP));
    printf("cos_table_0_001_LERP \t\t\t%.16f\n", runtime(cos_table_0_001_LERP));
    printf("cos_table_0_0001_LERP \t\t\t%.16f\n", runtime(cos_table_0_0001_LERP));
    printf("math.h \t\t\t\t\t%.16f\n", runtime(cos));
    printf("\n");

    // Code for generating a data file for gnuplot.
    /*
    FILE *f = fopen("plots/cosine.txt", "w");
    for(double x = 0.000; x < 4 * CONST_PI; x += 0.001) {
        fprintf(f, "%lf\t%lf\n", x, cos(x));
    }
    */

    return 0;
}