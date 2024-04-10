#include <check.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "s21_math.h"

// ABSOLUTE INT
START_TEST(s21_abs_test) {
  ck_assert_int_eq(s21_abs(0), abs(0));
  ck_assert_int_eq(s21_abs(-20), abs(-20));
  ck_assert_int_eq(s21_abs(1), abs(1));
  ck_assert_int_eq(s21_abs(-1), abs(-1));
  ck_assert_int_eq(s21_abs(2147483647), abs(2147483647));
  ck_assert_int_eq(s21_abs(-2147483648), abs(-2147483648));
  ck_assert_int_eq(s21_abs(2486486484), abs(2486486484));
  ck_assert_int_eq(s21_abs('a'), abs('a'));
  ck_assert_int_eq(s21_abs(-2.5), abs(-2.5));
}
END_TEST

// FABC

START_TEST(s21_fabs_test) {
  ck_assert_double_eq_tol(s21_fabs(2789.678), fabs(2789.678), 0.000001);
  ck_assert_double_eq_tol(s21_fabs(-457.567433), fabs(-457.567433), 0.000001);
  ck_assert_double_eq(s21_fabs(s21_INF), fabs(s21_INF));
  ck_assert_double_eq(s21_fabs(s21_NINF), fabs(s21_NINF));
  ck_assert_double_nan(s21_fabs(s21_NAN));
}
END_TEST

// COS

START_TEST(s21_cos_test) {
  ck_assert_double_eq_tol(s21_cos(0.156), cos(0.156), SMALLEST);
  ck_assert_double_eq_tol(s21_cos(1), cos(1), SMALLEST);
  ck_assert_double_eq_tol(s21_cos(-1), cos(-1), SMALLEST);
  ck_assert_double_nan(s21_cos(s21_NAN));
  ck_assert_double_nan(s21_cos(s21_INF));
  ck_assert_double_nan(s21_cos(s21_NINF));
  ck_assert_double_eq_tol(s21_cos(0), cos(0), SMALLEST);
  ck_assert_double_eq_tol(s21_cos(10), cos(10), SMALLEST);
  ck_assert_double_eq_tol(s21_cos(-10), cos(-10), SMALLEST);
}
END_TEST

// CEIL

START_TEST(s21_ceil_test) {
  ck_assert_double_eq_tol(s21_ceil(-0.5), ceil(-0.5), 0.000001);
  ck_assert_double_eq_tol(s21_ceil(-567.378), ceil(-567.378), 0.000001);
  ck_assert_double_eq_tol(s21_ceil(3.6), ceil(3.6), 0.000001);
  ck_assert_double_nan(s21_ceil(s21_NAN));
  ck_assert_double_infinite(s21_ceil(s21_INF));
  ck_assert_double_infinite(s21_ceil(s21_NINF));
  ck_assert_double_eq_tol(s21_ceil(0), ceil(0), 0.000001);
}
END_TEST

// ACOS

START_TEST(s21_acos_test) {
  ck_assert_double_eq_tol(s21_acos(0), acos(0), 0.000001);
  ck_assert_double_eq_tol(s21_acos(-0.369), acos(-0.369), 0.000001);
  ck_assert_double_eq_tol(s21_acos(-1), acos(-1), 0.000001);
  ck_assert_double_nan(s21_acos(s21_INF));
  ck_assert_double_nan(s21_acos(s21_NAN));
  ck_assert_double_nan(s21_acos(s21_NINF));
  ck_assert_double_eq_tol(s21_acos(1), acos(1), 0.000001);
  ck_assert_double_nan(s21_acos(100500));
  ck_assert_double_eq_tol(s21_acos(0.000001), acos(0.000001), 0.000001);
}
END_TEST

// ASIN
START_TEST(s21_asin_test) {
  ck_assert_double_eq_tol(s21_asin(0.156), asin(0.156), 0.000001);
  ck_assert_double_eq_tol(s21_asin(1), asin(1), 0.000001);
  ck_assert_double_eq_tol(s21_asin(-1), asin(-1), 0.000001);
  ck_assert_double_nan(s21_asin(s21_NAN));
  ck_assert_double_nan(s21_asin(s21_INF));
  ck_assert_double_nan(s21_asin(s21_NINF));
  ck_assert_double_eq_tol(s21_asin(0), asin(0), 0.000001);
  ck_assert_double_nan(s21_asin(100500));
}
END_TEST

// ATAN

