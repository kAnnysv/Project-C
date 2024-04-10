#include "s21_math.h"

long double s21_pow(double base, double exp) {
  long double result = 0;
  long double basecpy = base;
  if ((basecpy == -1 && exp == s21_INF) || (basecpy == 1 && s21_isnan(exp)) ||
      (basecpy == 1 && exp == s21_NINF) || (basecpy == s21_NAN && exp == 0) ||
      (basecpy == -1 && exp == s21_NINF) || (basecpy == 1 && exp == s21_INF) ||
      (basecpy == 1 && exp == 1) || (exp == 0) || (basecpy == 1 && exp == -1)) {
    result = 1;
  } else if ((s21_isnan(basecpy) && s21_isnan(exp)) ||
             (basecpy == -1 && exp < -1) ||
             (s21_isnan(basecpy) && exp == s21_INF) ||
             (s21_isnan(basecpy) && exp == s21_NINF) ||
             (s21_isnan(basecpy) && exp > 1)) {
    result = s21_NAN;
  } else if ((basecpy == s21_NINF && exp == s21_INF) ||
             (basecpy == s21_NINF && exp > 1)) {
    result = s21_INF;
  } else if ((basecpy == 0 && s21_isinf(exp)) ||
             (basecpy == s21_NINF && exp == s21_NINF)) {
    result = 0;
  } else if (basecpy < 0) {
    basecpy = -basecpy;
    result = s21_exp(exp * s21_log(basecpy));
    if (s21_fmod(exp, 2) != 0) {
      result = -result;
    }
    if (((long long int)exp < exp) || ((long long int)exp > exp)) {
      result = s21_NAN;
    }
  } else if (basecpy > 0) {
    result = s21_exp(exp * s21_log(basecpy));
  }
  return result;
}
