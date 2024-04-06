CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17 -lstdc++


test: clean
	#g++ tests/main.cpp tests/s21_list_test.cpp tests/s21_map_test.cpp tests/s21_stack_test.cpp  tests/s21_set_test.cpp containers/s21_list.h  containers/s21_stack.h containers/s21_map.h containers/s21_set.h -lgtest -o test
	g++ tests/main.cpp tests/s21_vector_test.cpp containers/s21_vector.h -lgtest -o test
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