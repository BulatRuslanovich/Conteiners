TEST_FOLDER  = tests
TEST_OUTPUT  = test
TEST_PRE_H   = main.h
SOURCE_FILES = s21_cont/s21_queue.h

CC   = g++ -g
FLAGS_BASIC  = -Wall -Wextra -Werror --std=c++17 #-pedantic
FLAGS_EXTRA  = $(FLAGS_BASIC) -fsanitize=address,undefined,leak
FLAGS_COV    = -lgtest -pthread --coverage

GCOV_INFO    = output.info
GCOV_FOLDER  = report

TMP_FILES    = $(GCOV_INFO) *.gcda *.gcno *.gcda $(TEST_FOLDER)/*.gcno *.gcov *.out $(TEST_OUTPUT).dSYM
REST_FILES   = $(GCOV_FOLDER) ./$(TEST_OUTPUT) $(VALGRIND_LOG) $(TEST_FOLDER)/$(TEST_PRE_H).gch $(TEST_FOLDER)/$(TEST_PRE_H).gcno

clean:
	rm -rf $(TMP_FILES) $(REST_FILES)
	rm -rf gcov_report.info
	

test:
	$(CC) --coverage $(TEST_FOLDER)/main.cc $(TEST_FOLDER)/test_Queue.cc $(SOURCE_FILES) -o $(TEST_OUTPUT) $(FLAGS_EXTRA) $(FLAGS_COV)
	./$(TEST_OUTPUT)

gcov_report: 
	$(CC) --coverage $(TEST_FOLDER)/main.cc $(TEST_FOLDER)/test_Queue.cc $(SOURCE_FILES) -o $(TEST_OUTPUT) $(FLAGS_EXTRA) $(FLAGS_COV)
	./$(TEST_OUTPUT)
	lcov -t "result" -o output.info -c -d . --include */s21_cont/*.h
	genhtml -o report output.info
	xdg-open report/index.html