START_TEST(s21_atan_test) {
  ck_assert_double_eq_tol(s21_atan(0.156), atan(0.156), 0.000001);
  ck_assert_double_eq_tol(s21_atan(-0.467), atan(-0.467), 0.000001);
  ck_assert_double_eq_tol(s21_atan(0), atan(0), 0.000001);
  ck_assert_double_eq_tol(s21_atan(100500), atan(100500), 0.000001);
  ck_assert_double_eq_tol(s21_atan(-100500), atan(-100500), 0.000001);
  ck_assert_double_eq_tol(s21_atan(1), atan(1), 0.000001);
  ck_assert_double_eq_tol(s21_atan(-1), atan(-1), 0.000001);
  ck_assert_double_eq_tol(s21_atan(s21_INF), atan(s21_INF), 0.000001);
  ck_assert_double_eq_tol(s21_atan(s21_NINF), atan(s21_NINF), 0.000001);
  ck_assert_double_nan(s21_atan(s21_NAN));
}
// POW

START_TEST(s21_pow_test) {
  long double result_s21_pow = 0.;
  double result_pow = 0.;
  double base = 1, exp = 1;

  for (int i = 0; i < 20; i++, base += 0.5, exp += 0.5) {
    result_s21_pow = s21_pow(base, exp);
    result_pow = pow(base, exp);
    ck_assert_ldouble_eq_tol(result_s21_pow, result_pow, S21_EPS);
  }

  ck_assert_ldouble_eq_tol(s21_pow(1, s21_NAN), pow(1, s21_NAN), S21_EPS);
  ck_assert_ldouble_eq_tol(s21_pow(-10, 3), pow(-10, 3), S21_EPS);
  ck_assert_ldouble_eq_tol(s21_pow(-10, 2), pow(-10, 2), S21_EPS);
  ck_assert_ldouble_nan(s21_pow(-1, -2.123));
  ck_assert_ldouble_nan(s21_pow(-1, 2.123));
  ck_assert_ldouble_eq_tol(s21_pow(10, 1), pow(10, 1), S21_EPS);
  ck_assert_ldouble_eq_tol(s21_pow(10, -1), pow(10, -1), S21_EPS);
  ck_assert_ldouble_eq_tol(s21_pow(10, 0), pow(10, 0), S21_EPS);
  ck_assert_ldouble_eq(s21_pow(s21_NINF, s21_NINF), pow(s21_NINF, s21_NINF));
  ck_assert_ldouble_eq(s21_pow(s21_NINF, s21_INF), pow(s21_NINF, s21_INF));
}
END_TEST

// LOG
START_TEST(s21_log_test) {
  ck_assert_ldouble_eq_tol(log(1), s21_log(1), S21_EPS);
  ck_assert_ldouble_eq_tol(log(0.1), s21_log(0.1), S21_EPS);
  ck_assert_ldouble_eq_tol(log(0.00001), s21_log(0.00001), S21_EPS);
  ck_assert_ldouble_eq_tol(log(S21_EPS), s21_log(S21_EPS), S21_EPS);
  ck_assert_ldouble_eq_tol(log(0.4), s21_log(0.4), S21_EPS);
  ck_assert_ldouble_eq_tol(log(100), s21_log(100), S21_EPS);
  ck_assert_ldouble_eq_tol(log(100000), s21_log(100000), S21_EPS);
  ck_assert_ldouble_eq_tol(log(1e100), s21_log(1e100), S21_EPS);
  ck_assert_ldouble_eq_tol(log(0.001), s21_log(0.001), S21_EPS);
  ck_assert_ldouble_nan(s21_log(-1));
  ck_assert_ldouble_infinite(s21_log(s21_INF));
  ck_assert_ldouble_infinite(s21_log(0));
  ck_assert_ldouble_nan(s21_log(s21_NINF));
  ck_assert_ldouble_nan(log(s21_NINF));
  ck_assert_ldouble_nan(s21_log(s21_NAN));
}
END_TEST

// SQRT
START_TEST(s21_sqrt_test) {
  for (double i = 0.; i <= 20.; i += 0.5) {
    ck_assert_ldouble_eq_tol(s21_sqrt(i), sqrt(i), S21_EPS);
  }

  ck_assert_ldouble_nan(s21_sqrt(s21_NINF));
  ck_assert_ldouble_infinite(s21_sqrt(s21_INF));
  ck_assert_ldouble_nan(s21_sqrt(s21_NAN));
  ck_assert_ldouble_nan(s21_sqrt(-10));
}
END_TEST

