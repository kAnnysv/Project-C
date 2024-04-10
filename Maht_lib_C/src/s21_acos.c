#include "s21_math.h"

long double s21_acos(double x) {
  long double acos_x = 0;
  if (x == -1) {
    acos_x = s21_PI;
  } else if (x == 1) {
    acos_x = 0.0;
  } else if (x == 0) {
    acos_x = s21_PI / 2;
  } else if (x > 0 && x < 1) {
    acos_x = s21_atan(s21_sqrt(1 - x * x) / x);
  } else if (x > -1 && x < 0) {
    acos_x = s21_PI + s21_atan(s21_sqrt(1 - x * x) / x);
  } else {
    acos_x = s21_NAN;
  }
  return acos_x;
}
