CXX=g++
CXXFLAGS= -std=c++17 -g
ROOT_DIR:= $(shell pwd)
BOOST_DIR := /usr/include/boost

MAINEXE = 

### Test Object ###
TEST_NAME = entity_unittest
###################
TESTSOURCE = $(ROOT_DIR)/test/$(TEST_NAME).cpp

BUILD_DIR = $(ROOT_DIR)/bin
TESTEXE = $(BUILD_DIR)/tests/$(TEST_NAME)

INCLUDES = -I$(BOOST_DIR) -I. -I$(ROOT_DIR)/include -I$(ROOT_DIR)/include/graph
LIBS = -lgtest_main -lgtest -pthread
SOURCES = $(shell find src -name '*.cpp')
OBJFILES = $(addprefix $(BUILD_DIR)/, $(SOURCES:.cpp=.o))

all: $(MAINEXE) $(TESTEXE)

$(TESTEXE): $(OBJFILES)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJFILES) $(TESTSOURCE) $(LIBS) -o $@

$(MAINEXE): $(OBJFILES)
	mkdir -p $(TEST_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBS) -o $@

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

test: $(TESTEXE)

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(TESTEXE)