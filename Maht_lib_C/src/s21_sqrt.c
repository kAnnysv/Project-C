#include "s21_math.h"

long double s21_fmax(double x, double y) {
  long double max = 0;
  if (y > x) {
    max = y;
  } else {
    max = x;
  }
  return max;
}

long double s21_sqrt(double x) {
  if (x > 0) {
    long double left = 0;
    long double right = s21_fmax(1, x);
    long double mid;

    mid = (left + right) / 2;

    while ((mid - left) > s21_EPS) {
      if (mid * mid > x) {
        right = mid;
      } else {
        left = mid;
      }
      mid = (left + right) / 2;
    }
    x = mid;
  } else if (x == 0) {
    x = 0;
  } else {
    x = s21_NAN;
  }
  return x;
}
