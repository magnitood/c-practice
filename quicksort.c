#include <stdio.h>
#include <stdlib.h>

int partition(int arr[], size_t beg, size_t end);
void quicksort_(int arr[], size_t beg, size_t end);
void quicksort(int arr[], size_t size);

int main()
{
	size_t size = 22;
	int arr[size];

	for (size_t i = 0; i < size; i++)
		arr[i] = rand();

	quicksort(arr, size);

	for (size_t i = 0; i < size; i++)
		printf("%d\n", arr[i]);
}

void quicksort(int arr[], size_t size)
{
	quicksort_(arr, 0, size-1);
}

void quicksort_(int arr[], size_t beg, size_t end)
{
	// base case
	if (end <= beg)
		return;

	// recursive case
	size_t pos = partition(arr, beg, end);
	quicksort_(arr, beg, pos-1);
	quicksort_(arr, pos+1, end);
}

int partition(int arr[], size_t beg, size_t end)
{
	int pivot_idx = end;
	int partitioned_idx = beg;

	for (size_t i = beg; i < end; i++) {
		if (arr[i] < arr[pivot_idx]) {
			int temp = arr[partitioned_idx];
			arr[partitioned_idx] = arr[i];
			arr[i] = temp;
			partitioned_idx++;
		}
	}

	int temp = arr[partitioned_idx];
	arr[partitioned_idx] = arr[pivot_idx];
	arr[pivot_idx] = temp;

	return partitioned_idx;
}
