CC = g++
CC_FLAGS = -Wall -std=c++11

BINDIR = bin
LIBDIR = lib
LIBRARIES = $(shell find $(LIBDIR) -name *.cpp)

SRC_ENC = src/encrypt
SRC_DEC = src/decrypt
SRC_SLN = src/solution
SOURCES_ENCRYPT = $(shell find $(SRC_ENC) -name *.cpp)
SOURCES_DECRYPT = $(shell find $(SRC_DEC) -name *.cpp)
SOURCES_SOLUTION = $(shell find $(SRC_SLN) -name *.cpp)

all : $(BINDIR)/bq-encrypt $(BINDIR)/bq-decrypt $(BINDIR)/bq-solution

$(BINDIR)/bq-encrypt : $(LIBRARIES) $(SOURCES_ENCRYPT)
	$(CC) $(CC_FLAGS) $(LIBRARIES) $(SOURCES_ENCRYPT) -o $(BINDIR)/bq-encrypt
$(BINDIR)/bq-decrypt : $(LIBRARIES) $(SOURCES_DECRYPT)
	$(CC) $(CC_FLAGS) $(LIBRARIES) $(SOURCES_DECRYPT) -o $(BINDIR)/bq-decrypt
$(BINDIR)/bq-solution : $(LIBRARIES) $(SOURCES_SOLUTION)
	$(CC) $(CC_FLAGS) $(LIBRARIES) $(SOURCES_SOLUTION) -o $(BINDIR)/bq-solution



clean :
	rm -f bin/*
