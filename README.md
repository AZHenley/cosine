# Cosine

Various methods of calculating cosine without math.h.

See the explanation and benchmarks at [http://austinhenley.com/blog/cosine.html](http://austinhenley.com/blog/cosine.html)

*For educational purposes only :)*

# BUILDING

```
clang -O3 -mavx benchmarks.c -o benchmarks -lm
./benchmarks -h
Usage: ./benchmarks [-na] [-nt] [-t <testname>]
   -na - Don't run accuracy tests
   -nt - Don't run speed tests.
   -t <testname> - Run a particular test instead of all tests.
   -p - Print all test names.
```

# TESTS

There are four types of tests:
* Taylor series with literal values
* Taylor series with running values
* Table lookup with clamp to nearest
* Table lookup with linear interpolation (LERP)

Table tests have the following properties
* cos_table_1 - a cosine table with 1 value per radian
* cos_table_0_1 - a cosine table with 10 values per radian
* cos_table_0_01 - a cosine table with 100 values per radian
* cos_table_0_001 - a cosine table with 1000 values per radian
* cos_table_0_0001 - a cosine table with 10,000 values per radian

```
cos_taylor_literal_4terms_naive
cos_taylor_literal_6terms_naive
cos_taylor_literal_6terms_2pi
cos_taylor_literal_6terms_pi
cos_taylor_literal_6terms
cos_taylor_literal_10terms
cos_taylor_running_6terms
cos_taylor_running_8terms
cos_taylor_running_10terms
cos_taylor_running_16terms
cos_table_1
cos_table_0_1
cos_table_0_01
cos_table_0_001
cos_table_0_0001
cos_table_1_LERP
cos_table_0_1_LERP
cos_table_0_01_LERP
cos_table_0_001_LERP
cos_table_0_0001_LERP
cos_math_h
```

You can run a particular test by using the `-t` switch:
```
./benchmarks -t cos_table_1_LERP
ACCURACY
cos_table_1_LERP                    0.1147496616359112

TIME
cos_table_1_LERP                    1.3534999999999999
```

Or run all tests with no arguments.
```
./benchmarks
Cosine benchmark

ACCURACY
cos_taylor_literal_4terms_naive     19.9880092736029695
cos_taylor_literal_6terms_naive     1.4652889617438571
cos_taylor_literal_6terms_2pi       1.4652889617438571
cos_taylor_literal_6terms_pi        0.0001004702941281
cos_taylor_literal_6terms           0.0001004702941279
cos_taylor_literal_10terms          0.0000000000756514
cos_taylor_running_6terms           0.0001004702941287
cos_taylor_running_8terms           0.0000001352604422
cos_taylor_running_10terms          0.0000000000756513
cos_taylor_running_16terms          0.0000000000000009
cos_table_1                         0.4944578886434219
cos_table_0_1                       0.0499943500331001
cos_table_0_01                      0.0049999938268771
cos_table_0_001                     0.0004999999109268
cos_table_0_0001                    0.0000499999164148
cos_table_1_LERP                    0.1147496616359112
cos_table_0_1_LERP                  0.0012496954434600
cos_table_0_01_LERP                 0.0000124999013960
cos_table_0_001_LERP                0.0000001249999969
cos_table_0_0001_LERP               0.0000000012500020
cos_math_h                          0.0000000000000000

TIME
cos_taylor_literal_4terms_naive     1.2767610000000000
cos_taylor_literal_6terms_naive     1.8665570000000000
cos_taylor_literal_6terms_2pi       2.7213579999999999
cos_taylor_literal_6terms_pi        3.0191659999999998
cos_taylor_literal_6terms           2.7813910000000002
cos_taylor_literal_10terms          4.3346099999999996
cos_taylor_running_6terms           2.7858489999999998
cos_taylor_running_8terms           3.6085900000000000
cos_taylor_running_10terms          4.5931400000000000
cos_taylor_running_16terms          6.5223639999999996
cos_table_1                         0.9697160000000000
cos_table_0_1                       1.0025700000000000
cos_table_0_01                      1.0026360000000001
cos_table_0_001                     1.0028140000000001
cos_table_0_0001                    1.0027860000000000
cos_table_1_LERP                    1.3534610000000000
cos_table_0_1_LERP                  1.4333030000000000
cos_table_0_01_LERP                 1.4268099999999999
cos_table_0_001_LERP                1.4344870000000001
cos_table_0_0001_LERP               1.4317990000000000
cos_math_h                          3.3061980000000002


Done
```

Your results will differ.
