example: example.c
	gcc -g $^ -o example

test: example
	./example
