#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

int main()
{
	void (*print_hi)(void);

	while (1) {
		void *handler = dlopen("./libdyn.so", RTLD_NOW);
		if (handler == NULL) {
			fprintf(stderr, "Error loading library\n");
			exit(EXIT_FAILURE);
		}

		print_hi = dlsym(handler, "print_hi");
		if (print_hi == NULL) {
			fprintf(stderr, "Error loading symbol\n");
			exit(EXIT_FAILURE);
		}

		print_hi();
	}


	return 0;
}
