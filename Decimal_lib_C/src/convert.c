#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  *dst = (s21_decimal){0};
  dst->bits[0] = abs(src);

  if (src < 0) {
    set_bit(dst, 127, 1);
  }

  return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int err = 0;
  int res = 0;
  int sign = get_bit(src, 127);
  s21_truncate(src, &src);
  if (src.bits[1] != 0 || src.bits[2] != 0) {
    err = 1;
  } else {
    res = src.bits[0];
    if (sign) res = res * -1;
    *dst = res;
  }
  return err;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int err = 0;
  double res = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 32; j++) {
      if (i == 0 && j == 0) {
        res += (double)(src.bits[i] & 1);
      } else {
        res += pow((src.bits[i] >> j & 1) * 2, j + i * 32);
      }
    }
  }
  for (int i = get_scale(src); i > 0; i--) {
    res /= 10;
  }
  if (get_bit(src, 127)) res *= -1;
  *dst = (float)res;
  return err;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int err = 0;
  set_zero(dst);
  char float_str[100] = {0};
  sprintf(float_str, "%+.7e", src);
  int mant = 0;
  int i = 0;
  int is_scale = 0;
  int scale_sign = 1;
  int scale = 0;
  while (float_str[i]) {
    if (isdigit(float_str[i])) {
      if (!is_scale) {
        mant *= 10;
        mant += float_str[i] - '0';
      } else {
        scale *= 10;
        scale += float_str[i] - '0';
      }
    } else if (float_str[i] == 'e') {
      is_scale = 1;
      if (float_str[i + 1] == '-') {
        scale_sign = -1;
      }
    }
    i++;
  }

  scale *= scale_sign;
  scale -= 7;
  while (mant != 0 && scale < -28) {
    int rem = mant % 10;
    mant /= 10;
    if (rem >= 5) {
      mant++;
    }
    scale++;
  }
  if (scale < -28) {
    err = 1;
  }
  if (!(mant % 10)) {
    mant /= 10;
    scale++;
  }
  dst->bits[0] = mant;
  s21_decimal ten = {{10, 0, 0, 0}};
  while (scale > 0 && !err) {
    err = s21_mul(*dst, ten, dst);
    scale--;
  }
  if (err) {
    set_zero(dst);
  } else {
    if (!s21_decimal_is_zero(*dst)) {
      set_scale(dst, abs(scale));
    }
    if (float_str[0] == '-') {
      s21_negate(*dst, dst);
    }
  }
  return err;
}
