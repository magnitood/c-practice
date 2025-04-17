clean:
	find . -not -iname "*.c" -not -type d -not -iname "Makefile" | xargs rm -rf

bit-operations: bit-operations.c
	gcc bit-operations.c -o bitoperations

test: test.c
	gcc test.c -o test -lm
