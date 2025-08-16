#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <limits.h>

#define MAX 25000

void merge_sort(int *, size_t);
void merge_sort_st(int *arr, size_t start, size_t end);
void combine(int *, int, int, int);
void *merge_sort_mt(void *);

int main()
{
	int *arr = malloc(sizeof(int) * MAX);
	printf("Filling array\n");
	for (int i = 0; i < MAX; i++) {
		arr[i] = rand();
	}
	printf("Starting Sort\n");
	merge_sort(arr, MAX);
	for (int i = 0; i < MAX; i++) {
		printf("%d\n", arr[i]);
	}
	printf("Sorted\n");
	return EXIT_SUCCESS;
}

struct merge_sort_mt_args_t {
	int *arr;
	size_t start;
	size_t end;
	size_t depth;
};

void merge_sort(int *arr, size_t size)
{
	struct merge_sort_mt_args_t merge_sort_mt_args = {arr, 0, size-1, 0};
	merge_sort_mt(&merge_sort_mt_args);
}

void merge_sort_st(int *arr, size_t start, size_t end)
{
	if (start >= end)
		return;

	int mid = (end + start) / 2;
	merge_sort_st(arr, start, mid);
	merge_sort_st(arr, mid+1, end);
	combine(arr, start, mid, end);
}

void *merge_sort_mt(void *args)
{
	struct merge_sort_mt_args_t *mt_arg = (struct merge_sort_mt_args_t *) args;
	int *arr = mt_arg->arr;
	size_t start = mt_arg->start;
	size_t end = mt_arg->end;
	size_t depth = mt_arg->depth;
	int mid = (end + start) / 2;

	// printf("MT: %lu\n", depth);

	if (start >= end)
		return NULL;

	if (depth < 6) {
		depth++;
		struct merge_sort_mt_args_t args_left = {arr, start, mid, depth};
		struct merge_sort_mt_args_t args_right = {arr, mid+1, end, depth};

		pthread_t t1 = 1;
		pthread_t t2 = 2;
		int ret1 = pthread_create(&t1, NULL, merge_sort_mt, &args_left);
		int ret2 = pthread_create(&t2, NULL, merge_sort_mt, &args_right);
		assert(!ret1);
		assert(!ret2);

		int ret3 = pthread_join(t1, NULL);
		int ret4 = pthread_join(t2, NULL);
		assert(!ret3);
		assert(!ret4);
	} else {
		merge_sort_st(arr, start, mid);
		merge_sort_st(arr, mid+1, end);
	}
	combine(arr, start, mid, end);
	return NULL;
}

void combine(int *arr, int start, int mid, int end)
{
	size_t temp_arr_size = end - start + 1;
	int *temp_arr = malloc(sizeof(int) * temp_arr_size);
	int i = start;
	int j = mid+1;
	int k = 0;
	while (i <= mid && j <= end) {
		if (arr[i] < arr[j])
			temp_arr[k++] = arr[i++];
		else
			temp_arr[k++] = arr[j++];
	}
	while (i <= mid)
		temp_arr[k++] = arr[i++];
	while (j <= end)
		temp_arr[k++] = arr[j++];

	memcpy(arr+start, temp_arr, sizeof(int) * temp_arr_size);
}
