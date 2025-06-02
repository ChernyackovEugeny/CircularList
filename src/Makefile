CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -I../include
LDFLAGS = -pthread

MAIN = main
MAIN_SRC = main.cpp

TEST_SRC = ../tests/circular_list_test.cpp
TEST_BIN = circular_list_test

all: $(MAIN)

$(MAIN): $(MAIN_SRC) ../include/circular_list.hpp
	$(CXX) $(CXXFLAGS) -o $(MAIN) $(MAIN_SRC)

test: $(TEST_SRC) ../include/circular_list.hpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TEST_BIN) $(TEST_SRC) -lgtest -lgtest_main

run: $(MAIN)
	./$(MAIN)

run_test: $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -f $(MAIN) $(TEST_BIN)

.PHONY: all test run run_test clean
