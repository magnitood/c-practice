#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

typedef struct node {
	int64_t data;
	struct node *left;
	struct node *right;
} node;

node *new(int64_t data) {
	node *new = malloc(sizeof(*new));
	assert(new != NULL);
	new->data = data;
	new->left = NULL;
	new->right = NULL;
	return new;
}

int main()
{
	return EXIT_SUCCESS;
}

ssize_t insert(node *root, size_t index, int64_t data)
{
	size_t index_parent = (index - 1) / 2;
	return index;
}
