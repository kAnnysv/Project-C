
#include "s21_decimal.h"

// получаем бит по индексу
unsigned get_bit(s21_decimal val, int index) {
  int i = index / 32;
  index -= (i * 32);
  return (val.bits[i] & (1 << index)) >> index;
}

void set_bit(s21_decimal *dec, int index, int val) {
  int i = index / 32;
  index -= (i * 32);
  if (val == 1) dec->bits[i] |= (1 << index);
  if (val == 0) dec->bits[i] &= (~(1 << index));
}

// определяем знак децимала
int check_sign(s21_decimal dec) { return get_bit(dec, 127); }

// определяем значение степени
int get_scale(s21_decimal dec) { return (dec.bits[3] & (255 << 16)) >> 16; }

// определяем значение числа до exp bits[3] до 16 бита
int get_before_scale(s21_decimal dec) { return (dec.bits[3] & 32767); }

// меняем значение степени на val
void set_scale(s21_decimal *dec, int val) {
  if (val < 29 && val > -1) {
    unsigned int temp = 0;
    if (get_bit(*dec, 127)) {
      temp = ((unsigned int)1 << 31);
    }

    temp |= (val << 16);
    dec->bits[3] = temp;
    // printf("%d\n", get_bit(*dec, 127));
  }
}

// сдвиг влево всей мантисы на 1
void shift_left(s21_decimal *dec) {
  s21_decimal temp = {0};
  int bit_temp = get_bit(*dec, 63);
  temp.bits[2] = dec->bits[2] << 1;
  set_bit(&temp, 64, bit_temp);
  bit_temp = get_bit(*dec, 31);
  temp.bits[1] = dec->bits[1] << 1;
  set_bit(&temp, 32, bit_temp);
  temp.bits[0] = dec->bits[0] << 1;
  temp.bits[3] = dec->bits[3];
  *dec = temp;
}

// сдвиг вправо всей мантисы на 1
void shift_right(s21_decimal *dec) {
  s21_decimal temp = {0};
  int bit_temp = get_bit(*dec, 32);
  temp.bits[0] = dec->bits[0] >> 1;
  set_bit(&temp, 31, bit_temp);
  bit_temp = get_bit(*dec, 64);
  temp.bits[1] = dec->bits[1] >> 1;
  set_bit(&temp, 63, bit_temp);
  temp.bits[2] = dec->bits[2] >> 1;
  temp.bits[3] = dec->bits[3];
  *dec = temp;
}

// печать децимала в двоичном коде
void print_binary(s21_decimal shatohin) {
  for (int i = 3; i > -1; i--) {
    for (int j = 31; j > -1; j--) {
      printf("%d", get_bit(shatohin, j + (i * 32)));
    }
    printf(" ");
  }
  printf("\n");
}

// умножение мантиссы на 10
// НО! если заходит в bits[4] меняет ext, быть аккуратнее
int multiplay_by_ten(s21_decimal dec, s21_decimal *res) {
  uint64_t tmp_u;
  unsigned int remainder = 0;
  for (int i = 0; i < 3; i++) {
    tmp_u = dec.bits[i];
    tmp_u *= 10;
    tmp_u += remainder;
    remainder = tmp_u >> 32;
    res->bits[i] = UINT_MAX & tmp_u;
  }
  return 0;
}

// деление мантиссы на 10
int division_by_ten(s21_decimal dec, s21_decimal *res) {
  uint64_t tmp_u;
  uint64_t remained = 0;
  for (int i = 2; i > -1; i--) {
    tmp_u = dec.bits[i];
    tmp_u |= remained << 32;
    remained = tmp_u % 10;
    tmp_u /= 10;
    res->bits[i] = UINT_MAX & tmp_u;
  }
  return remained;
}

void equalization(int ext_big, int ext_small, s21_decimal *big_ext,
                  s21_decimal *small_ext) {
  int diff = ext_big - ext_small;
  s21_decimal tmp = *small_ext;
  int work_mul = 1;
  while (diff > 0 && work_mul) {
    multiplay_by_ten(tmp, &tmp);
    if (get_before_scale(tmp)) work_mul = 0;
    if (work_mul) {
      diff--;
      set_scale(&tmp, ++ext_small);
      *small_ext = tmp;
    }
  }
  while (diff) {
    division_by_ten(*big_ext, big_ext);
    set_scale(big_ext, --ext_big);
    diff--;
  }
}

// приведение степеней к одному виду
// пример:
// подаем 123/10^10 и 123/10^5
// пoлучаем 123/10^10 и 12300000/10^10
void normalization(s21_decimal *dec_one, s21_decimal *dec_two) {
  int ext_one = get_scale(*dec_one);
  int ext_two = get_scale(*dec_two);
  // int work_mul = 1;
  if (ext_one > 28) {
    while (ext_one != 28) {
      division_by_ten(*dec_one, dec_one);
      set_scale(dec_one, --ext_one);
    }
  }
  if (ext_two > 28) {
    while (ext_two != 28) {
      division_by_ten(*dec_two, dec_two);
      set_scale(dec_two, --ext_two);
    }
  }
  int diff = ext_one - ext_two;
  if (diff > 0)
    equalization(ext_one, ext_two, dec_one, dec_two);
  else if (diff < 0)
    equalization(ext_two, ext_one, dec_two, dec_one);
}

int s21_decimal_is_zero(s21_decimal dec) {
  int res = 0;
  if (dec.bits[0] == 0 && dec.bits[1] == 0 && dec.bits[2] == 0) {
    res = 1;
  }

  return res;
}

void set_zero(s21_decimal *dec) {
  dec->bits[0] = dec->bits[1] = dec->bits[2] = dec->bits[3] = 0;
}

int int_add_decimal(s21_decimal dec, int a, s21_decimal *res) {
  int err = 0;
  s21_decimal int_dec = {0};
  int sign = (a < 0) ? 1 : 0;
  if (sign) s21_negate(int_dec, &int_dec);
  int_dec.bits[0] = abs(a);
  err = s21_add(dec, int_dec, res);

  return err;
}

void zeroing_dec(s21_decimal *dec) {
  dec->bits[0] = 0;
  dec->bits[1] = 0;
  dec->bits[2] = 0;
  dec->bits[3] = 0;
}

int check_zero_mantissa(s21_decimal *dec) {
  int flag = 1;
  for (int i = 0; i < 3; i++) {
    if (dec->bits[i]) {
      flag = 0;
    }
  }
  return flag;
}
