/* Jaura Kernel Development
 * ***
 * Muhammad Irvan Hermawan
 * 
 * Singly-linked list management
 * */
#include <stdlib.h>
#include <stdio.h>

typedef struct _SLIST_NODE{
	struct _SLIST_NODE *next;
	int data;
} SLIST_NODE;

typedef struct _SLIST {
	SLIST_NODE *firstNode;
	SLIST_NODE *lastNode;
} SLIST;

void SListAppend(SLIST *list,SLIST_NODE *newNode){
	if(!list->lastNode){
		list->lastNode = newNode;
		list->firstNode = newNode;
		newNode->next = 0;
	}
	else {
		list->lastNode->next = newNode;
		list->lastNode = newNode;
	}
}

void SListPrepend(SLIST *list,SLIST_NODE *newNode){
	if(!list->firstNode){
		list->firstNode = newNode;
		list->lastNode = newNode;
		newNode->next = 0;
	}
	else{
		newNode->next = list->firstNode;
		list->firstNode = newNode;
	}
}
void SListUnlink(SLIST *list,SLIST_NODE *node){
	SLIST_NODE *prevNode = list->firstNode;
	if(prevNode == node) prevNode = 0;
	while(prevNode){
		if(prevNode->next == node) break;
		if(prevNode->next == 0) return; //error
		prevNode = prevNode->next;
	}
	if(!prevNode)
		list->firstNode = node->next;
	else
		prevNode->next = node->next;
	if(!node->next){
		list->lastNode = prevNode;
	}
	return;
}

void SListDump(SLIST *list){
	SLIST_NODE *node = list->firstNode;
	printf("firstNode %x lastNode %x\n",list->firstNode,list->lastNode);
	while(node){
		printf("node at %x data: %i next: %x\n",node,node->data,node->next);
		node = node->next;
	}
}

SLIST slist;
int main(){
	char action;
	SLIST_NODE *node;
	SLIST_NODE *node_addr;
	int node_data;
	
	first:
	printf("[a]ppend [p]repend [d]ump [r]emove [q]uit:");
	scanf("\n%c",&action);
	switch (action){
		case 'd':
			SListDump(&slist);
			break;
		case 'a':
			node = malloc(sizeof(SLIST_NODE));
			printf("Node data:");
			scanf("\n%i",&node_data);
			node->data = node_data;
			SListAppend(&slist,node);
			break;
		case 'p':
			node = malloc(sizeof(SLIST_NODE));
			printf("Node data:");
			scanf("\n%i",&node_data);
			node->data = node_data;
			SListPrepend(&slist,node);
			break;
		case 'r':
			printf("Node addr:");
			scanf("\n%x",&node_addr);
			SListUnlink(&slist,node_addr);
			free(node_addr);
			break;
		case 'q':
			goto last;
			break;
		default:
			printf("Pilihan tidak diketahui\n");
			goto first;
			break;
	}
	goto first;
	
	last:
	return 0;
}
