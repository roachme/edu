SRCS=$(wildcard src/*.c)
OBJS=$(patsubst src/%.c, obj/%.o, $(SRCS))
CFLAGS=-I inc

all: wd
	@echo done


wd: $(OBJS)
	gcc $^ -o $@

init:
	if [ ! -d obj ];then 	\
		mkdir obj; 			\
	fi						
	echo 'source /usr/share/wd/wd.sh' >> ~/.bashrc
	

obj/%.o: src/%.c
	gcc -c $< -o $@ $(CFLAGS)

clean:
ifeq (wd, $(wildcard wd))
	rm wd
	rm obj/*
endif
	clear

re: clean all






install:
	cp wd /usr/local/bin/_wd
	mkdir /usr/share/wd/ -p
	cp scr/wd.sh /usr/share/wd/

uninstall:
	rm /usr/local/bin/_wd
	rm /usr/share/wd/ -rf