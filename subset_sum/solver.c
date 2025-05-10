#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
	int *data;
	size_t size;
} Arr;

Arr solve(Arr in, int target_sum)
{
	int *data = NULL;
	size_t size = 0;
	for (unsigned int i = 0; i < ((unsigned int) 1 << in.size); i++) { // 1 << in.size computers 2 ** in.size
		
		int *subset = malloc(sizeof(*subset) * in.size);
		size_t top = 0;
		int acc = 0;
		for (size_t j = 0; j < in.size; j++) {
			if ((i >> j) & 1) {
				subset[top++] = in.data[j];
				acc += in.data[j];
			}
		}

		if (acc == target_sum) {
			data = &subset[0];
			size = top;
			break;
		}
	}

	return (Arr) {
		.data = data,
		.size = size,
	};
}

int main(void)
{
	int test_count = 0;
	scanf("%d", &test_count);

	for (int i = 0; i < test_count; i++) {
		int in_arr_count = 0;
		scanf("%d", &in_arr_count);

		int *arr = malloc(sizeof(*arr) * in_arr_count);
		for (int i = 0; i < in_arr_count; i++)
			scanf("%d", &arr[i]);

		int target_sum = 0;
		scanf("%d", &target_sum);

		Arr in = { .data = arr, .size = in_arr_count };
		Arr result = solve(in, target_sum);

		if (result.size) {
			printf("[ ");
			for (size_t i = 0; i < result.size; i++)
				printf("%d ", result.data[i]);
			printf("]\n");
		} else
			printf("Not possible\n");
	}
	return 0;
}
