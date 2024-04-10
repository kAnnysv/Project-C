#include "s21_math.h"

long double s21_exp(double x) {
  long double result = 0;
  long double current = 1;
  int flag = 0;
  int count = 1;

  if (x < 0) {
    flag = 1;
    x = x * (-1);
  } else if (x == -1)
    x = 1;

  while ((current > s21_EPS)) {
    // printf("is x %f\n", x);
    if (x == s21_INF) {
      // printf("test1\n");
      result = s21_INF;
      break;
    }
    if (s21_isnan(x)) {
      // printf("test2\n");
      result = s21_NAN;
      break;
    }
    result = result + current;
    current = current * (x / count);

    count++;
    // printf("%d\n", count);
    if (count == 376) {
      result = s21_INF;
      break;
    }
  }
  if (flag) {
    result = 1 / result;
  }

  return result;
}
