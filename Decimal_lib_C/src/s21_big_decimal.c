#include "s21_decimal.h"

int bitwise_summation_bigdec(s21_bigdec val_1, s21_bigdec val_2,
                             s21_bigdec *res) {
  int transfer = 0;
  unsigned sum = 0;
  for (int i = 0; i < 256; i++) {
    sum = get_bit_bigdec(val_1, i) + get_bit_bigdec(val_2, i) + transfer;
    if (!sum) {
      set_bit_bigdec(res, i, 0);
      transfer = 0;
    } else if (sum == 1) {
      set_bit_bigdec(res, i, 1);
      transfer = 0;
    } else if (sum == 2) {
      set_bit_bigdec(res, i, 0);
      transfer = 1;
    } else if (sum == 3) {
      set_bit_bigdec(res, i, 1);
      transfer = 1;
    }
  }
  return 0;
}

int s21_sub_bigdec(s21_bigdec big, s21_bigdec small, s21_bigdec *res) {
  unsigned byte_big = 0;
  unsigned byte_small = 0;
  for (int i = 0; i < 256; i++) {
    byte_big = get_bit_bigdec(big, i);
    byte_small = get_bit_bigdec(small, i);
    if (byte_big == 0 && byte_small == 1) {
      take_bit_to_sub(&big, i);
      set_bit_bigdec(res, i, 1);
    } else {
      set_bit_bigdec(res, i, byte_big - byte_small);
    }
  }
  return 0;
}

int s21_mul_bigdec(s21_bigdec val_1, s21_bigdec val_2, s21_bigdec *res) {
  s21_bigdec tmp = {0};
  tmp.ext = val_1.ext;
  for (int i = 0; i < 256; i++) {
    s21_bigdec tmp_val_1 = val_1;
    if (get_bit_bigdec(val_2, i)) {
      shift_left_by_num_bigdec(&tmp_val_1, i);
      bitwise_summation_bigdec(tmp, tmp_val_1, &tmp);
    }
  }
  *res = tmp;
  return 0;
}

unsigned get_bit_bigdec(s21_bigdec val, int index) {
  int i = index / 32;
  index -= (i * 32);
  return (val.bits[i] & (1 << index)) >> index;
}

void set_bit_bigdec(s21_bigdec *dec, int index, int val) {
  int i = index / 32;
  index -= (i * 32);
  if (val == 1) dec->bits[i] |= (1 << index);
  if (val == 0) dec->bits[i] &= (~(1 << index));
}

void shift_left_bigdec(s21_bigdec *dec) {
  s21_bigdec tmp = {0};
  int bit_tmp = 0;
  tmp.ext = dec->ext;
  for (int i = 7; i > -1; i--) {
    bit_tmp = get_bit_bigdec(*dec, ((i * 32) - 1));
    tmp.bits[i] = dec->bits[i] << 1;
    if (i) set_bit_bigdec(&tmp, (i * 32), bit_tmp);
  }
  *dec = tmp;
}

void shift_left_by_num_bigdec(s21_bigdec *dec, int num) {
  for (int i = 0; i < num; i++) {
    shift_left_bigdec(dec);
  }
}

void transf_dec_bigdec(s21_decimal *dec, s21_bigdec *b_dec) {
  b_dec->sign = check_sign(*dec);
  b_dec->ext = get_scale(*dec);
  b_dec->bits[0] = dec->bits[0];
  b_dec->bits[1] = dec->bits[1];
  b_dec->bits[2] = dec->bits[2];
}

int great_mantissa_bigdec(s21_bigdec val_1, s21_bigdec val_2) {
  int equal = 0;
  for (int i = 255; i > -1; i--) {
    if (get_bit_bigdec(val_1, i) > get_bit_bigdec(val_2, i)) {
      equal = 1;
      break;
    } else if (get_bit_bigdec(val_1, i) < get_bit_bigdec(val_2, i)) {
      break;
    }
  }
  return equal;
}

int division_by_ten_bigdec(s21_bigdec dec, s21_bigdec *res) {
  uint64_t tmp_u;
  uint64_t remained = 0;
  for (int i = 7; i > -1; i--) {
    tmp_u = dec.bits[i];
    tmp_u |= remained << 32;
    remained = tmp_u % 10;
    tmp_u /= 10;
    res->bits[i] = UINT_MAX & tmp_u;
  }
  if (remained > 4) {
    res->bits[0] += 1;
  }
  return 0;
}

int multiplay_by_ten_bigdec(s21_bigdec dec, s21_bigdec *res) {
  uint64_t tmp_u;
  unsigned remained = 0;
  for (int i = 0; i < 8; i++) {
    tmp_u = dec.bits[i];
    tmp_u *= 10;
    tmp_u += remained;
    remained = tmp_u >> 32;
    res->bits[i] = UINT_MAX & tmp_u;
  }
  return 0;
}

