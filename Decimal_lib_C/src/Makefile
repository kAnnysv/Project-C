CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11 -pedantic 
TFLAGS=-o testing -lcheck --coverage 
SOURCE=anofer.c comparison_operators.c convert.c s21_addition_funcs.c s21_big_decimal.c s21_math.c
TFILES=tests.c
ifeq ($(shell uname), Linux)
	TFLAGS += -lm -lsubunit
endif

ifeq ($(shell uname), Darwin)
	TFLAGS += -fprofile-arcs -ftest-coverage
endif

all: s21_decimal.a test gcov_report

s21_decimal.a:
	$(CC) $(CFLAGS) -c $(SOURCE)
	ar -rc s21_decimal.a *.o

test: s21_decimal.a
	$(CC) $(TFILES) s21_decimal.a $(TFLAGS)
	./testing

gcov_report: test
	rm -rf html_report
	gcov -b *.c 
	lcov -d . -c -o coverage.info
	genhtml -o html_report coverage.info
	open ./html_report/index.html

clean:
	rm -rf *.o testing *.a *.gcno *.gcda *.gcov *.info


format:
	find . -type f -name "*.c" -exec clang-format -i {} \;
	find . -type f -name "*.h" -exec clang-format -i {} \;
