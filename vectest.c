#include <stdio.h>
#include "vec.h"


typedef struct llnode {
	int data;
	struct llnode *next;
} llnode;

typedef vec(int) vec_int;

vec_int *get_list();

int main()
{
	vec(llnode) ptr = INIT_VEC;
	vec_int *p_list_of_number = get_list();
	vec_int list_of_number = *p_list_of_number;
	for (size_t i = 0; i < list_of_number.length; i++) {
		printf("%d\n", list_of_number.arr[i]);
	}
}

vec_int *get_list()
{
	vec_int *ptr = malloc(sizeof(*ptr));
	vec_push_back(*ptr, 1);
	return ptr;
}