void normalization_bigdec(s21_bigdec *one, s21_bigdec *two) {
  int diff = one->ext - two->ext;
  while (one->ext > 28) {
    division_by_ten_bigdec(*one, one);
    one->ext--;
    diff--;
  }
  while (two->ext > 28) {
    division_by_ten_bigdec(*two, two);
    two->ext--;
    diff--;
  }
  while (diff > 0) {
    multiplay_by_ten_bigdec(*two, two);
    two->ext++;
    diff--;
  }
  while (diff < 0) {
    multiplay_by_ten_bigdec(*one, one);
    one->ext++;
    diff++;
  }
}

int check_bigdec(s21_bigdec dec) {
  int check = 0;
  for (int i = 7; i > 2; i--) {
    if (dec.bits[i] != 0) {
      check = 1;
      i = 0;
    }
  }
  return check;
}

int reduction_bigdec(s21_bigdec *dec) {
  int flag = 0;
  while ((check_bigdec(*dec) && !flag) || dec->ext > 28) {
    division_by_ten_bigdec(*dec, dec);
    --dec->ext;
  }
  if (dec->ext < 0) flag = 1;
  return flag;
}

int transf_bigdec_dec(s21_bigdec *big, s21_decimal *dec) {
  int flag = reduction_bigdec(big);
  set_scale(dec, big->ext);
  set_bit(dec, 127, big->sign);
  dec->bits[2] = big->bits[2];
  dec->bits[1] = big->bits[1];
  dec->bits[0] = big->bits[0];
  if (check_zero_mantissa(dec)) set_scale(dec, 0);
  return flag;
}

void print_bigdec(s21_bigdec dec) {
  for (int i = 7; i > -1; i--) {
    for (int j = 31; j > -1; j--) {
      printf("%d", get_bit_bigdec(dec, j + (i * 32)));
    }
    printf(" ");
  }
  printf("\n");
}

int take_bit_to_sub(s21_bigdec *val, int i) {
  int flag = 1;
  while (flag) {
    if (get_bit_bigdec(*val, i) == 0) {
      set_bit_bigdec(val, i, 1);
    } else if (get_bit_bigdec(*val, i)) {
      set_bit_bigdec(val, i, 0);
      flag = 0;
    }
    i++;
  }
  return 0;
}

int get_higher_bit_bigdec(s21_bigdec value) {
  int result = 0;
  for (int i = 255; i > -1; i--) {
    if (get_bit_bigdec(value, i)) {
      result = i;
      break;
    }
  }
  return result;
}

void shift_right_bigdec(s21_bigdec *dec) {
  s21_bigdec tmp = {0};
  int bit_tmp = 0;
  tmp.ext = dec->ext;
  for (int i = 7; i > -1; i--) {
    bit_tmp = get_bit_bigdec(*dec, ((i * 32) + 1));
    tmp.bits[i] = dec->bits[i] >> 1;
    set_bit_bigdec(&tmp, (i * 32), bit_tmp);
  }
  *dec = tmp;
}

void shift_right_by_num_bigdec(s21_bigdec *dec, int num) {
  for (int i = 0; i < num; i++) {
    shift_right_bigdec(dec);
  }
}

int is_equal_bigdec(s21_bigdec value_1, s21_bigdec value_2) {
  int result = 1;
  for (int i = 95; i > -1; i--) {
    if (get_bit_bigdec(value_1, i) != get_bit_bigdec(value_2, i)) {
      result = 0;
      break;
    }
  }
  return result;
}

void div_with_rem_bigdec(s21_bigdec value_1, s21_bigdec value_2,
                         s21_bigdec *result, s21_bigdec *remainder) {
  s21_bigdec big_result = {0};
  s21_bigdec buffer = value_1;
  int padding = get_higher_bit_bigdec(value_1) - get_higher_bit_bigdec(value_2);
  shift_right_by_num_bigdec(&buffer, padding);
  while (padding >= 0) {
    int bit_res = 0;
    if (great_mantissa_bigdec(buffer, value_2) ||
        is_equal_bigdec(buffer, value_2)) {
      s21_sub_bigdec(buffer, value_2, &buffer);
      bit_res = 1;
    }
    shift_left_bigdec(&big_result);
    set_bit_bigdec(&big_result, 0, bit_res);
    if (padding) {
      shift_left_bigdec(&buffer);
      s21_bigdec tmp = value_1;
      shift_right_by_num_bigdec(&tmp, padding - 1);
      int bit = get_bit_bigdec(tmp, 0);
      set_bit_bigdec(&buffer, 0, bit);
    }
    padding--;
  }
  *result = big_result;
  *remainder = buffer;
}