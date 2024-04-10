#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  uint64_t rem = 0;
  uint64_t num = 0;
  int scale = get_scale(value);

  while (scale > 0) {
    for (int i = 2; i > -1; i--) {
      num = value.bits[i];
      num += rem << 32;
      rem = num % 10;
      num /= 10;
      value.bits[i] = num;
    }
    scale--;
    rem = 0;
    num = 0;
  }
  set_scale(&value, 0);
  *result = value;

  return 0;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  value.bits[3] = value.bits[3] ^ ((unsigned int)1 << 31);
  *result = value;
  return 0;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_decimal trunc_val = {0};
  s21_decimal fraction = {0};
  s21_decimal zero_dec = {0};
  s21_truncate(value, &trunc_val);
  s21_sub(value, trunc_val, &fraction);
  if (value.bits[3] >> 31) {
    s21_negate(fraction, &fraction);
    if (!s21_is_greater(fraction, zero_dec)) {
      int_add_decimal(trunc_val, -1, &trunc_val);
    }
  }
  *result = trunc_val;
  return 0;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_decimal five = {{5, 0, 0, 0}};
  s21_decimal trunc_val = {0};
  s21_decimal fraction = {0};
  set_scale(&five, 1);
  s21_truncate(value, &trunc_val);
  s21_sub(value, trunc_val, &fraction);
  if (check_sign(value)) {
    s21_negate(fraction, &fraction);
    if (s21_is_greater_or_equal(fraction, five)) {
      int_add_decimal(trunc_val, -1, &trunc_val);
    }
  } else {
    if (s21_is_greater(fraction, five)) {
      int_add_decimal(trunc_val, 1, &trunc_val);
    }
  }

  *result = trunc_val;
  return 0;
}
