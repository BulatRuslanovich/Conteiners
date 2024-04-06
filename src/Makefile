CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17 -lstdc++


test: clean
	g++ tests/main.cc tests/s21_stack_test.cc containers/s21_stack.h -lgtest -o test
	./test

clean:
	rm -rf test *.o *.a *.gcda *.gcno *.out *.info report