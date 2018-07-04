#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "rb.h"
#include "bst.h"

void preorder_integer_bst(const struct bst_node *node){
	if(node == NULL)
		return;
	printf("%d ", *(int *)node->bst_data);
	if(node->bst_link[0] != NULL || node->bst_link[1] != NULL){
		putchar('(');
		preorder_integer_bst(node->bst_link[0]);
		putchar(',');
		putchar(' ');
		preorder_integer_bst(node->bst_link[1]);
		putchar(')');
	}
}

void preorder_integer_avl(const struct avl_node *node){
	if(node == NULL)
		return;
	printf("%d ", *(int *)node->avl_data);
	if(node->avl_link[0] != NULL || node->avl_link[1] != NULL){
		putchar('(');
		preorder_integer_avl(node->avl_link[0]);
		putchar(',');
		putchar(' ');
		preorder_integer_avl(node->avl_link[1]);
		putchar(')');
	}
}

void preorder_integer_rb(const struct rb_node *node){
	if(node == NULL)
		return;
	printf("%d ", *(int *)node->rb_data);
	if(node->rb_link[0] != NULL || node->rb_link[1] != NULL){
		putchar('(');
		preorder_integer_rb(node->rb_link[0]);
		putchar(',');
		putchar(' ');
		preorder_integer_rb(node->rb_link[1]);
		putchar(')');
	}
}

void inorder_integer_rb(const struct rb_node *node){
	if(node == NULL)
		return;
	if(node->rb_link[0] != NULL)
		inorder_integer_rb(node->rb_link[0]);
	printf("%d ", *(int *)node->rb_data);
	if(node->rb_link[1] != NULL)
		inorder_integer_rb(node->rb_link[1]);
}

void inorder_integer_bst(const struct bst_node *node){
	if(node == NULL)
		return;
	if(node->bst_link[0] != NULL)
		inorder_integer_bst(node->bst_link[0]);
	printf("%d ", *(int *)node->bst_data);
	if(node->bst_link[1] != NULL)
		inorder_integer_bst(node->bst_link[1]);
}

void inorder_integer_avl(const struct avl_node *node){
	if(node == NULL)
		return;
	if(node->avl_link[0] != NULL)
		inorder_integer_avl(node->avl_link[0]);
	printf("%d ", *(int *)node->avl_data);
	if(node->avl_link[1] != NULL)
		inorder_integer_avl(node->avl_link[1]);
}

void preorder_string_bst(const struct bst_node *node){
	if(node == NULL)
		return;
	printf("%s ", (char *)node->bst_data);
	if(node->bst_link[0] != NULL || node->bst_link[1] != NULL){
		putchar('(');
		preorder_string_bst(node->bst_link[0]);
		putchar(',');
		putchar(' ');
		preorder_string_bst(node->bst_link[1]);
		putchar(')');
	}
}

void preorder_string_rb(const struct rb_node *node){
	if(node == NULL)
		return;
	printf("%s ", (char *)node->rb_data);
	if(node->rb_link[0] != NULL || node->rb_link[1] != NULL){
		putchar('(');
		preorder_string_rb(node->rb_link[0]);
		putchar(',');
		putchar(' ');
		preorder_string_rb(node->rb_link[1]);
		putchar(')');
	}
}

void preorder_string_avl(const struct avl_node *node){
	if(node == NULL)
		return;
	printf("%s ", (char *)node->avl_data);
	if(node->avl_link[0] != NULL || node->avl_link[1] != NULL){
		putchar('(');
		preorder_string_avl(node->avl_link[0]);
		putchar(',');
		putchar(' ');
		preorder_string_avl(node->avl_link[1]);
		putchar(')');
	}
}

void inorder_string_avl(const struct avl_node *node){
	if(node == NULL)
		return;
	if(node->avl_link[0] != NULL)
		inorder_string_avl(node->avl_link[0]);
	printf("%s ", (char *)node->avl_data);
	if(node->avl_link[1] != NULL)
		inorder_string_avl(node->avl_link[1]);
}

void inorder_string_bst(const struct bst_node *node){
	if(node == NULL)
		return;
	if(node->bst_link[0] != NULL)
		inorder_string_bst(node->bst_link[0]);
	printf("%s ", (char *)node->bst_data);
	if(node->bst_link[1] != NULL)
		inorder_string_bst(node->bst_link[1]);
}

void inorder_string_rb(const struct rb_node *node){
	if(node == NULL)
		return;
	if(node->rb_link[0] != NULL)
		inorder_string_rb(node->rb_link[0]);
	printf("%s ", (char *)node->rb_data);
	if(node->rb_link[1] != NULL)
		inorder_string_rb(node->rb_link[1]);
}

int int_compare(const void *pa, const void *pb, void *param){
	int a = *(const int *)pa; int b = *(const int *)pb;
	if(a < b)
		return -1;
	else if(a > b)
		return +1;
	else
		return 0;
}

int string_compare(const void *pa, const void *pb, void *param){
	char *a = (char *)pa; char *b = (char *)pb;
	return strcmp(a, b);
}

int main(void){
	struct avl_table *tree;
	struct bst_table *bst;
	struct rb_table *rb;
#ifndef INTEGER	
	tree = avl_create(string_compare, NULL, NULL);
	bst = bst_create(string_compare, NULL, NULL);
	rb = rb_create(string_compare, NULL, NULL);

	char s[200];
	int i;
	for(i = 0; i < 32; i++){
		gets(s);
		char *element = (char *)malloc(sizeof(char) * 200);
		strcpy(element, s);
		void *a = avl_probe(tree, element);
		void *b = bst_probe(bst, element);
		void *r = rb_probe(rb, element);
	}
	preorder_string_avl(tree->avl_root);
	putchar('\n');
	preorder_string_bst(bst->bst_root);
	putchar('\n');
	preorder_string_rb(rb->rb_root);
	putchar('\n');
	#ifdef DEBUG
		inorder_string_avl(tree->avl_root);
		putchar('\n');
		inorder_string_avl(tree->avl_root);
		putchar('\n');
		inorder_string_avl(tree->avl_root);
		putchar('\n');
	#endif

#else
	tree = avl_create(int_compare, NULL, NULL);
	bst = bst_create(int_compare, NULL, NULL);
	rb = rb_create(int_compare, NULL, NULL);
	
	int i;
	while(scanf("%d", &i) != EOF){
		int *element = (int *)malloc(sizeof(int));
		*element = i;
		void *a = avl_probe(tree, element);
		void *b = bst_probe(bst, element);
		void *r = rb_probe(rb, element);
	}
	preorder_integer_avl(tree->avl_root);
	puts("");
	preorder_integer_bst(bst->bst_root);
	puts("");
	preorder_integer_rb(rb->rb_root);
	puts("");
	#ifdef DEBUG
		inorder_integer_bst(bst->bst_root);
		putchar('\n');
		inorder_integer_avl(tree->avl_root);
		putchar('\n');
		inorder_integer_rb(rb->rb_root);
		putchar('\n');
	#endif
#endif
	return 0;
}