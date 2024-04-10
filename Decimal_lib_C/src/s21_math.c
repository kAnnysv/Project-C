#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  // int sign = 0;
  zeroing_dec(result);
  s21_bigdec big_value_1 = {0};
  s21_bigdec big_value_2 = {0};
  s21_bigdec big_result = {0};
  transf_dec_bigdec(&value_1, &big_value_1);
  transf_dec_bigdec(&value_2, &big_value_2);
  normalization_bigdec(&big_value_1, &big_value_2);
  big_result.ext = big_value_1.ext;
  if (big_value_1.sign == big_value_2.sign) {
    // sign = big_value_1.sign;
    bitwise_summation_bigdec(big_value_1, big_value_2, &big_result);
    big_result.sign = big_value_1.sign;
  } else if (great_mantissa_bigdec(big_value_1, big_value_2)) {
    // sign = big_value_1.sign;
    s21_sub_bigdec(big_value_1, big_value_2, &big_result);
    big_result.sign = big_value_1.sign;
  } else if (great_mantissa_bigdec(big_value_2, big_value_1)) {
    // sign = big_value_2.sign;
    s21_sub_bigdec(big_value_2, big_value_1, &big_result);
    big_result.sign = big_value_2.sign;
  }
  flag = transf_bigdec_dec(&big_result, result);
  if (flag && big_result.sign) flag += 1;
  return flag;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  s21_negate(value_2, &value_2);
  flag = s21_add(value_1, value_2, result);
  if (s21_decimal_is_zero(*result)) {
    result->bits[3] = 0;
  }
  return flag;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  zeroing_dec(result);
  s21_bigdec big_value_1 = {0};
  s21_bigdec big_value_2 = {0};
  s21_bigdec big_result = {0};
  transf_dec_bigdec(&value_1, &big_value_1);
  transf_dec_bigdec(&value_2, &big_value_2);
  normalization_bigdec(&big_value_1, &big_value_2);
  big_result.ext = big_value_1.ext;
  s21_mul_bigdec(big_value_1, big_value_2, &big_result);
  big_result.ext *= 2;
  if (big_value_1.sign == big_value_2.sign)
    big_result.sign = 0;
  else if (big_value_1.sign != big_value_2.sign)
    big_result.sign = 1;
  flag = transf_bigdec_dec(&big_result, result);
  if (flag && big_result.sign) flag += 1;
  return flag;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = 0;
  int exp = 0;
  zeroing_dec(result);
  s21_bigdec big_value_1 = {0};
  s21_bigdec big_value_2 = {0};
  s21_bigdec null_big = {0};
  s21_bigdec big_result = {0};
  s21_bigdec remainder = {0};
  transf_dec_bigdec(&value_1, &big_value_1);
  transf_dec_bigdec(&value_2, &big_value_2);
  big_result.sign = big_value_1.sign ^ big_value_2.sign;
  if (is_equal_bigdec(big_value_2, null_big)) {
    code = 3;
  } else if (!is_equal_bigdec(big_value_1, null_big)) {
    normalization_bigdec(&big_value_1, &big_value_2);
    div_with_rem_bigdec(big_value_1, big_value_2, &big_value_1, &remainder);
    while (great_mantissa_bigdec(remainder, null_big) ||
           great_mantissa_bigdec(big_value_1, null_big)) {
      exp++;
      multiplay_by_ten_bigdec(big_result, &big_result);
      multiplay_by_ten_bigdec(remainder, &remainder);
      bitwise_summation_bigdec(big_result, big_value_1, &big_result);
      if (get_higher_bit_bigdec(big_result) > 95) {
        break;
      }
      div_with_rem_bigdec(remainder, big_value_2, &big_value_1, &remainder);
    }
  }
  while ((get_higher_bit_bigdec(big_result) > 95) && exp > 0) {
    division_by_ten_bigdec(big_result, &big_result);
    exp--;
  }
  big_result.ext = exp - 1;
  if (big_result.ext > 28) {
    division_by_ten_bigdec(big_result, &big_result);
  }
  transf_bigdec_dec(&big_result, result);
  return code;
}