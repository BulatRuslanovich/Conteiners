CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17 -lstdc++


test: clean
	$(CC) $(CFLAGS) --coverage tests/*.cc -lgtest -g -o test
	./test
clean:
	rm -rf test *.o *.a *.gcda *.gcno *.out