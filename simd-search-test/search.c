#include "search.h"

int search(int arr[], int key, size_t size)
{
	int ret = -1;
	for (size_t i = 0; i < size; i++) {
		if (arr[i] == key) {
			ret = i;
			break;
		}
	}
	return ret;
}
