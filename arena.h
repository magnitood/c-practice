#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
	uintptr_t *words;
	size_t size;
	size_t capacity;
} Arena;

static inline Arena arena_make(size_t capacity)
{
	Arena a = {0};

	uintptr_t *words = (uintptr_t *) malloc(sizeof(*words) * capacity);
	if (words == NULL) {
		perror(NULL);
		exit(EXIT_FAILURE);
	}

	a.words = words;
	a.size = 0;
	a.capacity = 0;

	return a;
}

static inline void arena_destroy(Arena *a)
{
	if (a != NULL) {
		free(a->words);
		a->words = NULL;
		a->size = 0;
		a->capacity = 0;
	}
}

static inline void *arena_alloc(Arena *a, size_t type_size, size_t count)
{
	if (a == NULL)
		return malloc(type_size * count);

	size_t bytes_required = type_size * count; // TODO: check for multiplication overflow
	size_t word_size = sizeof(*(a->words));
	size_t words_to_allocate = (bytes_required + word_size - 1) / word_size; // the compiler should optimize the division out as word_size is usually a power of 2
	if (a->size + words_to_allocate > a->capacity) {
		a->size += words_to_allocate;
		return a->words + a->size;
	}

	return NULL;
}

static inline void arena_reset(Arena *a)
{
	if (a == NULL)
		return;

	a->size = 0;
}
