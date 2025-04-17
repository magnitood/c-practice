#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
	int data;
	struct Node * next;
} NODE;

typedef struct SinglyLinkedList {
	NODE * head;
} SLL; 

struct SinglyLinkedList * 
open()
{
	struct SinglyLinkedList * pSSL = (struct SinglyLinkedList *) malloc(sizeof(struct SinglyLinkedList));
	if(pSSL == NULL)
		fprintf(stderr, "Initialising Linked List Failed\n");
	pSSL->head = NULL;
	return pSSL;
}

void 
close(struct SinglyLinkedList * pSSL)
{
	free(pSSL);
}

void 
__insert_beg(struct SinglyLinkedList * pSSL, int data)
{

	if(pSSL->head == NULL) {
		struct Node * pNode = (struct Node *) malloc(sizeof(struct Node));
		pNode->data = data;
		pNode->next = NULL;
		pSSL->head = pNode;
	}

	struct Node * temp_pNode = pSSL->head;
	struct Node * pNode = (struct Node *) malloc(sizeof(struct Node));
	pNode->data = data;
	pNode->next = temp_pNode;
	pSSL->head = pNode;
}



int main()
{
	printf("Hello World\n");
	return 0;
}
