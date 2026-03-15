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

%_test: %_test.c %.o
	clang -o $@ $^
	./$@

clean:
	rm -f $(OBJS) *.d bas

-include $(wildcard *.d)

