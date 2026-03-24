OBJS = build/lexer.o build/parser.o build/listing.o build/interpreter.o
TESTSRCS = $(wildcard src/*_test.c)
TESTS = $(patsubst src/%.c,build/%.log,$(TESTSRCS))
CFLAGS = -Wall -Wextra -Wno-unused-parameter -Werror -g -Isrc/ -Iexternal/include
LIBS = external/bin/libslog.a
INCLUDES = external/include/slog.h external/include/minunit.h

.PHONY: run all clean test

all: bas test

run: bas
	@reset
	./bas

clean:
	rm -rf build/ bas

test: $(TESTS)

bas: build/bas.o $(OBJS) $(LIBS)
	clang -o bas $^

build/%.o: src/%.c | build external/.stamp
	clang -c $(CFLAGS) -o $@ $< -MMD -MP -MF $(@:.o=.d)

build/%_test: build/%_test.o $(OBJS) $(LIBS) | build
	clang -o $@ $^

build/%_test.log: build/%_test | build
	./$< 2> $@ || { echo; echo "====" $@ "====";  cat $@; echo "===="; }

build:
	mkdir -p $@

external/.stamp: bsl bsl-deps.json
	./bsl

	# slog
	$(MAKE) -C external/github/kala13x/slog slog.o
	(cd external/github/kala13x/slog && ar rcs libslog.a slog.o)
	$(MAKE) -C external/github/kala13x/slog INSTALL_BIN=$(CURDIR)/external/bin INSTALL_INC=$(CURDIR)/external/include install

	#minunit
	cp external/github/siu/minunit/minunit.h external/include

	touch external/.stamp
	
-include $(wildcard build/*.d)

