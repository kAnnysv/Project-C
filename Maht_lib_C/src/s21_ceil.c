#include "s21_math.h"

long double s21_ceil(double x) {
  long double ceil_x = (long long int)x;
  if (x == s21_INF) {
    ceil_x = s21_INF;
  } else if (x == s21_NINF) {
    ceil_x = s21_NINF;
  } else if (s21_isnan(x)) {
    ceil_x = s21_NAN;
  } else if (s21_fabs(x) > 0.0 && x != ceil_x) {
    if (x > 0.0) {
      ceil_x += 1;
    }
  }
  return ceil_x;
}