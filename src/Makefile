CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17 -lstdc++

test: clean
	g++ $(CFLAGS) tests/*.cpp containers/*.h -lgtest -o test
	./test
gcov: report
	g++ --coverage tests/*.cpp containers/*.h -lgtest -o test
	./test
	lcov -t "result" -o output.info -c -d . --include */src/containers/*.h
	genhtml -o report output.info
	xdg-open report/index.html
report:
	mkdir -p report
clean:
	rm -rf test *.o *.a *.gcda *.gcno *.out *.info report
cpplint:
	clang-format -n --verbose tests/*.cpp containers/*.h
valgrind:
	valgrind  --tool=memcheck --track-fds=yes --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./test

