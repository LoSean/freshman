#include <stdio.h>
#include <stdlib.h>
#include "avl_ntudsa.h"
#define MAXMEN 100002 

struct owner{
	int id; 
	struct avl_table *garage;
};
typedef struct owner Owner;

struct game{
	int i_th_game;
	int height;
	int price;
	struct game *parent;
	struct owner *belong;
};
typedef struct game Game;

typedef long long int Long;

void preorder(const struct avl_node *node){
	if(node == NULL)
		return;
	printf("%d-%d", (int)node->avl_cnt, (int)node->avl_data);
	if(node->avl_link[0] != NULL || node->avl_link[1] != NULL){
		putchar('(');
		preorder(node->avl_link[0]);
		putchar(',');
		putchar(' ');
		preorder(node->avl_link[1]);
		putchar(')');
	}
}

Game* find(Game *gset, int game){
	
	if(gset[game].parent == NULL)
		return &gset[game];

	Game *tmp = &gset[game];
	while(tmp->parent != NULL)
		tmp = tmp->parent;
	return tmp;
}

void mergea_to_b(struct avl_node *insert, struct avl_table *receive){
	if(insert == NULL)
		return;
	//int *data = (int *)malloc(sizeof(int));/*allocate new memory*/
	//*data = insert->avl_data;
	avl_probe(receive, insert->avl_data);
	if(insert->avl_link[0] != NULL || insert->avl_link[1] != NULL){
		mergea_to_b(insert->avl_link[0], receive);
		mergea_to_b(insert->avl_link[1], receive);	
	}
}

struct avl_table *mergetree(struct avl_table *tree1, struct avl_table *tree2){
	if(tree1->avl_count < tree2->avl_count){
		mergea_to_b(tree2->avl_root, tree1);
		return tree1;
	}
	else{
		mergea_to_b(tree2->avl_root, tree1);
		return tree1;
	}
}

void mergeowner(Owner *oset, Game *groot1, Game *groot2){
	if(groot1->height < groot2->height){
		oset[groot1->belong->id].garage = mergetree(groot1->belong->garage, groot2->belong->garage);
		groot2->belong = groot1->belong;
		groot1->parent = groot2;
	}
	else if(groot1->height == groot2->height){
		oset[groot1->belong->id].garage = mergetree(groot1->belong->garage, groot2->belong->garage);
		groot2->parent = groot1;
		groot1->height++;
	}
	else{
		oset[groot1->belong->id].garage = mergetree(groot1->belong->garage, groot2->belong->garage);
		groot2->parent = groot1;
	}
}

void borrow(Owner *oset, Game *gset){
	int game1, game2;
	scanf("%d%d", &game1, &game2);

	Game *groot1 = find(gset, game1-1);
	Game *groot2 = find(gset, game2-1);
	//printf("%d %d\n", groot1->belong->id, groot2->belong->id);/*print game1 borrow game2*/
	if(groot1->belong->id == groot2->belong->id)
		return;
	else
		mergeowner(oset, groot1, groot2);
}

int int_compare(const void *pa, const void *pb, void *param){
	int a = *(const int *)pa; int b = *(const int *)pb;
	if(a < b)
		return -1;
	else
		return 1;
}

void buygames(struct avl_node *root, Long *s, int *size){
	if(root == NULL)
		return;
	if(root->avl_data * root->avl_cnt + root->avl_sum[0] + root->avl_sum[1] <= *s){
		*size += (root->avl_cnt + root->avl_cnode[0] + root->avl_cnode[1]);
		return; 
	}
	if(root->avl_data * root->avl_cnt + root->avl_sum[0] <= *s){
		*size += (root->avl_cnt + root->avl_cnode[0]);
		*s -= (root->avl_data * root->avl_cnt + root->avl_sum[0]);
		buygames(root->avl_link[1], s, size);
		return;
	}
	else if(root->avl_data * root->avl_cnt + root->avl_sum[0] > *s){
		int i;
		for(i = root->avl_cnt-1; i > 0; i--)
			if(root->avl_data * i + root->avl_sum[0] <= *s){
				*size += (i + root->avl_cnode[0]);
				*s -= (root->avl_data * i + root->avl_sum[0]);
				return;
			}
	}
	buygames(root->avl_link[0], s, size);
}

void buy(Owner *oset, Game *gset){
	int game;
	Long s;
	scanf("%d", &game);
	scanf("%lld", &s);

	int size = 0;
	Game *root = find(gset, game-1);
	buygames(root->belong->garage->avl_root, &s, &size);
	printf("%d %d\n", root->belong->id+1, size);
}

int main(void){
	int friends, events;
	Owner oset[MAXMEN];
	Game gset[MAXMEN];
	struct avl_table *avl[MAXMEN];
	scanf("%d%d", &friends, &events);

	int i;
	for(i = 0; i < friends; i++){
		avl[i] = avl_create(int_compare, NULL, NULL);
		oset[i].garage = avl[i];
		oset[i].id = i;
		gset[i].i_th_game = i;
		scanf("%d", &gset[i].price);
		avl_probe(avl[i], gset[i].price);
		gset[i].belong = &oset[i];
		gset[i].height = 1;
	}
	/*for(i = 0; i < friends; i++){
			preorder(avl[i]->avl_root);
			putchar('\n');
	}*/
	int cases;
	for(i = 0; i < events; i++){
		scanf("%d", &cases);
		//int j;
		if(cases == 1)
			borrow(oset, gset);
		else if(cases == 2){
			buy(oset, gset);
		}
		/*printf("%d=======================\n", i);
		for(j = 0; j < friends; j++){
			if(oset[j].garage == NULL){
				printf("no element in set%d\n", j);
				continue;
			}
			preorder(oset[j].garage->avl_root);
			putchar('\n');
		}
		printf("=======================\n");*/
		else
			printf("Invalid Command.\n");
	}
	return 0;
}
