#include "calc.h"

int valid_func(char c) {
  int err = 0;
  if (c == 'c' || c == 'o' || c == 's' || c == 'i' || c == 'n' || c == 't' ||
          c == 'a' || c == 'g' || c == 'r' || c == 'l' || c == 'q' || c == 'm'
      || c == 'd') {
    err = 1;
  }

  return err;
}

int valid_experss(const char *mas) {
  char c;
  int err = 0;
  for (size_t i = 0; i < strlen(mas); i++) {
    c = mas[i];
    if (isdigit(c)) {
      continue;
    } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == ' ' ||
               c == '^' || c == '(' || c == ')' || c == '.' || c == 'x') {

      continue;
    } else if (c == '.' && mas[i + 1] == '.') {
      break;

    } else if (valid_func(c)) {
      if (c == 'c' && mas[i + 1] == 'o' && mas[i + 2] == 's' &&
          mas[i + 3] == '(' && check_letter(mas[i - 1])) {
        i += 3;
      } else if (c == 's' && check_letter(mas[i - 1]) && mas[i + 1] == 'i' &&
                 mas[i + 2] == 'n' && mas[i + 3] == '(') {
        i += 3;
      } else if (c == 't' && check_letter(mas[i - 1]) && mas[i + 1] == 'a' &&
                 mas[i + 2] == 'n' && mas[i + 3] == '(') {
        i += 3;
      } else if (c == 'a' && check_letter(mas[i - 1]) && mas[i + 1] == 't' &&
                 mas[i + 2] == 'a' && mas[i + 3] == 'n' && mas[i + 4] == '(') {
        i += 4;
      } else if (c == 'a' && check_letter(mas[i - 1]) && mas[i + 1] == 'c' &&
                 mas[i + 2] == 'o' && mas[i + 3] == 's' && mas[i + 4] == '(') {
        i += 4;
      } else if (c == 'a' && check_letter(mas[i - 1]) && mas[i + 1] == 's' &&
                 mas[i + 2] == 'i' && mas[i + 3] == 'n' && mas[i + 4] == '(') {
        i += 4;
      } else if (c == 's' && check_letter(mas[i - 1]) && mas[i + 1] == 'q' &&
                 mas[i + 2] == 'r' && mas[i + 3] == 't' && mas[i + 4] == '(') {
        i += 4;
      } else if (c == 'l' && check_letter(mas[i - 1]) && mas[i + 1] == 'n' &&
                 mas[i + 2] == '(') {
        i += 3;
      } else if (c == 'l' && check_letter(mas[i - 1]) && mas[i + 1] == 'o' &&
                 mas[i + 2] == 'g' && mas[i + 3] == '(') {
        i += 3;
      } else if (c == 'm' && check_letter(mas[i - 1]) && mas[i + 1] == 'o' &&
                 mas[i + 2] == 'd') {

        i += 2;
      } else {
        err = 1;
      }

    } else {
      err = 1;
    }
  }
  return err;
}