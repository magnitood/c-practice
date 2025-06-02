#!/usr/bin/env bash
set -xe

# gcc -c main.c
# gcc -c dyn.c

main() {
	gcc -Wall -Wextra main.c -o main
}

dyn() {
	gcc -Wall -Wextra -c dyn.c -fPIC
	gcc -Wall -Wextra -shared dyn.o -o libdyn.so
	rm -rf dyn.o
}

dyn
