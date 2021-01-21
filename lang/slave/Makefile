SRCS   := $(wildcard src/*.c)
OBJS   := $(patsubst src/%.c, obj/%.o, $(SRCS))
RM     := rm -rf
PRJ    := slave

CFLAGS := -I inc -Wall
LFLAGS := -lm
CC     := gcc



all: $(PRJ)

$(PRJ): $(OBJS)
	$(CC) $^ -o $@

obj/%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS)


clean:
ifeq (slave, $(wildcard slave))
	$(RM) obj/* slave
	clear
else
	clear
endif


re: clean all
