#include <iostream>
#include <cstring>
#include <cstdio>
#include "binomial_heap.h"
using namespace std;

void assign(BinomialHeap<MyPair> *harr){
	int cm, id, p;
	scanf("%d%d%d", &cm, &id, &p);
	MyPair input(id, p);
	harr[cm].insert(input);
	printf("There are %d tasks on computer %d.\n", harr[cm].getsize(), cm);
}

void execute(BinomialHeap<MyPair> *harr){
	int cm;
	scanf("%d", &cm);
	int lastp = harr[cm].getmaxp();
	if(lastp == -1){
		printf("No task on the computer.\n");
		return;
	}
	while(lastp == harr[cm].getmaxp()){
		MyPair ptmp = harr[cm].pop();
		printf("Computer %d executed task %d.\n", cm, ptmp.first);
		lastp = ptmp.second;
	}

}

void merge1(BinomialHeap<MyPair> *harr, const int w){
	int cm1, cm2;
	scanf("%d%d", &cm1, &cm2);
	if(harr[cm2].getsize() >= w){
		harr[cm1].merge(harr[cm2]);//computer2 has to be empty!!
		printf("The largest priority number is now %d on %d.\n", harr[cm1].getmaxp(), cm1);
	}
	else
		printf("Merging request failed.\n");
}

int main(void){
	int c, w;
	BinomialHeap<MyPair> *harr;
	cin >> c >> w;
	harr = new BinomialHeap<MyPair>[c+5];

	char task[10];
	while(scanf("%s", task) != EOF){
		if(!strcmp(task, "assign"))
			assign(harr);
		else if(!strcmp(task, "execute"))
			execute(harr);
		else if(!strcmp(task, "merge"))
			merge1(harr, w);
		else if(!strcmp(task, "quit"))
			break;
		else
			cout << "Invalid Command\n";
	}
	delete harr;
	return 0;
}