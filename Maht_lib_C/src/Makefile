CFLAGS = -Wall -Werror -Wextra -std=c11 -g
MATHFUNC = $(SOURCES:.c=.o)
SOURCES = s21_fmod.c s21_acos.c s21_asin.c s21_atan.c s21_ceil.c s21_fabs.c s21_pow.c s21_cos.c s21_log.c s21_sqrt.c s21_tan.c s21_sin.c s21_abs.c s21_floor.c s21_exp.c
TESTS = s21_test.o
S21MATHLIB = s21_math.a

UNAME = $(shell uname -s)
FLAGS =

ifeq ($(UNAME), Linux)
	FLAGS += -lcheck -lm -lsubunit -lrt -lpthread
else
	FLAGS += -lcheck
endif

all: test style

%.o: %.c
	gcc $(CFLAGS) -c $^  -o $@

test: $(TESTS) $(S21MATHLIB)
	gcc  $^ -o test $(CFLAGS) $(FLAGS)
	rm -rf *.o 
	./test
	
$(TESTS): $(TESTS:.o=.c)
	gcc -Wall -std=c11 -c $^  -o $@
	
$(S21MATHLIB): $(MATHFUNC)
	ar rc $(S21MATHLIB) $^
	ranlib $(S21MATHLIB)

style:
	clang-format -i -style=Google *.c *.h

rebuild: clean all

gcov_report: clean $(TESTS)
	gcc -o test $(TESTS) --coverage $(SOURCES) -lcheck -lm
	./test
	lcov -t "a.out" -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index.html
	rm -rf test *.o *.a *gcda *gcno *info


clean:
	rm -rf report
	rm -rf test *.o *.a *.gch *gcda report *gcno *info

.PHONY: all, test, style, rebuild, gcov_report, clean, s21_math.a