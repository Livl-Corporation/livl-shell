CC=gcc
CFLAGS=-Wall -c
LDFLAGS=-I ./include/

# Add color codes
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
NC=\033[0m # No Color

SRC_DIR=./src
INC_DIR=./include
BIN_DIR=./bin
DOC_DIR=./doc
GCOV_DIR=./gcov

GCOVFLAGS=-O0 --coverage -lgcov -Wall -g

LCOV_REPORT=report.info

SRC=$(wildcard $(SRC_DIR)/*.c)
OBJ=$(SRC:.c=.o)
EXEC=livl-shell

GEXEC=$(EXEC).cov

AR_NAME=archive_$(EXEC).tar.gz

all: message $(SRC) $(EXEC)

message:
	@echo "$(GREEN)>>> Starting the livl-bash building process... <<<$(NC)"

# To remove the .o files 
# .INTERMEDIATE: $(OBJ)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)
    
%.o:%.c | $(BIN_DIR)
	@echo "$(BLUE)Compiling $<...$(NC)"
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

$(EXEC): $(OBJ) 
	@echo "\n$(YELLOW)>>> Linking the object files... <<<$(NC)"
	$(CC) -o $(BIN_DIR)/$@ -Wall $(LDFLAGS) $(OBJ)
	@echo "\n$(GREEN)>>> Compilation finished. Executable is located in $(BIN_DIR)/$(EXEC) <<<$(NC)"
	@rm $(OBJ)

$(GEXEC):
	$(CC) $(GCOVFLAGS) -o $(GCOV_DIR)/$@ -Wall $(LDFLAGS) $(SRC)

run: all
	@echo "\n$(GREEN)>>> Running the executable... <<<$(NC)"
	@$(BIN_DIR)/$(EXEC)

doc:
	doxygen $(DOC_DIR)/doxygen.conf

gcov: $(GEXEC)
	# generate some data for gcov by calling the generated binary with various options
	find $(ROOT_DIR) -name "*.gcno" -not -path "./gcov/*" -exec mv {} $(GCOV_DIR) \;

	$(GCOV_DIR)/$(GEXEC) -h
	$(GCOV_DIR)/$(GEXEC) -i input -o output -v

	find $(ROOT_DIR) -name "*.gcda" -not -path "./gcov/*" -exec mv {} $(GCOV_DIR) \;
	gcov -o $(GCOV_DIR) $(GEXEC)
	lcov -o $(GCOV_DIR)/$(LCOV_REPORT) -c -f -d $(GCOV_DIR)
	genhtml -o $(GCOV_DIR)/report $(GCOV_DIR)/$(LCOV_REPORT)

package: gcov doc all
	rm -rf $(AR_NAME)
	tar cvfz $(AR_NAME) ./*

clean:	
	rm -rf $(OBJ)

clean-gcov:
	rm -rf $(GCOV_DIR)/*

mrproper: clean
	rm -rf $(BIN_DIR)/*
	rm -rf $(DOC_DIR)/latex/
	rm -rf $(DOC_DIR)/html/
	rm -rf $(GCOV_DIR)/*

help:
	@echo "$(GREEN)Usage: make [target]$(NC)"
	@echo "$(BLUE)Targets:"
	@echo "  all       : Compile the project."
	@echo "  run       : Run the executable."
	@echo "  doc       : Generate documentation using Doxygen."
	@echo "  gcov      : Generate code coverage data using gcov and lcov."
	@echo "  package   : Package the project into a tar.gz file."
	@echo "  clean     : Remove all object files."
	@echo "  clean-gcov: Remove all gcov-related files."
	@echo "  mrproper  : Perform a deep clean of the project."
	@echo "  help      : Show this help message.$(NC)"

.PHONY: doc
.PHONY: clean-gcov
.PHONY: run
.PHONY: message