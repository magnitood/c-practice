#include <stdio.h>
#include "print_hello.h"

int main(int argc, char *argv[])
{
	for (size_t i = 1; i < argc; i++) {
		printf("%s\n", argv[i]);
	}

	return 0;
}
