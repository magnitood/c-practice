#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>

typedef struct Point {
	int64_t x;
	int64_t y;
} Vector;

int main()
{
	FILE *input = fopen("testinput.txt", "r");
	uint32_t ntests;
	fscanf(input, "%u\n", &ntests);

	uint32_t nvec;
	while (fscanf(input, "%u\n", &nvec) != EOF) { // causes side effect
		Vector *vec_arr[nvec];
		for (uint32_t i = 0; i < nvec; i++) {
			Vector *v = malloc(sizeof(*v));
			assert(v != NULL);
			fscanf(input, "%ld %ld\n", &v->x, &v->y);
			vec_arr[i] = v;
		}

		// bool is_counterclockwise = true;
		// for (uint32_t i = 1; i < nvec; i++) {
		// 	Vector *v1 = vec_arr[i - 1];
		// 	Vector *v2 = vec_arr[i];
		//
		// 	// compute the magnitude of the k component of the cross product
		// 	int64_t det = (v1->x * v2->y) - (v2->x * v1->y);
		// 	if (det < 0) {
		// 		is_counterclockwise = false;
		// 		break;
		// 	}
		// }
		// if (is_counterclockwise)
		// 	printf("Valid\n");
		// else
		// 	printf("Invalid\n");
	}

	return EXIT_SUCCESS;
}
