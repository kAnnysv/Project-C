#include "s21_math.h"

long double s21_floor(double x) {
  long double floor_x = (long long int)x;
  if (x == s21_INF) {
    floor_x = s21_INF;
  } else if (x == s21_NINF) {
    floor_x = s21_NINF;
  } else if (s21_isnan(x)) {
    floor_x = s21_NAN;
  } else if (s21_fabs(x) > 0.0 && x != floor_x) {
    if (x < 0) {
      floor_x -= 1;
    }
  }
  return floor_x;
}
