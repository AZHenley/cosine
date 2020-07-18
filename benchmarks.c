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

#define RTEST(x)  { #x, x }

struct Tester {
    char name[255];
    double (*func)(double v);
};

static struct Tester tests[] = {
    /* cos_taylor_literal */
    RTEST(cos_taylor_literal_4terms_naive),
    RTEST(cos_taylor_literal_6terms_naive),
    RTEST(cos_taylor_literal_6terms_2pi),
    RTEST(cos_taylor_literal_6terms_pi),
    RTEST(cos_taylor_literal_6terms),
    RTEST(cos_taylor_literal_10terms),
    /* cos_taylor_running */
    RTEST(cos_taylor_running_6terms),
    RTEST(cos_taylor_running_8terms),
    RTEST(cos_taylor_running_10terms),
    RTEST(cos_taylor_running_16terms),
    /* cos_table */
    RTEST(cos_table_1),
    RTEST(cos_table_0_1),
    RTEST(cos_table_0_01),
    RTEST(cos_table_0_001),
    RTEST(cos_table_0_0001),
    /* cos_table_lerp */
    RTEST(cos_table_1_LERP),
    RTEST(cos_table_0_1_LERP),
    RTEST(cos_table_0_01_LERP),
    RTEST(cos_table_0_001_LERP),
    RTEST(cos_table_0_0001_LERP),
};

const int num_tests = sizeof(tests) / sizeof(*tests);

// Benchmarks the accuracy and time for all of our cosine implementations.
int main(int argc, char *argv[])
{
    int i;
    printf("Cosine benchmark\n\n");
    printf("ACCURACY\n");
    for (i = 0;i < num_tests;i++) {
        printf("%-35s %.16lf\n", tests[i].name, accuracy(tests[i].func));
    }
    
    printf("\nTIME\n");
    for (i = 0;i < num_tests;i++) {
        printf("%-35s %.16lf\n", tests[i].name, runtime(tests[i].func));
    }
    // Code for generating a data file for gnuplot.
    /*
    FILE *f = fopen("plots/cosine.txt", "w");
    for(double x = 0.000; x < 4 * CONST_PI; x += 0.001) {
        fprintf(f, "%lf\t%lf\n", x, cos(x));
    }
    */

    return 0;
}