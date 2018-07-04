#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>
#include <time.h>
#define CLK 0
#define IMP 1
#define ADID 2
#define POS 4
#define DEP 5
#define QUERY 6

using namespace std;

struct dataset{
	int info[10];
	char url[20];
};
typedef struct dataset DataSet;

bool clkcmp(DataSet& a, DataSet& b){
	if(a.info[ADID] != b.info[ADID])
		return (a.info[ADID] < b.info[ADID]);
	else
		return (a.info[QUERY] < b.info[QUERY]);
}

void get0(vector<DataSet> base[]){
	int usrid, adid, query, pos, dep;
	scanf("%d%d%d%d%d", &usrid, &adid, &query, &pos, &dep);

	int clksum = 0, impsum = 0;
	vector<DataSet>::iterator i;
	for(i = base[usrid].begin(); i != base[usrid].end(); i++)
		if (adid == (*i).info[ADID] && query == (*i).info[QUERY] && 
		    pos == (*i).info[POS] && dep == (*i).info[DEP]){
			clksum += (*i).info[CLK];
			impsum += (*i).info[IMP];
		}	
	printf("%d %d\n", clksum, impsum);
	printf("********************\n");
}

void clicked1(vector<DataSet> base[]){
	int usrid;
	scanf("%d", &usrid);
	
	printf("usrid sorting...\n");
	sort(base[usrid].begin(), base[usrid].end(), clkcmp);
	printf("sorting success\n");
	vector<DataSet>::iterator i;
	for(i = base[usrid].begin(); i != base[usrid].end(); i++){
		if((*i).info[CLK] > 0)
			printf("%d %d\n", (*i).info[ADID], (*i).info[QUERY]);
	}
	printf("********************\n");	
}

int main(int argc, char *argv[]){
	clock_t t1, t2;
	t1 = clock();
	FILE *fp;
	fp = fopen(argv[1], "r");
	assert(fp != NULL);
	vector<DataSet> *base = new vector<DataSet> [30000000];
	DataSet eat;
	int a;
	int usrid;
	int count = 0;
	while(fscanf(fp, "%d%d%s%d%d%d%d%d%d%d%d%d", &eat.info[0], &eat.info[1], eat.url,
						     &eat.info[2], &eat.info[3], &eat.info[4], 
						     &eat.info[5], &eat.info[6], &eat.info[7], 
						     &eat.info[8], &eat.info[9], &usrid) != EOF){
		base[usrid].push_back(eat);
		count++;
		if(count%1000000 == 0)
			printf("count = %d\n", count);
		/*vector<DataSet>::iterator i;
		for(i = base[usrid].begin(); i != base[usrid].end(); i++){
			for(int j = 0; j < 10; j++)
				cout << (*i).info[j] << " ";
			cout << (*i).url;
			cout << "\n";  
		}
		cout << "*********************" << "\n";
		*/
	}
	t2 = clock();
	printf("runtime = %lf\n", (t2-t1)/(double)(CLOCKS_PER_SEC));

	int process = 0;
	char order[15];
	char operation[4][15] = {"get", "clicked", "impressed", "profit"};
	scanf("%s", order);
	while(strcmp(order, "quit")){ 
		for(int i = 0; i < 4; i++)
			if(!strcmp(order, operation[i])){
				process = i;
				break;
			}

		switch(process){
		case 0:
			get0(base);
			break;
		case 1:
			clicked1(base);
			break;
		}

		scanf("%s", order);
	}

	return 0;
}


