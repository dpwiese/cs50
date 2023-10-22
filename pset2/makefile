# Project directories
CWD := $(abspath $(shell pwd))
SRC := $(CWD)/src
BIN := $(CWD)/bin

# External commands
RM=/bin/rm -f

SRC_FILES := $(wildcard $(SRC)/*.c)
OUT_FILES := $(subst src,bin,$(subst .c,, $(SRC_FILES)))

.PHONY: all clean
.SILENT: all clean

all: $(OUT_FILES)

$(BIN)/%: $(SRC)/%.c
	clang $< -lcs50 -o $@

clean:
	- $(RM) $(BIN)/*
