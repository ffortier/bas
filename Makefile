OBJS = lexer.o parser.o
TESTSRCS = $(wildcard *_test.c)
TESTS = $(TESTSRCS:.c=.log)
CFLAGS = -Wall -g

.PHONY: run all clean test

all: bas test

run: bas
	./bas

test: $(TESTS)

bas: bas.o $(OBJS)
	clang -o bas $^

%.o: %.c
	clang -c $(CFLAGS) -o $@ $< -MMD -MP -MF $(@:.o=.d)

%_test: %_test.o $(OBJS)
	clang -o $@ $^

%_test.log: %_test
	./$< > $@

clean:
	rm -f $(OBJS) *.d *_test *_test.log *_test.o bas
	
-include $(wildcard *.d)

