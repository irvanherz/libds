/* Jaura Kernel Development
 * ***
 * Muhammad Irvan Hermawan
 * 
 * Doubly-linked list management
 * */


typedef struct _DLIST_NODE{
	struct _DLIST_NODE *next;
	struct _DLIST_NODE *prev;
	int data;
} DLIST_NODE;

typedef struct _DLIST {
	DLIST_NODE *firstNode;
	DLIST_NODE *lastNode;
} DLIST;


void DListInsertAfter(DLIST *list,DLIST_NODE *node,DLIST_NODE *newNode){
	if(!node){ //nothing? append!
		if(!list->lastNode){
			list->lastNode = newNode;
			list->firstNode = newNode;
			newNode->prev = 0;
			newNode->next = 0;
		}
		else {
			newNode->next = 0;
			newNode->prev = list->lastNode;
			list->lastNode->next = newNode;
			list->lastNode = newNode;
		}
		return;
	}
	newNode->prev = node;
	if(!node->next){
		list->lastNode = newNode;
	}
	else {
		newNode->next = node->next;
		node->next->prev = newNode;
		node->next = newNode;
	}
}

void DListInsertBefore(DLIST *list,DLIST_NODE *node,DLIST_NODE *newNode){
	if(!node) //nothing? prepend!
	{
		if(!list->firstNode){
			list->firstNode = newNode;
			list->lastNode = newNode;
			newNode->prev = 0;
			newNode->next = 0;
		}
		else{
			newNode->prev = 0;
			newNode->next = list->firstNode;
			list->firstNode->prev = newNode;
			list->firstNode = newNode;
		}
		return;
	}
	newNode->next = node;
	if(!node->prev){
		list->firstNode = newNode;
	}
	else {
		newNode->prev = node->prev;
		node->prev->next = newNode;
		node->prev = newNode;
	}
}

void DListPrepend(DLIST *list,DLIST_NODE *newNode){
	if(!list->firstNode){
		list->firstNode = newNode;
		list->lastNode = newNode;
		newNode->prev = 0;
		newNode->next = 0;
	}
	else{
		newNode->prev = 0;
		newNode->next = list->firstNode;
		list->firstNode->prev = newNode;
		list->firstNode = newNode;
	}
}

void DListAppend(DLIST *list,DLIST_NODE *newNode){
	if(!list->lastNode){
		list->lastNode = newNode;
		list->firstNode = newNode;
		newNode->prev = 0;
		newNode->next = 0;
	}
	else {
		newNode->next = 0;
		newNode->prev = list->lastNode;
		list->lastNode->next = newNode;
		list->lastNode = newNode;
	}
}

void DListUnlink(DLIST *list,DLIST_NODE *node){
	if(!node->prev)
		list->firstNode = node->next;
	else
		node->prev->next = node->next;
	if(!node->next){
		list->lastNode = node->prev;
	}
	else
		node->next->prev = node->prev;
}

void DListDump(DLIST *list){
	DLIST_NODE *node = list->firstNode;
	while(node){
		printf("node at %x data: %i prev: %x next: %x\n",node,node->data,node->prev,node->next);
		node = node->next;
	}
}

DLIST dlist = {0,0};
int main(){
	char action;
	DLIST_NODE *node;
	DLIST_NODE *node_addr;
	int node_data;
	
	first:
	printf("[a]ppend [p]repend Insert a[f]ter Insert [b]efore [d]ump [r]emove [q]uit:");
	scanf("\n%c",&action);
	switch (action){
		case 'd':
			DListDump(&dlist);
			break;
		case 'a':
			node = malloc(sizeof(DLIST_NODE));
			printf("Node data:");
			scanf("\n%i",&node_data);
			node->data = node_data;
			DListAppend(&dlist,node);
			break;
		case 'p':
			node = malloc(sizeof(DLIST_NODE));
			printf("Node data:");
			scanf("\n%i",&node_data);
			node->data = node_data;
			DListPrepend(&dlist,node);
			break;
		case 'f':
			node = malloc(sizeof(DLIST_NODE));
			printf("Node addr (hex):");
			scanf("\n%x",&node_addr);
			printf("Node data:");
			scanf("\n%i",&node_data);
			node->data = node_data;
			DListInsertAfter(&dlist,node_addr,node);
			break;
		case 'b':
			node = malloc(sizeof(DLIST_NODE));
			printf("Node addr (hex):");
			scanf("\n%x",&node_addr);
			printf("Node data:");
			scanf("\n%i",&node_data);
			node->data = node_data;
			DListInsertBefore(&dlist,node_addr,node);
			break;
		case 'r':
			node = malloc(sizeof(DLIST_NODE));
			printf("Node addr (hex):");
			scanf("\n%x",&node_addr);
			DListUnlink(&dlist,node_addr);
			free(node_addr);
			break;
		case 'q':
			goto last;
			break;
		default:
			printf("Invalid option\n");
			goto first;
			break;
	}
	goto first;
	
	last:
	return 0;
}
