CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17 -lstdc++

test: clean
test: clean
	$(CC) $(CFLAGS) --coverage tests/*.cc containners/s21_stack.cpp -lgtest -g -o test
	./test
clean:
	rm -rf test *.o *.a *.gcda *.gcno *.out