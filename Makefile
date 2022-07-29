CC = gcc

BUILDDIR ?= bin

TARGET := $(BUILDDIR)/converter

.phony: all clean test

__dirs := $(shell mkdir -p ${BUILDDIR})

$(TARGET): 
	$(CC) src/converter.c -o $(TARGET)

clean: 
	$(RM) -r $(BUILDDIR)

test: 
	make
	./$(TARGET) maf/inputFile.maf out