// TANGENT
START_TEST(s21_tan_test) {
  ck_assert_double_eq_tol(s21_tan(0.156), tan(0.156), SMALLEST);
  ck_assert_double_eq_tol(s21_tan(1), tan(1), SMALLEST);
  ck_assert_double_eq_tol(s21_tan(-1), tan(-1), SMALLEST);
  ck_assert_double_nan(s21_tan(s21_NAN));
  ck_assert_double_nan(s21_tan(s21_INF));
  ck_assert_double_nan(s21_tan(s21_NINF));
  ck_assert_double_eq_tol(s21_tan(0), tan(0), SMALLEST);
  ck_assert_double_eq_tol(s21_tan(2 * M_PI), tan(2 * M_PI), SMALLEST);
  ck_assert_double_eq_tol(s21_tan(10), tan(10), SMALLEST);
  ck_assert_double_eq_tol(s21_tan(-10), tan(-10), SMALLEST);
}
END_TEST

// SINE
START_TEST(s21_sin_test) {
  ck_assert_double_eq_tol(s21_sin(0.156), sin(0.156), SMALLEST);
  ck_assert_double_eq_tol(s21_sin(1), sin(1), SMALLEST);
  ck_assert_double_eq_tol(s21_sin(-1), sin(-1), SMALLEST);
  ck_assert_double_nan(s21_sin(s21_NAN));
  ck_assert_double_nan(s21_sin(s21_INF));
  ck_assert_double_nan(s21_sin(s21_NINF));
  ck_assert_double_eq_tol(s21_sin(0), sin(0), SMALLEST);
  ck_assert_double_eq_tol(s21_sin(10), sin(10), SMALLEST);
  ck_assert_double_eq_tol(s21_sin(-10), sin(-10), SMALLEST);
  ck_assert_double_eq_tol(s21_sin(1000000), sin(1000000), SMALLEST);
  ck_assert_double_eq_tol(s21_sin(-1000000), sin(-1000000), SMALLEST);
}
END_TEST

// FMOD
START_TEST(s21_fmod_test) {
  ck_assert_ldouble_eq_tol(s21_fmod(2.34, 2.0), fmod(2.34, 2.0), S21_EPS);
  ck_assert_ldouble_eq_tol(s21_fmod(-2.34, 2.0), fmod(-2.34, 2.0), S21_EPS);
  ck_assert_ldouble_eq_tol(s21_fmod(2.34, -2.0), fmod(2.34, -2.0), S21_EPS);
  ck_assert_ldouble_eq_tol(s21_fmod(-2.34, -2.0), fmod(-2.34, -2.0), S21_EPS);
  ck_assert_ldouble_eq_tol(s21_fmod(3, 21.21), fmod(3, 21.21), S21_EPS);
  ck_assert_ldouble_eq_tol(s21_fmod(3, -21.21), fmod(3, -21.21), S21_EPS);
  ck_assert_ldouble_eq_tol(s21_fmod(-9, -100500), fmod(-9, -100500), S21_EPS);
  ck_assert_ldouble_eq_tol(s21_fmod(-9, -9), fmod(-9, -9), S21_EPS);
  ck_assert_ldouble_eq_tol(s21_fmod(1e+10, 9), fmod(1e+10, 9), S21_EPS);
  ck_assert_ldouble_eq_tol(s21_fmod(1e+15, 9), fmod(1e+15, 9), S21_EPS);
  ck_assert_ldouble_eq_tol(s21_fmod(1e+15, s21_INF), fmod(1e+15, s21_INF),
                           s21_EPS);
  ck_assert_ldouble_nan(s21_fmod(s21_INF, s21_INF));
  ck_assert_ldouble_nan(fmod(s21_INF, s21_INF));
  ck_assert_ldouble_nan(s21_fmod(s21_NAN, s21_NAN));
  ck_assert_ldouble_nan(fmod(s21_NAN, s21_NAN));
  ck_assert_ldouble_nan(s21_fmod(2.45, 0));
  ck_assert_ldouble_nan(fmod(2.45, 0));
  ck_assert_ldouble_nan(s21_fmod(0, 0));
  ck_assert_ldouble_nan(fmod(0, 0));
  ck_assert_ldouble_nan(s21_fmod(s21_INF, 0));
  ck_assert_ldouble_nan(fmod(s21_INF, 0));
  ck_assert_ldouble_nan(s21_fmod(s21_INF, s21_NINF));
}
END_TEST

// FLOOR
START_TEST(s21_floor_test) {
  ck_assert_double_eq_tol(s21_floor(-0.8), floor(-0.8), 0.000001);
  ck_assert_double_eq_tol(s21_floor(0.8), floor(0.8), 0.000001);
  ck_assert_double_eq_tol(s21_floor(-10.23), floor(-10.23), 0.000001);
  ck_assert_double_eq(s21_floor(s21_INF), floor(s21_INF));
  ck_assert_double_nan(s21_floor(NAN));
  ck_assert_double_eq(s21_floor(s21_NINF), floor(s21_NINF));
  ck_assert_double_eq_tol(s21_floor(-1200), floor(-1200), 0.000001);
}
END_TEST

