#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <assert.h>

int main()
{
	srand(25);
	int key = 4;
	int (*search_gcc)(int[], int, size_t);
	int (*search_clang)(int[], int, size_t);

	void *handler_gcc = dlopen("libsearch-gcc.so", RTLD_NOW);
	void *handler_clang = dlopen("libsearch-clang.so", RTLD_NOW);
	assert(handler_gcc);

	search_gcc = dlsym(handler_gcc, "search");
	search_clang = dlsym(handler_clang, "search");

	int arr[10000];
	for (int i = 0; i < 10000; i++)
		arr[i] = (rand() % 101);

	//search
	assert(search_gcc);
	int loc = search_gcc(arr, key, 10000);
	if (loc < 0)
		printf("Key not found\n");
	else
		printf("Key found at: %d\n", loc);

	exit(EXIT_SUCCESS);
}
