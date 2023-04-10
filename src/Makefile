CC= gcc -std=c11
CFLAGS= -Wall -Wextra -Werror 
TEST= *.c test1/*.c
TEST_FLAGS = -lcheck

OS := $(shell uname -s)

ifeq ($(OS), Darwin)
    TEST_FLAGS = -lcheck
else
	TEST_FLAGS = -lcheck -lpthread -pthread -lrt -lm -lsubunit
endif


all: s21_matrix.a

build: 
	gcc $(CFLAGS) *.c -o test -g
	./test #delete

test: clean
		$(CC) $(TEST_FLAGS) $(CFLAGS) *.c test1/*.c -o test -g
		 ./test

gcov_report: clean
		$(CC) --coverage $(TEST_FLAGS) $(CFLAGS) $(TEST)  -o test
		
		./test
		lcov -t "test" -o test.info -c -d . 
		genhtml -o report test.info
		open report/index.html

clean:
	rm -rf test
	rm -rf *.a *.out *.o report *.gc* s21_matrix.a *.info 
run:
	./test

s21_matrix.a: clean
		$(CC) $(CFLAGS) *.c -c 
		ar rcs s21_matrix.a *.o

rebuild:
	make clean
	make all

leak:
	CK_FORK=no leaks --atExit -- ./test 

