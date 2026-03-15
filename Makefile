OBJS = bas.o lexer.o
TESTSRCS = $(wildcard *_test.c)
TESTS = $(TESTSRCS:.c=)
CFLAGS = -Wall -g

.PHONY: run all clean test

all: bas test

run: bas
	./bas

test: $(TESTS)

bas: $(OBJS)
	clang -o bas $(OBJS)

%.o: %.c
	clang -c $(CFLAGS) -o $@ $< -MMD -MP -MF $(@:.o=.d)

%_test: %_test.o %.o
	clang -o $@ $^
	./$@

clean:
	rm -f $(OBJS) *.d *_test bas

-include $(wildcard *.d)

