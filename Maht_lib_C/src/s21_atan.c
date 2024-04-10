#include "s21_math.h"

long double s21_atan(double x) {
  long double atan_x = 0;
  if (x == 1) {
    atan_x = s21_PI / 4.0;
  } else if (x == -1) {
    atan_x = -s21_PI / 4.0;
  } else if (x == 0) {
    atan_x = 0;
  } else if (x >= -1 && x <= 1) {
    for (int i = 1; i < 5000; i++) {
      atan_x += (s21_pow(-1.0, (i - 1.0)) * s21_pow(x, 2.0 * i - 1.0)) /
                (2.0 * i - 1.0);
    }
  } else if (x < -1 || x > 1) {
    double l = s21_fabs(x);
    for (int i = 1; i < 5000; i++) {
      atan_x += (s21_pow(-1.0, (i - 1.0)) * s21_pow(1.0 / l, 2.0 * i - 1.0)) /
                (2.0 * i - 1.0);
    }
    atan_x = (s21_PI / 2.0) - atan_x;
    if (x < 0) {
      atan_x = -atan_x;
    }
  } else {
    atan_x = s21_NAN;
  }
  return atan_x;
}
