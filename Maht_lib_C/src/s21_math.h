#ifndef S21_MATH_
#define S21_MATH_
#include <limits.h>

#define s21_EPS 2.220446049250313e-16
#define s21_E 2.7182818284590452
#define s21_PI 3.1415926535897932384626433832795
#define s21_INF 1.0 / 0.0
#define s21_NINF -s21_INF
#define s21_NAN __builtin_nanf("0x7fc00000")
#define s21_DBL_MAX 1.7976931348623158e+308
#define S21_EPS 1e+17
#define SMALLEST 0.000001
#define s21_isnan(x) __builtin_isnan(x)
#define s21_isinf(x) __builtin_isinf(x)

long double s21_fabs(double number);
int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_pow(double base, double exp);
long double s21_cos(double angle);
long double s21_log(double x);
long double s21_sqrt(double x);
long double s21_fmod(double x, double y);
long double s21_tan(double angle);
long double s21_sin(double angle);
long double s21_floor(double x);
long double s21_exp(double x);

#endif