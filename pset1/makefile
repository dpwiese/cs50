# Project directories
CWD := $(abspath $(shell pwd))
SRC := $(CWD)/src
BIN := $(CWD)/bin

# One of [clang, gcc-13]. Alias gcc -> gcc-13 doesn't work with make
CC=clang

# External commands
RM=/bin/rm -f

SRC_FILES := $(wildcard $(SRC)/*.c)
OUT_FILES := $(subst src,bin,$(subst .c,, $(SRC_FILES)))

.PHONY: all clean
.SILENT: all clean

all: $(OUT_FILES)

# The -L flag and path is needed for gcc
$(BIN)/%: $(SRC)/%.c
	$(CC) $< -L/usr/local/lib -lcs50 -o $@

clean:
	- $(RM) $(BIN)/*
