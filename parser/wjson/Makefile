SRC=$(wildcard *.c)
OBJ=$(patsubst %.c, %.o, $(SRC))


all: wjson

%.o: %.c
	gcc -c $< -o $@

wjson: $(OBJ)
	gcc $^ -o $@

run:
	./wjson

clean:
	rm wjson

re: clean all
