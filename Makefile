CC=gcc
CFLAGS=-g -Wall

CXX=g++
CXXFLAGS=-g -Wall -std=c++11 -I.
LDLIBS=-lm

RM=rm -f

TESTFLAGS=-I/usr/local/lib/include/
TESTLIBS=-lcheck

TARGET=main
TESTTARGET=test

SRCS=src/robot.c
OBJS=$(subst .c,.o,$(SRCS))
TESTSRCS=$(subst .c,_test.c,$(SRCS)) src/test_helpers.c src/robot_test_helpers.c
TESTOBJS=$(OBJS) $(subst .c,.o,$(TESTSRCS))

LOCALLIBSRCS=lib/hash_table_simple.c
LOCALLIBOBJS=$(subst .c,.o,$(LOCALLIBSRCS))
TESTLOCALLIBSRCS=$(subst .c,_test.c,$(LOCALLIBSRCS))
TESTLOCALLIBOBJS=$(LOCALLIBOBJS) $(subst .c,.o,$(TESTLOCALLIBSRCS))

.PHONY: default all clean

default: $(TARGET)
all: default

.PRECIOUS: $(TARGET) $(OBJECTS)

# compile only, C source
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

# compile only, C++ source
%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)


main: main.o $(OBJS) $(LOCALLIBOBJS)
	$(CC) -o bin/$@ $^ $(CCFLAGS) $(LDLIBS)


test: test.o $(TESTOBJS) $(TESTLOCALLIBOBJS)
	$(CC) $(CCFLAGS) $(TESTFLAGS) -o bin/$@ $^ $(LDLIBS) $(TESTLIBS) && \
	./bin/$@

clean:
	$(RM) $(OBJS) $(LOCALLIBOBJS)

distclean: clean
	$(RM) main.o bin/$(TARGET)

testclean: clean
	$(RM) $(OBJS) $(TESTOBJS) $(TESTLOCALLIBOBJS) bin/$(TESTTARGET)

# http://stackoverflow.com/questions/1484817/how-do-i-make-a-simple-makefile-gcc-unix
