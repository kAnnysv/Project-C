#include "calc.h"

void push_double(double n, int *i, double *mas) {
  *i = *i + 1;

  mas[*i] = n;
}

double pop_double(double *mas, int *i) {
  double res = mas[*i];

  *i = *i - 1;

  return res;
}

void push_char(char n, int *i, char *mas) {
  *i = *i + 1;

  mas[*i] = n;
}
char pop_char(char *mas, int *i) {
  char res = mas[*i];

  *i = *i - 1;

  return res;
}

int op_priority(char c) {
  int priority = 0;
  if (c == '+' || c == '-') {
    priority = 1;
  } else if (c == '*' || c == '/') {
    priority = 2;
  } else if (c == '^') {
    priority = 3;
  } else if (c == '(') {
    priority = 5;
  } else if (c == 'a' || c == 'b' || c == 'd' || c == 'e' || c == 'o' ||
             c == 'u' || c == 'q' || c == 'l' || c == 'g' || c == 'm') {
    priority = 4;
  }
  return priority;
}

double calc_end(double *stek_double, int *count_double, char *stek_char,
                int *count_char) {
  double result = 0;
  double num2 = pop_double(stek_double, count_double);
  double num1;
  char c = pop_char(stek_char, count_char);

  if (c == 'a') {
    result = cos(num2);
  } else if (c == 'b') {
    result = sin(num2);
  } else if (c == 'd') {
    result = tan(num2);
  } else if (c == 'e') {
    result = acos(num2);
  } else if (c == 'o') {
    result = asin(num2);
  } else if (c == 'u') {
    result = atan(num2);
  } else if (c == 'q') {
    result = sqrt(num2);
  } else if (c == 'l') {
    result = log(num2);
  } else if (c == 'g') {
    result = log10(num2);
  } else if (c == '+') {
    num1 = pop_double(stek_double, count_double);
    result = num1 + num2;
  } else if (c == '*') {
    num1 = pop_double(stek_double, count_double);
    result = num1 * num2;
  } else if (c == '-') {
    num1 = pop_double(stek_double, count_double);
    result = num1 - num2;
  } else if (c == '/') {
    num1 = pop_double(stek_double, count_double);
    result = num1 / num2;
  } else if (c == '^') {
    num1 = pop_double(stek_double, count_double);
    result = pow(num1, num2);
  } else if (c == 'm') {
    num1 = pop_double(stek_double, count_double);
    result = fmod(num1, num2);
  }
  push_double(result, count_double, stek_double);

  return result;
}

void calc(double *stek_double, int *count_double, char c) {
  double result = 0;
  double num2 = pop_double(stek_double, count_double);
  double num1;
  if (c == 'a') {
    result = cos(num2);
  } else if (c == 'b') {
    result = sin(num2);
  } else if (c == 'd') {
    result = tan(num2);
  } else if (c == 'e') {
    result = acos(num2);
  } else if (c == 'o') {
    result = asin(num2);
  } else if (c == 'u') {
    result = atan(num2);
  } else if (c == 'q') {
    result = sqrt(num2);
  } else if (c == 'l') {
    result = log(num2);
  } else if (c == 'g') {
    result = log10(num2);
  } else if (c == '+') {
    num1 = pop_double(stek_double, count_double);
    result = num1 + num2;
  } else if (c == '*') {
    num1 = pop_double(stek_double, count_double);
    result = num1 * num2;
  } else if (c == '-') {
    num1 = pop_double(stek_double, count_double);
    result = num1 - num2;
  } else if (c == '/') {
    num1 = pop_double(stek_double, count_double);
    result = num1 / num2;
  } else if (c == '^') {
    num1 = pop_double(stek_double, count_double);
    result = pow(num1, num2);
  } else if (c == 'm') {
    num1 = pop_double(stek_double, count_double);
    result = fmod(num1, num2);
  }
  push_double(result, count_double, stek_double);
}

void clear_space(char *mas) {
  char tmp[STEKSIZE];
  char c;
  int tm = 0;
  for (size_t i = 0; i < strlen(mas); i++) {
    c = mas[i];
    if (c == ' ' || c == '\t') {
      continue;

    } else {
      if (c == '-') {
        if (i == 0 || mas[i - 1] == '(') {
          tmp[tm] = '0';
          tm++;
        }
      }
      tmp[tm] = c;

      tm++;
    }
  }

  strcpy(mas, tmp);
}

void function_substitution(char *mas) {
  char tmp[STEKSIZE] = {0};
  char c;
  int tm = 0;
  for (size_t i = 0; i < strlen(mas); i++) {
    c = mas[i];
    if (c == 'c' && mas[i + 1] == 'o' && mas[i + 2] == 's' &&
        mas[i + 3] == '(' && check_letter(mas[i - 1])) {
      tmp[tm] = 'a';
      i += 2;
    } else if (c == 's' && check_letter(mas[i - 1]) && mas[i + 1] == 'i' &&
               mas[i + 2] == 'n' && mas[i + 3] == '(') {
      tmp[tm] = 'b';
      i += 2;
    } else if (c == 't' && check_letter(mas[i - 1]) && mas[i + 1] == 'a' &&
               mas[i + 2] == 'n' && mas[i + 3] == '(') {
      tmp[tm] = 'd';
      i += 2;
    } else if (c == 'a' && check_letter(mas[i - 1]) && mas[i + 1] == 'c' &&
               mas[i + 2] == 'o' && mas[i + 3] == 's' && mas[i + 4] == '(') {
      tmp[tm] = 'e';
      i += 3;
    } else if (c == 'a' && check_letter(mas[i - 1]) && mas[i + 1] == 's' &&
               mas[i + 2] == 'i' && mas[i + 3] == 'n' && mas[i + 4] == '(') {
      tmp[tm] = 'o';
      i += 3;
    } else if (c == 'a' && check_letter(mas[i - 1]) && mas[i + 1] == 't' &&
               mas[i + 2] == 'a' && mas[i + 3] == 'n' && mas[i + 4] == '(') {
      tmp[tm] = 'u';
      i += 3;
    } else if (c == 's' && check_letter(mas[i - 1]) && mas[i + 1] == 'q' &&
               mas[i + 2] == 'r' && mas[i + 3] == 't' && mas[i + 4] == '(') {
      tmp[tm] = 'q';
      i += 3;
    } else if (c == 'l' && check_letter(mas[i - 1]) && mas[i + 1] == 'n' &&
               mas[i + 2] == '(') {
      tmp[tm] = 'l';
      i += 1;
    } else if (c == 'l' && check_letter(mas[i - 1]) && mas[i + 1] == 'o' &&
               mas[i + 2] == 'g' && mas[i + 3] == '(') {
      tmp[tm] = 'g';
      i += 2;
    } else if (c == 'm' && check_letter(mas[i - 1]) && mas[i + 1] == 'o' &&
               mas[i + 2] == 'd') {
      tmp[tm] = 'm';
      i += 2;
    } else {
      tmp[tm] = c;
    }

    tm++;
  }

  strcpy(mas, tmp);
}
