#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000000

void merge_sort(int *, size_t);
void merge_sort_(int *, size_t, size_t);
void combine(int *, int, int, int);

int main()
{
	int *arr = malloc(sizeof(int) * MAX);
	printf("Filling array\n");
	for (int i = 0; i < MAX; i++) {
		arr[i] = rand();
	}
	printf("Starting Sort\n");
	merge_sort(arr, MAX);
	// for (int i = 0; i < MAX; i++) {
	// 	printf("%d\n", arr[i]);
	// }
	printf("Sorted\n");
	return EXIT_SUCCESS;
}

void merge_sort(int *arr, size_t size)
{
	merge_sort_(arr, 0, size-1);
}

void merge_sort_(int *arr, size_t start, size_t end)
{
	if (start >= end)
		return;
	int mid = (end + start) / 2;
	merge_sort_(arr, start, mid);
	merge_sort_(arr, mid+1, end);
	combine(arr, start, mid, end);
}

void combine(int *arr, int start, int mid, int end)
{
	size_t temp_arr_size = end - start + 1;
	int *temp_arr = malloc(sizeof(int) * temp_arr_size);
	int i = start;
	int j = mid+1;
	int k = 0;
	while (i <= mid && j <= end) {
		if (arr[i] < arr[j]) {
			temp_arr[k] = arr[i];
			i++;
			k++;
		} else {
			temp_arr[k] = arr[j];
			j++;
			k++;
		}
	}
	while (i <= mid) {
		temp_arr[k] = arr[i];
		k++;
		i++;
	}
	while (j <= end) {
		temp_arr[k] = arr[j];
		k++;
		j++;
	}
	// for (int l = 0; l < temp_arr_size; l++) {
	// 	arr[start+l] = temp_arr[l];
	// }
	memcpy(arr+start, temp_arr, sizeof(int) * temp_arr_size);
}
