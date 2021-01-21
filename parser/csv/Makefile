SRCS := $(wildcard src/*.c)
OBJS := $(wildcard src/%.c, obj/%.o, $(SRCS))
PRJ  := csv
CC   := gcc

all: $(PRJ)

$(PRJ): $(OBJS)
	gcc $(SRCS) -o $@

obj/%.o: src/%.c
	$(CC) -c $< -o $@

clean:
ifeq ($(PRJ), $(wildcard $(PRJ)))
	rm $(PRJ)
endif
	clear

re: clean all