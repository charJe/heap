test: example
	./example

example: example.c heap.o
	gcc $^ -o example

heap.o: heap.c
	gcc -c $<
