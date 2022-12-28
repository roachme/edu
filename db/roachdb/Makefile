DEPS=$(wildcard inc/*.h)
SRCS=$(wildcard src/*.c)
OBJS=$(patsubst src/%.c, obj/%.o, $(SRCS))
CFLAGS=-I inc
CC=gcc

all: roach


obj/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

roach: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	@rm -rf obj/*

re: clean all
