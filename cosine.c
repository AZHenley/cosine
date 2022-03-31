// Austin Henley and Stephen Marz
// See the explanation and benchmarks at http://austinhenley.com/blog/cosine.html
// Various methods of calculating cosine without math.h
// For educational purposes only :)

#include "costable_1.h"
#include "costable_0_1.h"
#include "costable_0_01.h"
#include "costable_0_001.h"
#include "costable_0_0001.h"

#define CONST_PI  3.14159265358979323846264338327950288419716939937510
#define CONST_2PI 6.28318530717958623199592693708837032318115234375000

#define modd(x, y) ((x) - (int)((x) / (y)) * (y))
#define lerp(w, v1, v2) ((1.0 - (w)) * (v1) + (w) * (v2))

double absd(double a) { *((unsigned long *)&a) &= ~(1UL << 63); return a; }

//
// Naive Taylor series functions.
//

double cos_taylor_literal_4terms_naive(double x)
{
    return 1 - ((x * x) / (2)) + ((x * x * x * x) / (24)) - ((x * x * x * x * x * x) / (720)) + ((x * x * x * x * x * x * x * x) / (40320));
}

double cos_taylor_literal_6terms_naive(double x)
{
    return 1 - ((x * x) / (2)) + ((x * x * x * x) / (24)) - ((x * x * x * x * x * x) / (720)) + ((x * x * x * x * x * x * x * x) / (40320)) - ((x * x * x * x * x * x * x * x * x * x) / (3628800)) + ((x * x * x * x * x * x * x * x * x * x * x * x) / (479001600));
}

// Taylor series with literals.

double cos_taylor_literal_6terms_2pi(double x)
{
    x = modd(x, CONST_2PI);
    return 1 - ((x * x) / (2)) + ((x * x * x * x) / (24)) - ((x * x * x * x * x * x) / (720)) + ((x * x * x * x * x * x * x * x) / (40320)) - ((x * x * x * x * x * x * x * x * x * x) / (3628800)) + ((x * x * x * x * x * x * x * x * x * x * x * x) / (479001600));
}

double cos_taylor_literal_6terms_pi(double x)
{
    x = modd(x, CONST_2PI);
    char sign = 1;
    if (x > CONST_PI)
    {
        x -= CONST_PI;
        sign = -1;
    }
    return sign * (1 - ((x * x) / (2)) + ((x * x * x * x) / (24)) - ((x * x * x * x * x * x) / (720)) + ((x * x * x * x * x * x * x * x) / (40320)) - ((x * x * x * x * x * x * x * x * x * x) / (3628800)) + ((x * x * x * x * x * x * x * x * x * x * x * x) / (479001600)));
}

double cos_taylor_literal_6terms(double x)
{
    x = modd(x, CONST_2PI);
    char sign = 1;
    if (x > CONST_PI)
    {
        x -= CONST_PI;
        sign = -1;
    }
    double xx = x * x;

    return sign * (1 - ((xx) / (2)) + ((xx * xx) / (24)) - ((xx * xx * xx) / (720)) + ((xx * xx * xx * xx) / (40320)) - ((xx * xx * xx * xx * xx) / (3628800)) + ((xx * xx * xx * xx * xx * xx) / (479001600)));
}

double cos_taylor_literal_10terms(double x)
{
    x = modd(x, CONST_2PI);
    char sign = 1;
    if (x > CONST_PI)
    {
        x -= CONST_PI;
        sign = -1;
    }
    double xx = x * x;

    return sign * (1 - ((xx) / (2)) + ((xx * xx) / (24)) - ((xx * xx * xx) / (720)) + ((xx * xx * xx * xx) / (40320)) - ((xx * xx * xx * xx * xx) / (3628800)) + ((xx * xx * xx * xx * xx * xx) / (479001600)) - ((xx * xx * xx * xx * xx * xx * xx) / (87178291200)) + ((xx * xx * xx * xx * xx * xx * xx * xx) / (20922789888000)) - ((xx * xx * xx * xx * xx * xx * xx * xx * xx) / (6402373705728000)) + ((xx * xx * xx * xx * xx * xx * xx * xx * xx * xx) / (2432902008176640000)));
}

//
// Taylor series with running product.
//

double cos_taylor_running_6terms(double x)
{
    int div = (int)(x / CONST_PI);
    x = x - (div * CONST_PI);
    char sign = 1;
    if (div % 2 != 0)
        sign = -1;

    double result = 1.0;
    double inter = 1.0;
    double num = x * x;
    for (int i = 1; i <= 6; i++)
    {
        double comp = 2.0 * i;
        double den = comp * (comp - 1.0);
        inter *= num / den;
        if (i % 2 == 0)
            result += inter;
        else
            result -= inter;
    }
    return sign * result;
}

double cos_taylor_running_8terms(double x)
{
    int div = (int)(x / CONST_PI);
    x = x - (div * CONST_PI);
    char sign = 1;
    if (div % 2 != 0)
        sign = -1;

    double result = 1.0;
    double inter = 1.0;
    double num = x * x;
    for (int i = 1; i <= 8; i++)
    {
        double comp = 2.0 * i;
        double den = comp * (comp - 1.0);
        inter *= num / den;
        if (i % 2 == 0)
            result += inter;
        else
            result -= inter;
    }
    return sign * result;
}

double cos_taylor_running_10terms(double x)
{
    int div = (int)(x / CONST_PI);
    x = x - (div * CONST_PI);
    char sign = 1;
    if (div % 2 != 0)
        sign = -1;

    double result = 1.0;
    double inter = 1.0;
    double num = x * x;
    for (int i = 1; i <= 10; i++)
    {
        double comp = 2.0 * i;
        double den = comp * (comp - 1.0);
        inter *= num / den;
        if (i % 2 == 0)
            result += inter;
        else
            result -= inter;
    }
    return sign * result;
}

