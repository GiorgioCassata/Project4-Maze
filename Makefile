CC=g++
CFLAGS=-c -g -O3 -std=c++14
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBS=
LDFLAGS=
PROGRAM=a.out

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) -o $(PROGRAM) $(OBJECTS) $(LDFLAGS) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $<

depend: .depend

.depend: $(SOURCES)
	rm -f .depend
	$(CC) $(CFLAGS) -MM $^ >> .depend;

include .depend

clean:
	rm -f .depend $(OBJECTS)

erase:
	rm -f .depend $(OBJECTS) $(PROGRAM)

run: all
	./$(PROGRAM)
