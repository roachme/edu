SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp, obj/%.o, $(SRCS))
RM     := rm -rf
PRJ    := simdb

CFLAGS := -I inc -Wall
LFLAGS := -lm
CC     := g++


all: $(PRJ)


init:
	test -e obj  || mkdir obj
	test -e data || mkdir data
	test -e src  || mkdir src
	test -e bin  || mkdir bin




$(PRJ): $(OBJS)
	$(CC) $^ -o $@


obj/%.o: src/%.cpp
	$(CC) -fpic -c $< -o $@ $(CFLAGS)

_clean:
ifeq ($(PRJ), $(wildcard $(PRJ)))
	$(RM) $(PRJ) 
	$(RM) obj/*
endif
	clear


clean:
	test  $(PRJ)  && $(RM) $(PRJ)
	test  obj    && $(RM) obj
	test  bin    && $(RM) bin
	test  lib    && $(RM) lib


re: _clean all


lib.so: $(OBJS)
	gcc -shared $^ -o lib/$@


py:
	clear
	python3 gui/gui.py


