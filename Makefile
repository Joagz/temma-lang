CC=gcc
FLAGS=-fstack-clash-protection -fstack-protector-strong\
			-Wall -no-pie -Werror=format-security -Werror=implicit-function-declaration

# SOURCE DIRS
SRC_DIR=./src
SCANNER_DIR=./src/scanner
BUILD_DIR=./build
BIN_DIR=./bin
UTIL_DIR=./src/util

# OUTPUT DIRS 
SCANNER_OUT_DIR=$(BUILD_DIR)/scanner
UTIL_OUT_DIR=$(BUILD_DIR)/util

# SCANNER FILES
SCAN_SRC=$(SCANNER_DIR)/scan.c
SCAN_O=$(SCANNER_OUT_DIR)/scan.o

#DEBUG FILES 
DEBUG_SRC=$(UTIL_DIR)/debug.c 
DEBUG_O=$(UTIL_OUT_DIR)/debug.o

FILES=$(BUILD_DIR)/compiler.o $(SCAN_O) $(DEBUG_O)
INCLUDES=-I$(SRC_DIR)/ -I$(SCANNER_DIR)/ -I$(UTIL_DIR)/
DEBUG=-DDEBUG_MODE_FULL

all: $(FILES)
	$(CC) $(FLAGS) $(INCLUDES) $(FILES) -o $(BIN_DIR)/compiler

$(BUILD_DIR)/compiler.o: $(SRC_DIR)/compiler.c 
	$(CC) -c $(INCLUDES) $(DEBUG) $(SRC_DIR)/compiler.c -o $(BUILD_DIR)/compiler.o

$(SCAN_O): $(SCAN_SRC)
	$(CC) $(FLAGS) $(INCLUDES) $(DEBUG) -c $(SCAN_SRC) -o $(SCAN_O)

$(DEBUG_O): $(DEBUG_SRC)
	$(CC) $(FLAGS) $(INCLUDES) $(DEBUG) -c $(DEBUG_SRC) -o $(DEBUG_O)


clean:
	rm -f $(SCAN_O)
	rm -f $(BUILD_DIR)/compiler.o
	rm -f $(BIN_DIR)/compiler
