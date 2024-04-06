CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17 -lstdc++


test: clean
	$(CC) $(CFLAGS) --coverage tests/s21_array_test.cc -lgtest -g -o test
	./test
clean:
	rm -rf test *.o *.a *.gcda *.gcno *.out