// EXP
START_TEST(s21_exp_test) {
  ck_assert_ldouble_eq_tol(exp(1), s21_exp(1), S21_EPS);
  ck_assert_ldouble_eq_tol(exp(0), s21_exp(0), S21_EPS);
  ck_assert_ldouble_eq_tol(exp(0.1), s21_exp(0.1), S21_EPS);
  ck_assert_ldouble_eq_tol(exp(25), (double)s21_exp(25), S21_EPS);
  ck_assert_ldouble_eq_tol(exp(-1), s21_exp(-1), S21_EPS);
  ck_assert_ldouble_eq_tol(exp(-800), s21_exp(-800), S21_EPS);
  ck_assert_ldouble_eq_tol(exp(32), (double)s21_exp(32), S21_EPS);
  ck_assert_ldouble_eq_tol(exp(-'N'), s21_exp(-'N'), S21_EPS);
  ck_assert_ldouble_eq_tol(exp(-0.1), s21_exp(-0.1), S21_EPS);
  ck_assert_ldouble_eq_tol(exp(-37), s21_exp(-37), S21_EPS);
  ck_assert_ldouble_eq_tol(exp(-s21_INF), s21_exp(-s21_INF), S21_EPS);
  ck_assert_ldouble_nan(s21_exp(s21_NAN));
  ck_assert_ldouble_infinite(s21_exp(s21_INF));
  ck_assert_ldouble_eq_tol(s21_exp(s21_NINF), exp(s21_NINF), 0.0000001);
}
END_TEST

Suite *exp_suite() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("exp(x)");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_exp_test);
  suite_add_tcase(s, tc_core);
  return s;
}

Suite *floor_suite() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("floor(x)");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_floor_test);
  suite_add_tcase(s, tc_core);
  return s;
}

Suite *fmod_suite() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("fmod(x)");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_fmod_test);
  suite_add_tcase(s, tc_core);
  return s;
}

Suite *abs_suite() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("abs(x)");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_abs_test);
  suite_add_tcase(s, tc_core);
  return s;
}

Suite *sin_suite() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("sin(x)");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_sin_test);
  suite_add_tcase(s, tc_core);
  return s;
}

Suite *tan_suite() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("tan(x)");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_tan_test);
  suite_add_tcase(s, tc_core);
  return s;
}

Suite *sqrt_suite() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("sqrt(x)");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_sqrt_test);
  suite_add_tcase(s, tc_core);
  return s;
}

Suite *log_suite() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("log(x)");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_log_test);
  suite_add_tcase(s, tc_core);
  return s;
}

Suite *cos_suite() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("cos(x)");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_cos_test);
  suite_add_tcase(s, tc_core);
  return s;
}

Suite *atan_suite() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("atan(x)");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_atan_test);
  suite_add_tcase(s, tc_core);
  return s;
}

Suite *asin_suite() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("asin(x)");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_asin_test);
  suite_add_tcase(s, tc_core);
  return s;
}

Suite *acos_suite() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("acos(x)");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_acos_test);
  suite_add_tcase(s, tc_core);
  return s;
}

Suite *fabs_suite() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("fabs(x)");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_fabs_test);
  suite_add_tcase(s, tc_core);
  return s;
}

Suite *ceil_suite() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("ceil(x)");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_ceil_test);
  suite_add_tcase(s, tc_core);
  return s;
}

Suite *pow_suite() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("pow(x)");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_pow_test);
  suite_add_tcase(s, tc_core);
  return s;
}

void case_test(Suite *s, int *fail) {
  SRunner *runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  *fail = srunner_ntests_failed(runner);
  srunner_free(runner);
}

int main() {
  int fail = 0;

  case_test(fabs_suite(), &fail);
  case_test(ceil_suite(), &fail);
  case_test(pow_suite(), &fail);
  case_test(acos_suite(), &fail);
  case_test(asin_suite(), &fail);
  case_test(atan_suite(), &fail);
  case_test(cos_suite(), &fail);
  case_test(log_suite(), &fail);
  case_test(sqrt_suite(), &fail);
  case_test(tan_suite(), &fail);
  case_test(sin_suite(), &fail);
  case_test(abs_suite(), &fail);
  case_test(fmod_suite(), &fail);
  case_test(floor_suite(), &fail);
  case_test(exp_suite(), &fail);
  return fail;
}