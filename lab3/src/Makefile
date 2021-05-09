CXX := g++
TARGET := 0710006_lab3
CXXFLAGS := -std=c++17 -Wall -Wextra -O3
SRC_DIRS := .
SRCS := $(wildcard $(SRC_DIRS:=/*.cpp))
DEPS := $(SRCS:.cpp=.d)
CUDD := ../cudd-3.0.0
INCLUDE := -I $(CUDD)/cudd -I $(CUDD)/util -I $(CUDD)
LINKER := $(CUDD)/cudd/.libs/libcudd.a -lm
					

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $< $(LINKER)

clean:
	rm -rf $(TARGET) $(DEPS)

ifeq (test,$(firstword $(MAKECMDGOALS)))
	TEST_CASE_ID := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
	$(eval $(TEST_CASE_ID):;@:)
endif

test: $(TARGET)
	@echo test on case$(TEST_CASE_ID)

.PHONY: all clean test
-include $(DEPS)
