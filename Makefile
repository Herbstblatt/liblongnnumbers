CXX=g++
CFLAGS=-c -std=c++20 -O3 -Iinclude -Iexternal
BUILD_DIR=build
SRC_DIR=src
TEST_DIR=tests
EXAMPLES_DIR=examples

build: ariphmetics comparsions constructors conversions misc
	cd $(BUILD_DIR) ; ar r liblongnumbers.a \
		$(SRC_DIR)/ariphmetics.o $(SRC_DIR)/comparsions.o \
		$(SRC_DIR)/constructors.o $(SRC_DIR)/conversions.o \
		$(SRC_DIR)/misc.o

test: build-tests
	./$(BUILD_DIR)/test.out

pi: build-pi
	./$(BUILD_DIR)/pi.out


build-tests: build test-main test-ariphmetics test-comparsions test-conversions
	$(CXX) -L$(BUILD_DIR) $(BUILD_DIR)/$(TEST_DIR)/main.o \
		$(BUILD_DIR)/$(TEST_DIR)/ariphmetics.o \
		$(BUILD_DIR)/$(TEST_DIR)/comparsions.o \
		$(BUILD_DIR)/$(TEST_DIR)/conversions.o \
		-llongnumbers \
		-o $(BUILD_DIR)/test.out

build-pi: build pi-main
	$(CXX) -L$(BUILD_DIR) $(BUILD_DIR)/$(EXAMPLES_DIR)/pi.o -llongnumbers -o $(BUILD_DIR)/pi.out



ariphmetics: $(SRC_DIR)/ariphmetics.cpp
	mkdir -p $(BUILD_DIR)/$(SRC_DIR)
	$(CXX) $(CFLAGS) $(SRC_DIR)/ariphmetics.cpp -o $(BUILD_DIR)/$(SRC_DIR)/ariphmetics.o

comparsions: $(SRC_DIR)/comparsions.cpp
	mkdir -p $(BUILD_DIR)/$(SRC_DIR)
	$(CXX) $(CFLAGS) $(SRC_DIR)/comparsions.cpp -o $(BUILD_DIR)/$(SRC_DIR)/comparsions.o

constructors: $(SRC_DIR)/constructors.cpp
	mkdir -p $(BUILD_DIR)/$(SRC_DIR)
	$(CXX) $(CFLAGS) $(SRC_DIR)/constructors.cpp -o $(BUILD_DIR)/$(SRC_DIR)/constructors.o

conversions: $(SRC_DIR)/conversions.cpp
	mkdir -p $(BUILD_DIR)/$(SRC_DIR)
	$(CXX) $(CFLAGS) $(SRC_DIR)/conversions.cpp -o $(BUILD_DIR)/$(SRC_DIR)/conversions.o

misc: $(SRC_DIR)/misc.cpp
	mkdir -p $(BUILD_DIR)/$(SRC_DIR)
	$(CXX) $(CFLAGS) $(SRC_DIR)/misc.cpp -o $(BUILD_DIR)/$(SRC_DIR)/misc.o


test-main: $(TEST_DIR)/main.cpp
	mkdir -p $(BUILD_DIR)/$(TEST_DIR)
	$(CXX) $(CFLAGS) $(TEST_DIR)/main.cpp -o $(BUILD_DIR)/$(TEST_DIR)/main.o

test-ariphmetics: $(TEST_DIR)/ariphmetics.cpp
	mkdir -p $(BUILD_DIR)/$(TEST_DIR)
	$(CXX) $(CFLAGS) $(TEST_DIR)/ariphmetics.cpp -o $(BUILD_DIR)/$(TEST_DIR)/ariphmetics.o

test-comparsions: $(TEST_DIR)/comparsions.cpp
	mkdir -p $(BUILD_DIR)/$(TEST_DIR)
	$(CXX) $(CFLAGS) $(TEST_DIR)/comparsions.cpp -o $(BUILD_DIR)/$(TEST_DIR)/comparsions.o

test-conversions: $(TEST_DIR)/conversions.cpp
	mkdir -p $(BUILD_DIR)/$(TEST_DIR)
	$(CXX) $(CFLAGS) $(TEST_DIR)/conversions.cpp -o $(BUILD_DIR)/$(TEST_DIR)/conversions.o


pi-main: $(EXAMPLES_DIR)/pi.cpp
	mkdir -p $(BUILD_DIR)/$(EXAMPLES_DIR)
	$(CXX) $(CFLAGS) $(EXAMPLES_DIR)/pi.cpp -o $(BUILD_DIR)/$(EXAMPLES_DIR)/pi.o