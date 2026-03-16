OBJS = build/lexer.o build/parser.o
TESTSRCS = $(wildcard src/*_test.c)
TESTS = $(patsubst src/%.c,build/%.log,$(TESTSRCS))
CFLAGS = -Wall -g

.PHONY: run all clean test

all: bas test

run: bas
	./bas

test: $(TESTS)

bas: build/bas.o $(OBJS)
	clang -o bas $^

build/%.o: src/%.c | build
	clang -c $(CFLAGS) -o $@ $< -MMD -MP -MF $(@:.o=.d)

build/%_test: build/%_test.o $(OBJS) | build
	clang -o $@ $^

build/%_test.log: build/%_test | build
	./$< > $@

build:
	mkdir $@

clean:
	rm -rf build/ bas
	
-include $(wildcard build/*.d)

