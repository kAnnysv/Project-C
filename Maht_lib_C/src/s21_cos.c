#include "s21_math.h"

long double check_angle(double angle) {
  if (s21_fabs(angle) > 2 * s21_PI) {
    int sign = 1;
    if (angle < 0) {
      sign = -1;
    }
    long long int minus = angle / (2 * s21_PI);
    angle -= (minus - 1 * sign) * 2 * s21_PI;
  }

  return angle;
}

long double s21_cos(double angle) {
  if (angle == s21_INF || angle == s21_NINF) return s21_NAN;
  angle = check_angle(angle);

  long double ans = 1;
  int i = 2;
  long double fact = 1;
  int sign = -1;
  long double power = angle * angle;
  long double prev_ans = ans - 1;
  long double temp = 10;
  while (((temp > 0 && temp >= SMALLEST) || (temp < 0 && temp <= SMALLEST)) &&
         ans != prev_ans) {
    prev_ans = ans;
    fact *= i * (i - 1);
    temp = power / fact;
    ans += sign * temp;
    i += 2;
    power *= angle * angle;
    sign = sign == 1 ? -1 : 1;
  }
  return ans;
}
