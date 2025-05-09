#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include "arena.h"

typedef struct Node Node;
struct Node {
	Node *left;
	Node *right;
	uint32_t data;
};


Node *new_node(Arena *a, int data)
{
	Node *new = arena_alloc(a, sizeof(*new), 1);
	// Node *new = malloc(sizeof(Node));
	memset(new, 0, sizeof(*new));
	new->data = data;
	return new;
}

void level_order(Arena scratch, Node *root, size_t tree_size)
{
	// Node **queue = malloc(sizeof(Node *) * tree_size); // scratch purposes
	Node **queue = arena_alloc(&scratch, sizeof(*queue), tree_size);
	size_t front = 0;
	size_t back = 0;

	queue[back++] = root;

	while (front != back || queue[front] != NULL) {
		Node *temp = queue[front++];
		printf("%"PRIu32" ", temp->data);
		if (temp->left != NULL)
			queue[back++] = temp->left;

		if (temp->right != NULL)
			queue[back++] = temp->right;
	}
	putchar('\n');
}

void invert_tree(Node *root)
{
	if (root->left == NULL || root->right == NULL)
		return;

	Node *left = root->left;
	Node *right = root->right;

	uint32_t temp = left->data;
	left->data = right->data;
	right->data = temp;

	invert_tree(left);
	invert_tree(right);
}

// program to invert a binary tree
int main()
{
	Arena perm = arena_make(256 << 20); // 256 Megabytes
	Node *root = new_node(&perm, 99);
	Node *one = new_node(&perm, 1);
	Node *two = new_node(&perm, 2);
	Node *three = new_node(&perm, 3);
	Node *four = new_node(&perm, 4);
	Node *five = new_node(&perm, 5);
	Node *six = new_node(&perm, 6);
	root->left = one;
	root->right = two;

	one->left = three;
	one->right = four;
	
	two->left = five;
	two->right = six;

	level_order(perm, root, 7);
	invert_tree(root);
	level_order(perm, root, 7);

	return EXIT_SUCCESS;
}