double cos_taylor_running_16terms(double x)
{
    int div = (int)(x / CONST_PI);
    x = x - (div * CONST_PI);
    char sign = 1;
    if (div % 2 != 0)
        sign = -1;

    double result = 1.0;
    double inter = 1.0;
    double num = x * x;
    for (int i = 1; i <= 16; i++)
    {
        double comp = 2.0 * i;
        double den = comp * (comp - 1.0);
        inter *= num / den;
        if (i % 2 == 0)
            result += inter;
        else
            result -= inter;
    }
    return sign * result;
}

double cos_taylor_running_yterms(double x, int y)
{
    int div = (int)(x / CONST_PI);
    x = x - (div * CONST_PI);
    char sign = 1;
    if (div % 2 != 0)
        sign = -1;

    double result = 1.0;
    double inter = 1.0;
    double num = x * x;
    for (int i = 1; i <= y; i++)
    {
        double comp = 2.0 * i;
        double den = comp * (comp - 1.0);
        inter *= num / den;
        if (i % 2 == 0)
            result += inter;
        else
            result -= inter;
    }
    return sign * result;
}

//
// Lookup table.
//

double cos_table_1(double x)
{
    x = absd(x);
    x = modd(x, CONST_2PI);
    return costable_1[(int)(x + 0.5)];
}

double cos_table_0_1(double x)
{
    x = absd(x);
    x = modd(x, CONST_2PI);
    return costable_0_1[(int)(x * 10 + 0.5)];
}


double cos_table_0_01(double x)
{
    x = absd(x);
    x = modd(x, CONST_2PI);
    return costable_0_01[(int)(x * 100 + 0.5)];
}

double cos_table_0_001(double x)
{
    x = absd(x);
    x = modd(x, CONST_2PI);
    return costable_0_001[(int)(x * 1000 + 0.5)];
}

double cos_table_0_0001(double x)
{
    x = absd(x);
    x = modd(x, CONST_2PI);
    return costable_0_0001[(int)(x * 10000 + 0.5)];
}

//
// Lookup table with LERP.
//

double cos_table_1_LERP(double x)
{
    x = absd(x);
    x = modd(x, CONST_2PI);
    double i = x * 1.0;
    int index = (int)i;
    return lerp(i - index,             /* weight      */
                costable_1[index],     /* lower value */
                costable_1[index + 1]  /* upper value */
                );
}

double cos_table_0_1_LERP(double x)
{
    x = absd(x);
    x = modd(x, CONST_2PI);
    double i = x * 10.0;
    int index = (int)i;
    return lerp(i - index,               /* weight      */
                costable_0_1[index],     /* lower value */
                costable_0_1[index + 1]  /* upper value */
                );
}

double cos_table_0_01_LERP(double x)
{
    x = absd(x);
    x = modd(x, CONST_2PI);
    double i = x * 100.0;
    int index = (int)i;
    return lerp(i - index,                /* weight      */
                costable_0_01[index],     /* lower value */
                costable_0_01[index + 1]  /* upper value */
                );
}

double cos_table_0_001_LERP(double x)
{
    x = absd(x);
    x = modd(x, CONST_2PI);
    double i = x * 1000.0;
    int index = (int)i;
    return lerp(i - index,                 /* weight      */
                costable_0_001[index],     /* lower value */
                costable_0_001[index + 1]  /* upper value */
                );
}

double cos_table_0_0001_LERP(double x)
{
    x = absd(x);
    x = modd(x, CONST_2PI);
    double i = x * 10000.0;
    int index = (int)i;
    return lerp(i - index,                  /* weight      */
                costable_0_0001[index],     /* lower value */
                costable_0_0001[index + 1]  /* upper value */
                );
}

double cos_math_h(double x) {
    return cos(x);
}

///
/// Parabola based cos approximations
///
/// Original by Nick for sin can be found at [1]. The cos
/// version here is deduced from `cos(x) = sin(x + pi/2)`.
/// Additionally, the original only accounts for input values in [-pi..pi],
/// making its precision absolutely horrible in the benchmark tests.
///
/// The optimized versions have been deduced by Milian Wolff, see [2].
/// They are quite quick and don't have abysmal precision, giving them
/// a nice position in the middle for both metrics.
///
/// [1]: https://web.archive.org/web/20171228230531/http://forum.devmaster.net/t/fast-and-accurate-sine-cosine/9648
/// [2]: https://stackoverflow.com/a/28050328/35250
///

double cos_parabola(double x)
{
    // cos(x) = sin(x + pi/2)
    x += (CONST_PI / 2.);

    const double B = 4. / CONST_PI;
    const double C = -4. / (CONST_PI * CONST_PI);

    double y = B * x + C * x * fabs(x);

    return y;
}

double cos_parabola_extra(double x)
{
    // cos(x) = sin(x + pi/2)
    x += (CONST_PI / 2.);

    const double B = 4. / CONST_PI;
    const double C = -4. / (CONST_PI * CONST_PI);

    double y = B * x + C * x * fabs(x);

    // const float Q = 0.775;
    const double P = 0.225;

    y = P * (y * fabs(y) - y) + y;   // Q * y + P * y * abs(y)

    return y;
}

double cos_parabola_opt(double x)
{
    const double tp = 1. / CONST_2PI;
    x *= tp;
    x -= .25 + floor(x + .25);
    x *= 16. * (fabs(x) - .5);
    return x;
}

double cos_parabola_extra_opt(double x)
{
    const double tp = 1. / CONST_2PI;
    x *= tp;
    x -= .25 + floor(x + .25);
    x *= 16. * (fabs(x) - .5);
    x += .225 * x * (fabs(x) - 1.);
    return x;
}
