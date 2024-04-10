#include "s21_math.h"

long double s21_fmod(double x, double y) {
  long double result;
  int flag = 0;
  if ((x == s21_INF) && (y == s21_INF)) flag = 1;
  int n = x / y;

  if ((y == 0) || (x == s21_NAN)) {
    // printf("test\n");
    result = s21_NAN;
  } else if ((y == s21_INF)) {
    if (x) {
      result = x;
    } else
      result = s21_NAN;
  }

  else if ((y == s21_INF)) {
    if (x == s21_INF) result = s21_NAN;
  }

  else {
    if ((x == s21_INF) || (y == s21_INF)) {
      result = s21_NAN;
    } else {
      // printf("test last else\n");
      result = x - n * y;
    }
  }
  if (flag) result = s21_NAN;
  return result;
}
