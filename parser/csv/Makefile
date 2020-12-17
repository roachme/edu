
all: cockroach

cockroach:
	gcc cockroach.c -o cockroach
	./cockroach

clean:
ifeq (cockroach, $(wildcard cockroach))
	rm cockroach
endif
	clear

re: clean all