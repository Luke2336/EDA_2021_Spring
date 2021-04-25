CXX := g++
TARGET := 0710006_lab2.o
CXXFLAGS := -std=c++17 -Wall -Wextra -O3 -fopenmp
SRC_DIRS := .
SRCS := $(wildcard $(SRC_DIRS:=/*.cpp))
DEPS := $(SRCS:.cpp=.d)

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -MMD $< -o $@

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
