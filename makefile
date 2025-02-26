CXX = g++

CXXFLAGS = -std=c++20 -Igoogletest/googletest/include -Iinclude -O2 -pthread

SRC_DIR = src
TEST_DIR = tests
GTEST_DIR = googletest

GTEST_LIB_DIR = $(GTEST_DIR)/build/lib
GTEST_LIBS = -L$(GTEST_LIB_DIR) -lgtest -lgtest_main -lpthread

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) pi_number/pi_number.cpp

pi:
	$(CXX) $(CXXFLAGS) $(wildcard src/*.cpp) pi_number/pi_number.cpp -o pi_number.out
	./pi_number.out

test: $(GTEST_LIB_DIR)/libgtest.a
	$(CXX) $(CXXFLAGS) $(wildcard src/*.cpp) tests/main.cpp $(GTEST_LIBS) -o test.out
	./test.out

clean:
	rm -f pi_number.out test.out

.PHONY: pi test clean