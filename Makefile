CPP=g++
CXXTESTGEN?=cxxtestgen
CPPFLAGS=-I./ -std=c++11
AR=ar
ARFLAGS=rcs

all: libcproto.a

libcproto.a: cproto.o
	$(AR) $(ARFLAGS) libcproto.a cproto.o

cproto.o:
	$(CPP) $(CPPFLAGS) cproto.cpp -c -o cproto.o

test: all
	$(CXXTESTGEN) --error-printer test/MessageTests.hpp -o message.test.cpp
	$(CPP) $(CPPFLAGS) message.test.cpp -o message.test.elf
	./message.test.elf

	$(CXXTESTGEN) --error-printer test/StreamReaderTests.hpp -o stream_reader.test.cpp
	$(CPP) $(CPPFLAGS) stream_reader.test.cpp -o stream_reader.test.elf
	./stream_reader.test.elf

.PHONY: all test
