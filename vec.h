#include <stdlib.h>
#include <assert.h>

#ifndef CUSTOM_DYN_ARR_VEC
#define CUSTOM_DYN_ARR_VEC

#define vec(type)\
	struct {\
		type *arr;\
		size_t capacity;\
		size_t length;\
	}\

#define INIT_VEC { .arr = NULL, .capacity = 0, .length = 0 };
#define MIN_VEC_CAP 256

#define vec_push_back(vec, item)\
	do {\
		if (((vec)).length >= (vec).capacity) {\
			if ((vec).capacity == 0)\
				(vec).capacity = MIN_VEC_CAP;\
			else\
				(vec).capacity *= 2;\
			(vec).arr = realloc((vec).arr, (vec).capacity * sizeof((vec).arr));\
		}\
		(vec).arr[(vec).length++] = (item);\
	} while(0)\

#define vec_free(vec)\
	do {\
		free((vec).arr);\
		(vec).arr = NULL;\
		(vec).capacity = 0;\
		(vec).length = 0;\
	} while(0)\

#endif /* CUSTOM_DYN_ARR_VEC */
