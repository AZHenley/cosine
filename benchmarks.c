#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "cosine.c"

// Measures the time of many executions in seconds. Smaller number is better.
double runtime(double (*func)(double))
{
    clock_t start = clock();
    for (int i = 0; i < 100000000; i++)
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
    double stop = CONST_2PI;
    double step = 0.0000001;
    for (double i = start; i < stop; i += step)
    {
        double c = absd(func(i) - cos(i));
        if (c > w)
        {
            w = c;
        }
    }
    return w;
}

#define RTEST(x)  { #x, x }

static struct {
    char name[35];
    double (*func)(double v);
} tests[] = {
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
    int run_accuracy = 1;
    int run_runtime = 1;
    int literal = 1;
    int running = 1;
    int table = 1;
    int lerp = 1;
    int i;
    int j;

    for (i = 1;i < argc;i++) {
        if (!strcmp(argv[i], "-na")) {
            run_accuracy = 0;
        }
        else if (!strcmp(argv[i], "-nt")) {
            run_runtime = 0;
        }
        else if (!strcmp(argv[i], "-t")) {
            i++;
            if (i >= argc) {
                printf("Error, -t needs a test name.\n");
                return -1;
            }
            for (j = 0;j < num_tests;j++) {
                if (!strcmp(argv[i], tests[j].name)) {
                    printf("ACCURACY\n");
                    printf("%-35s %.16lf\n", tests[j].name, accuracy(tests[j].func));
                    printf("\nTIME\n");            
                    printf("%-35s %.16lf\n", tests[j].name, runtime(tests[j].func));
                    return 0;
                }
            }            
            printf("Test '%s' not found.\n", argv[i]);
            return -1;
        }
        else if (!strcmp(argv[i], "-p")) {
            printf("AVAILABLE TESTS\n");
            for (j = 0;j < num_tests;j++) {
                printf("%s\n", tests[j].name);
            }
            return 0;
        }
        else {
            printf("Usage: %s [-na] [-nt] [-t <testname>]\n   -na - Don't run accuracy tests\n   -nt - Don't run speed tests.\n   -t <testname> - Run a particular test instead of all tests.\n   -p - Print all test names.\n", argv[0]);
            return 0;
        }
    }


    printf("Cosine benchmark\n\n");
    if (run_accuracy) {
        printf("ACCURACY\n");
        for (i = 0;i < num_tests;i++) {
            printf("%-35s %.16lf\n", tests[i].name, accuracy(tests[i].func));
        }
    }
    
    if (run_runtime) {
        printf("\nTIME\n");
        for (i = 0;i < num_tests;i++) {
            printf("%-35s %.16lf\n", tests[i].name, runtime(tests[i].func));
        }
    }
    printf("\n\nDone\n");
    // Code for generating a data file for gnuplot.
    /*
    FILE *f = fopen("plots/cosine.txt", "w");
    for(double x = 0.000; x < 4 * CONST_PI; x += 0.001) {
        fprintf(f, "%lf\t%lf\n", x, cos(x));
    }
    */

    return 0;
}