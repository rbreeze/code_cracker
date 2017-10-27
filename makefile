HEADERS = cs50.h

default: main

main: code_cracker.c $(HEADERS)
	gcc cs50.c code_cracker.c -o main

clean: 
	-rm -f main.o
	-rm -f main
