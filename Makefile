CXX ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra -Wpedantic -Werror -Iinclude
BIN := build

.PHONY: all test clean

all: $(BIN)/flight_booking $(BIN)/train_booking

$(BIN)/%: src/%.cpp include/*.hpp | $(BIN)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BIN)/test_structures: tests/test_structures.cpp include/*.hpp | $(BIN)
	$(CXX) $(CXXFLAGS) $< -o $@

test: all $(BIN)/test_structures
	./$(BIN)/test_structures
	bash tests/smoke.sh

$(BIN):
	mkdir -p $(BIN)

clean:
	rm -rf $(BIN)
