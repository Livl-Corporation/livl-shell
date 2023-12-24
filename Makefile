CC=gcc
CFLAGS=-Wall -c
LDFLAGS=-I ./include/

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

all: $(SRC) $(EXEC)

run: all
	@echo "Running the executable..."
	@$(BIN_DIR)/$(EXEC) && echo "Execution successful!"

# To remove the .o files 
.INTERMEDIATE: $(OBJ)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)
    
%.o:%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

$(EXEC): $(OBJ) 
	$(CC) -o $(BIN_DIR)/$@ -Wall $(LDFLAGS) $(OBJ)

$(GEXEC):
	$(CC) $(GCOVFLAGS) -o $(GCOV_DIR)/$@ -Wall $(LDFLAGS) $(SRC)

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

.PHONY: doc
.PHONY: clean-gcov
.PHONY: run