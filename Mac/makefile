export PATH=/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin
CC=gcc
CXX=g++ -std=c++11
#CPPFLAGS=-g $(shell root-config --cflags)
#LDFLAGS=-g $(shell root-config --ldflags)
#LDLIBS=$(shell root-config --libs)

SRCS=test.cpp
OBJS=$(subst .cc,.o,$(SRCS))

all:test

test: $(OBJS)
	$(CXX) -o test $(OBJS)
	#$(CXX) $(LDFLAGS) -o test $(OBJS) $(LDLIBS)

clean:
	rm -f test

distclean: clean
	rm -f test