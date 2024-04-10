#include "s21_math.h"

long double s21_asin(double x) {
  long double asin_x = 0;
  if (x >= -1 && x <= 1) {
    asin_x = s21_atan(x / s21_sqrt(1 - x * x));
  } else {
    asin_x = s21_NAN;
  }
  return asin_x;
}