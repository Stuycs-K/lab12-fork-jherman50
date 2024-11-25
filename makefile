compile: fork.o
	gcc -o fork fork.o
run: fork
	./fork
fork.o: fork.c
	gcc -c fork.c
