
TEST_FOLDER  = tests
TEST_OUTPUT  = test
TEST_PRE_H   = main.h

COMPILATOR   = g++ -g
FLAGS_BASIC  = -Wall -Wextra -Werror --std=c++17 #-pedantic
FLAGS_EXTRA  = $(FLAGS_BASIC) -fsanitize=address,undefined,leak
FLAGS_COV    = -lgtest -pthread -lgcov --coverage

GCOV_INFO    = gcov_report.info
GCOV_FOLDER  = report
VALGRIND_LOG = _valgrind-out.txt
TMP_FILES    = $(GCOV_INFO) *.gcda *.gcno *.gcda $(TEST_FOLDER)/*.gcno *.gcov *.out $(TEST_OUTPUT).dSYM
REST_FILES   = $(GCOV_FOLDER) ./$(TEST_OUTPUT) $(VALGRIND_LOG) $(TEST_FOLDER)/$(TEST_PRE_H).gch $(TEST_FOLDER)/$(TEST_PRE_H).gcno

.PHONY: clean
clean:
	rm -rf $(TMP_FILES)

.PHONY: fclean
fclean: clean
	rm -rf $(REST_FILES)

.PHONY: test
test:
	$(COMPILATOR) -c $(TEST_FOLDER)/$(TEST_PRE_H) -o $(TEST_FOLDER)/$(TEST_PRE_H).gch $(FLAGS_EXTRA) $(FLAGS_COV)
	$(COMPILATOR) $(TEST_FOLDER)/*.cc -o $(TEST_OUTPUT) $(FLAGS_EXTRA) $(FLAGS_COV)
	./$(TEST_OUTPUT)

.PHONY: gcov_report
gcov_report: test
	lcov -t "gcov_report" -o $(GCOV_INFO) -c -d . --no-external && \
	genhtml -o $(GCOV_FOLDER) $(GCOV_INFO) && \
	$(MAKE) clean && \
	open $(GCOV_FOLDER)/index.html

.PHONY: lint
lint:
	clang-format -n *.h $(TEST_FOLDER)/*.cc $(TEST_FOLDER)/*.h
	cppcheck --enable=all --language=c++ --std=c++17 \
	--suppress=missingIncludeSystem \
	--suppress=unusedFunction \
	--suppress=noExplicitConstructor \
	--suppress=operatorEqVarError \
	--suppress=postfixOperator \
	--suppress=selfAssignment \
	--suppress=unreadVariable \
	*.h $(TEST_FOLDER)/*.cc $(TEST_FOLDER)/*.h

.PHONY: format
format:
	clang-format -i *.h $(TEST_FOLDER)/*.cc $(TEST_FOLDER)/*.h

.PHONY: grind
grind: FLAGS_EXTRA = $(FLAGS_BASIC)
grind: fclean test
	valgrind \
	--leak-check=full \
	--show-reachable=yes \
	--show-leak-kinds=all \
	--track-origins=yes \
	--log-file=$(VALGRIND_LOG) ./$(TEST_OUTPUT)
	$(MAKE) clean
