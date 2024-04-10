FLAGS = -Wall -Wextra -Werror -g -std=c11 # -fsanitize=address
LFLAGS = -lcheck -lpthread -lm
SOURCES= calcul.c stek.c valid.c
OBJECTS= calcul.o stek.o valid.o
TARGET = Smart_Calculator

ifeq ($(shell uname -s), Linux)
        LFLAGS = -lm -lpthread -lcheck -lsubunit
endif

all: test

test: 
	gcc $(FLAGS) $(SOURCES) -c test.c
	gcc $(FLAGS) test.o $(OBJECTS) $(LFLAGS) -o test.out
	rm -rf *.o 
	clear
	./test.out

install:
	mkdir build
	mkdir $(HOME)/Desktop/Calculator
	cd build && cmake ../calcqt/CMakeLists.txt && make
	cp -rf build/calcqt.app $(HOME)/Desktop/Calculator/Calculator.app

uninstall: clean
	rm -rf build
	rm -rf calcqt/calcqt.app
	rm -rf calcqt/CMakeFiles
	rm -rf calcqt/Makefile
	rm -rf calcqt/calc_autogen
	rm -rf calcqt/CMakeCache.txt
	rm -rf calcqt/cmake_install.cmake
	rm -rf $(HOME)/Desktop/Calculator

gcov_report: clean add_coverage test
	./test.out
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	rm -rf *.gcda *.gcno test.info
	open report/index.html

dist:
	mkdir ../dist
	cp -r ../src ../dist
	cp ../README.md ../dist
	tar -czvf dist.tar.gz ../dist
	rm -rf ../dist

dvi:
#d readme/ && texi2dvi --pdf document.tex 
	open ./readme/document.pdf	

add_coverage:
	$(eval FLAGS += --coverage)

clean:
	rm -rf *.o gcov_report *.a *.gcda *.gcno test test.info -r report

style:
	clang-format -i -style=Google *.c *.h

rebuild: clean all

