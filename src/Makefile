TEST_DIR  = tests
TEST_EXE  = test
TEST_PRE_H   = main.h
SOURCE_FILES = s21_cont/s21_queue.h

CC   = g++ -g
FLAGS_BASIC  = -Wall -Wextra -Werror --std=c++17 #-pedantic
FLAGS_EXTRA  = $(FLAGS_BASIC) -fsanitize=address,undefined,leak
FLAGS_COV    = -lgtest -pthread --coverage

GCOV_INFO    = output.info
GCOV_DIR  = report

TMP_FILES    = $(GCOV_INFO) *.gcda *.gcno *.gcda $(TEST_DIR)/*.gcno *.gcov *.out $(TEST_EXE).dSYM
REST_FILES   = $(GCOV_DIR) ./$(TEST_EXE) $(VALGRIND_LOG) $(TEST_DIR)/$(TEST_PRE_H).gch $(TEST_DIR)/$(TEST_PRE_H).gcno

all: test gcov_report

clean:
	rm -rf $(TMP_FILES) $(REST_FILES)
	rm -rf gcov_report.info
	

test:
	$(CC) --coverage $(TEST_DIR)/main.cc $(TEST_DIR)/test_Queue.cc $(SOURCE_FILES) -o $(TEST_EXE) $(FLAGS_EXTRA) $(FLAGS_COV)
	./$(TEST_EXE)

gcov_report: 
	$(CC) --coverage $(TEST_DIR)/main.cc $(TEST_DIR)/test_Queue.cc $(SOURCE_FILES) -o $(TEST_EXE) $(FLAGS_EXTRA) $(FLAGS_COV)
	./$(TEST_EXE)
	lcov -t "result" -o output.info -c -d . --include */s21_cont/*.h
	genhtml -o report output.info
	xdg-open report/index.html

valgrind:
	valgrind --tool=memcheck --track-fds=yes --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./$(TEST_EXE)

