#include <stdlib.h>
#include <stdio.h>

typedef struct _RBTreeNode {
	int					data;
	int					colour; //0 for black
	struct _RBTreeNode	*parent;
	struct _RBTreeNode	*left;
	struct _RBTreeNode	*right;
} RBTreeNode;

typedef struct RBTree {
	RBTreeNode	*root;
} RBTree;


void rotate_left(RBTree *tree, RBTreeNode *x){
	RBTreeNode *y = x->right;
	x->right = y->left;
	
	if(y->left) y->left->parent = x;
		y->parent = x->parent;
	if(x->parent == 0)
		tree->root = y;
	else if(x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	x->parent = y;
	y->left = x;
}

void rotate_right(RBTree *tree, RBTreeNode *x){
	RBTreeNode *y = x->left;
	x->left = y->right;
	
	if(y->right) y->right->parent = x;
		y->parent = x->parent;
	if(x->parent == 0)
		tree->root = y;
	else if(x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	x->parent = y;
	y->right = x;
}

#define IS_RED(x) ((x) ? ((x->colour) ? 1:0):0) 
void insert_fixup(RBTree *tree, RBTreeNode *z){
	RBTreeNode *y;
	while(IS_RED(z->parent)){
		if(z->parent == z->parent->parent->left){
			y = z->parent->parent->right;
			if(IS_RED(y)){
				z->parent->colour = 0;
				y->colour = 0;
				z->parent->parent->colour = 1;
				z = z->parent->parent;
			}
			else{
				if(z == z->parent->right){
					z = z->parent;
					rotate_left(tree,z);
				}
				z->parent->colour = 0;
				z->parent->parent->colour = 1;
				rotate_right(tree,z->parent->parent);
			}
		}
		else { //parent at right
			y = z->parent->parent->left;
			if(IS_RED(y)){
				z->parent->colour = 0;
				y->colour = 0;
				z->parent->parent->colour = 1;
				z = z->parent->parent;
			}
			else {
				if(z == z->parent->left){
					z = z->parent;
					rotate_right(tree,z);
				}
				z->parent->colour = 0;
				z->parent->parent->colour = 1;
				rotate_left(tree,z->parent->parent);
			}
		}
	}
	tree->root->colour = 0;
}

void RBTreeInsert(RBTree *tree, RBTreeNode *node){
	RBTreeNode *y = 0;
	RBTreeNode *x = tree->root;
	
	node->left = 0;
	node->right = 0;
	
	while (x != 0){
		y = x;
		if(node->data < x->data)
			x = x->left;
		else
			x = x->right;
	}
	node->parent = y;
	if(y == 0){
		tree->root = node;
	}
	else{
		if(node->data < y->data)
			y->left = node;
		else {
			y->right = node;
		}
	}
	node->colour = 1; //RED
	insert_fixup(tree,node);
}

void RBTreeDump(RBTree *tree){
	char action;
	RBTreeNode *node = tree->root;
	first:
	printf("node data %x color %x left %x right %x\n",node->data,
			node->colour,node->left,node->right);
	printf("[u]p [l]eft [r]ight [q]uit:");
	scanf("\n%c",&action);
	switch (action){
		case 'u':
			node = node->parent;
			break;
		case 'l':
			node = node->left;
			break;
		case 'r':
			node = node->right;
			break;
		case 'q':
			goto last;
			break;
		default:
			goto first;
	}
	goto first;
	
	last:
	return;
}


RBTree rbt = {0};
int main(){
	char action;
	RBTreeNode *node;
	int node_data;
	
	first:
	printf("[i]nsert [d]ump [u]nlink [q]uit:");
	scanf("\n%c",&action);
	switch (action){
		case 'd':
			RBTreeDump(&rbt);
			break;
		case 'i':
			node = (RBTreeNode*)malloc(sizeof(RBTreeNode));
			printf("Node data:");
			scanf("\n%i",&node_data);
			node->data = node_data;
			RBTreeInsert(&rbt,node);
			break;
		case 'q':
			goto last;
			break;
		default:
			printf("Unknown cmd\n");
			goto first;
			break;
	}
	goto first;
	
	last:
	return 0;
}
