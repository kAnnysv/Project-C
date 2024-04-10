
#include "s21_math.h"

long double s21_log(double x) {
  int ex_pow = 0;
  double result = 0;
  double compare = 0;

  if (x == 0.0) {
    result = s21_NINF;
  } else if (x == s21_NINF) {
    result = s21_NAN;
  } else if (x == s21_INF) {
    result = s21_INF;
  } else if (x > 0) {
    for (; x >= s21_E; x /= s21_E, ex_pow++) continue;
    for (int i = 0; i < 100; i++) {
      compare = result;
      result = compare + 2 * (x - s21_exp(compare)) / (x + s21_exp(compare));
    }
  } else {
    result = s21_NAN;
  }
  return (result + ex_pow);
}
