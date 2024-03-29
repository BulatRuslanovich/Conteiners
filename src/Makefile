CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c++17 -lstdc++

test: clean
	$(CC) $(CFLAGS) --coverage tests/*.cc -lgtest -lgtest_main -g -o test
	./test

clean:
	rm -rf test *.o *.a *.gcda *.gcno *.out