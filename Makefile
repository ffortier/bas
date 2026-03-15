OBJS = bas.o lexer.o
CFLAGS = -Wall -g

.PHONY: run all clean

all: bas

run: bas
	./bas

bas: $(OBJS)
	clang -o bas $(OBJS)

%.o: %.c
	clang -c $(CFLAGS) -o $@ $< -MMD -MP -MF $(@:.o=.d)

clean:
	rm -f $(OBJS) *.d bas

-include $(wildcard *.d)

