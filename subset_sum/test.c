#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// input format
// first line: no of test cases, say x having 1 <= x  <= 100
// for each test case: 
// 	no of array elements 1 <= n <= 10,000
// 	array elements array element 1 <= a <= 10,000
// 	targest sum 1 <= a <= 10,000

int random_int(int low, int high)
{
	int r = rand();
	return (r%(high - low + 1) + low);
}

int main(void)
{
	const int test_min = 1;
	const int test_max = 100;
	const int arr_count_min = 1;
	// const int arr_count_max = 1 * 10;
	const int arr_count_max = 25;
	const int elem_min = -10 * 10;
	const int elem_max = 10 * 10;
	const int target_sum_min = -10 * 10;
	const int target_sum_max = 10 * 10;

	// srand(time(NULL));
	srand(time(0));
	int test_count = random_int(test_min, test_max);
	printf("%d\n", test_count);

	for (int i = 0; i < test_count; i++) {
		int in_arr_count = random_int(arr_count_min, arr_count_max);
		printf("%d\n", in_arr_count);

		for (int i = 0; i < in_arr_count; i++) {
			printf("%d ", random_int(elem_min, elem_max));
		}
		putchar('\n');

		int target_sum = random_int(target_sum_min, target_sum_max);
		printf("%d\n", target_sum);
	}
	return 0;
}
