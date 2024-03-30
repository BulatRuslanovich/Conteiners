CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c++17 -lstdc++

test: clean
	g++ tests/main.cpp tests/s21_list_test.cpp containers/s21_list.h -lgtest -o test
	./test

gcov: report
	g++ --coverage tests/main.cpp tests/s21_list_test.cpp containers/s21_list.h -lgtest -o test
	./test
	lcov -t "result" -o output.info -c -d . --include */src/containers/*.h
	genhtml -o report output.info
	xdg-open report/index.html

report:
	mkdir -p report
clean:
	rm -rf test *.o *.a *.gcda *.gcno *.out *.info report