SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c, obj/%.o, $(SRC))
CFLAGS=-I inc


all: slave

obj/%.o: src/%.c
	@gcc -c $< -o $@ $(CFLAGS)

slave: $(OBJ)
	@gcc  $^ -o $@
	./$@


clean:
ifeq (slave, $(wildcard slave))
	@rm -rf obj/*.o slave
	clear
else
	clear
endif


re: clean all
