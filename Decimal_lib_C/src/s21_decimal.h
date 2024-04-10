#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H
#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned sign;
  int ext;
  unsigned int bits[8];
} s21_bigdec;

unsigned int get_bit(s21_decimal val, int index);
void set_bit(s21_decimal *dec, int index, int val);
int check_sign(s21_decimal dec);
int int_add_decimal(s21_decimal dec, int a, s21_decimal *res);
int get_scale(s21_decimal dec);
int get_before_scale(s21_decimal dec);
void set_scale(s21_decimal *dec, int val);
void shift_left(s21_decimal *dec);
void shift_right(s21_decimal *dec);
void print_binary(s21_decimal shatohin);
int multiplay_by_ten(s21_decimal dec, s21_decimal *res);
int division_by_ten(s21_decimal dec, s21_decimal *res);
void equalization(int ext_big, int ext_small, s21_decimal *big_ext,
                  s21_decimal *small_ext);
void normalization(s21_decimal *dec_one, s21_decimal *dec_two);
void zeroing_dec(s21_decimal *dec);
void set_zero(s21_decimal *dec);
int check_zero_mantissa(s21_decimal *dec);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_decimal_is_zero(s21_decimal dec);
int s21_is_equal(s21_decimal dec_1, s21_decimal dec_2);
int s21_is_not_equal(s21_decimal dec_1, s21_decimal dec_2);
int s21_is_greater(s21_decimal dec_1, s21_decimal dec_2);
int s21_is_greater_or_equal(s21_decimal dec_1, s21_decimal dec_2);
int s21_is_less(s21_decimal dec_1, s21_decimal dec_2);
int s21_is_less_or_equal(s21_decimal dec_1, s21_decimal dec_2);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);

unsigned get_bit_bigdec(s21_bigdec val, int index);
void set_bit_bigdec(s21_bigdec *dec, int index, int val);
void transf_dec_bigdec(s21_decimal *dec, s21_bigdec *b_dec);
int great_mantissa_bigdec(s21_bigdec val_1, s21_bigdec val_2);
int division_by_ten_bigdec(s21_bigdec dec, s21_bigdec *res);
int multiplay_by_ten_bigdec(s21_bigdec dec, s21_bigdec *res);
int bitwise_summation_bigdec(s21_bigdec val_1, s21_bigdec val_2,
                             s21_bigdec *res);
void normalization_bigdec(s21_bigdec *dec_one, s21_bigdec *dec_two);
int check_bigdec(s21_bigdec dec);
int reduction_bigdec(s21_bigdec *dec);
int transf_bigdec_dec(s21_bigdec *big, s21_decimal *dec);
void shift_left_bigdec(s21_bigdec *dec);
void shift_left_by_num_bigdec(s21_bigdec *dec, int num);
void print_bigdec(s21_bigdec dec);
int take_bit_to_sub(s21_bigdec *val, int i);
int get_higher_bit_bigdec(s21_bigdec value);
void shift_right_bigdec(s21_bigdec *dec);
void shift_right_by_num_bigdec(s21_bigdec *dec, int num);
int is_equal_bigdec(s21_bigdec value_1, s21_bigdec value_2);
void div_with_rem_bigdec(s21_bigdec value_1, s21_bigdec value_2,
                         s21_bigdec *result, s21_bigdec *remainder);

int s21_mul_bigdec(s21_bigdec val_1, s21_bigdec val_2, s21_bigdec *res);
int s21_sub_bigdec(s21_bigdec big, s21_bigdec small, s21_bigdec *res);

#endif
