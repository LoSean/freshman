#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>
#include <time.h>
#define CLK 0
#define IMP 1
#define ADID 2
#define ADER 3
#define POS 4
#define DEP 5
#define QUERY 6
#define KEY 7
#define TITLE 8
#define DSP 9

using namespace std;

struct dataset{
	int info[10];
	char url[20];
};
typedef struct dataset DataSet;

struct impset{
	int info[4];
	char url[20];
};
typedef struct impset ImpSet;

struct proset{
	int info[3];
};
typedef struct proset ProSet;

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

bool clkcmp(DataSet& a, DataSet& b){
	if(a.info[ADID] != b.info[ADID])
		return (a.info[ADID] < b.info[ADID]);
	return (a.info[QUERY] < b.info[QUERY]);
}

bool anscmp(pair<int, int> a, pair<int, int> b){
	if(a.first != b.first)
		return (a.first < b.first);
	return (a.second < b.second);
}

void clicked1(vector<DataSet> base[]){
	int usrid;
	scanf("%d", &usrid);

//	sort(base[usrid].begin(), base[usrid].end(), clkcmp);
	vector<DataSet>::iterator i;
	vector<pair<int, int> > ans;
	for(i = base[usrid].begin(); i != base[usrid].end(); i++){
		if((*i).info[CLK] > 0){
				ans.push_back(make_pair((*i).info[ADID], (*i).info[QUERY]));		
		}
	}
	sort(ans.begin(), ans.end(), anscmp);
	printf("push_back success\n");

	vector<pair<int, int> >::iterator ansmax;
	ansmax = unique(ans.begin(), ans.end());
	
	printf("unique success\n");
	printf("%d\n", (int)(ansmax-ans.begin()));

	vector<pair<int, int> >::iterator j;
	for(j = ans.begin(); j < ansmax; j++)
		printf("%d %d\n", (*j).first, (*j).second);
	printf("********************\n");
}

bool impcmp(DataSet& a, DataSet& b){
	return (a.info[ADID] < b.info[ADID]);
}

bool setcmp(ImpSet& a, ImpSet& b){
	if(a.info[0] != b.info[0])
		return (a.info[0] < b.info[0]);
	else if(a.info[1] != b.info[1])
		return (a.info[1] < b.info[1]);
	else if(a.info[2] != b.info[2])
		return (a.info[2] < b.info[2]);
	else if(a.info[3] != b.info[3])
		return (a.info[3] < b.info[3]);
	else{
		if(strlen(a.url) != strlen(b.url))
			return (strlen(a.url) < strlen(b.url));
		else
			return (strcmp(a.url, b.url));
	}
}

bool unicmp(ImpSet& a, ImpSet& b){
	return ((a.info[0] == b.info[0]) && (a.info[1] == b.info[1]) &&
		(a.info[2] == b.info[2]) && (a.info[3] == b.info[3]) &&
		!strcmp(a.url, b.url));
}

void impressed2(vector<DataSet> base[]){
	int usrid1, usrid2;
	scanf("%d%d", &usrid1, &usrid2);

	sort(base[usrid1].begin(), base[usrid1].end(), impcmp);
	sort(base[usrid2].begin(), base[usrid2].end(), impcmp);

	int adid;
	ImpSet data;
	vector<DataSet>::iterator i;
	vector<DataSet>::iterator j;
	i = base[usrid1].begin();
	j = base[usrid2].begin();
	while(i != base[usrid1].end() && j != base[usrid2].end()){
		if((*i).info[ADID] > (*j).info[ADID]){
			j++;
		}
		else if((*i).info[ADID] < (*j).info[ADID]){
			i++;
		}
		else{
			vector<ImpSet> set;
			printf("%d == %d\n", (*i).info[ADID], (*j).info[ADID]);
			adid = (*i).info[ADID];
			printf("%d\n", adid);
			assert(adid == (*j).info[ADID]);
			while((*i).info[ADID] == adid){
				data.info[0] = (*i).info[ADER];
				data.info[1] = (*i).info[KEY];
				data.info[2] = (*i).info[TITLE];
				data.info[3] = (*i).info[DSP];
				strcpy(data.url, (*i).url);
				set.push_back(data);
				i++;
			}
			while((*j).info[ADID] == adid){
				data.info[0] = (*j).info[ADER];
				data.info[1] = (*j).info[KEY];
				data.info[2] = (*j).info[TITLE];
				data.info[3] = (*j).info[DSP];
				strcpy(data.url, (*j).url);
				set.push_back(data);
				j++;
			}
			printf("set sorting...\n");
			sort(set.begin(), set.end(), setcmp);
			printf("set sorting success\n");

			vector<ImpSet>::iterator maxset;
			printf("processing unique\n");
			maxset = unique(set.begin(), set.end(), unicmp);
			printf("unique success\n");

			vector<ImpSet>::iterator uni;
			for(uni = set.begin(); uni != maxset; uni++){
				printf("\t%s ", (*uni).url);
				for(int k = 0; k < 4; k++)
					printf("%d ", (*uni).info[k]);
				putchar('\n');
			}
		}
	}
	printf("********************\n");
}

bool procmp(ProSet& a, ProSet& b){
	return (a.info[0] < b.info[0]);
}

void profit3(vector< vector<ProSet> >& pbase){
	int adid;
	double theta;
	scanf("%d%lf", &adid, &theta);

	printf("pbase sorting...\n");
	sort(pbase[adid].begin(), pbase[adid].end(), procmp);
	printf("pbase sorting success\n");

	int clksum = 0, impsum = 0;
	vector<ProSet>::iterator i;
	i = pbase[adid].begin();
	clksum += (*i).info[1];
	impsum += (*i).info[2];
	i++;
	if(i == pbase[adid].end())
		printf("%d\n", (*(i-1)).info[0]);
	while(i != pbase[adid].end()){
		printf("in while clksum = %d, impsum = %d\n", clksum, impsum);
		printf("*(i-1).info[0] = %d\n", (*(i-1)).info[0]);
		if((*(i-1)).info[0] == (*i).info[0]){
			clksum += (*i).info[1];
			impsum += (*i).info[2];
		}
		else{
			if((double)(clksum/impsum) >= theta)
				printf("%d\n", (*(i-1)).info[0]);
			clksum = impsum = 0;
			clksum += (*i).info[1];
			impsum += (*i).info[2];
		}
		i++;
	}
	if((double)(clksum/impsum) >= theta)
				printf("%d\n", (*(i-1)).info[0]);
	printf("********************\n");
}

int main(int argc, char *argv[]){
	clock_t t1, t2;
	t1 = clock();
	FILE *fp;
	fp = fopen(argv[1], "r");
	assert(fp != NULL);

	vector<DataSet> *base = new vector<DataSet> [25000000];
	vector< vector<ProSet> > pbase;
	pbase.reserve(25000000);
	DataSet eat;
	ProSet put;
	int a;
	int usrid;
	int count = 0;
	while(fscanf(fp, "%d%d%s%d%d%d%d%d%d%d%d%d", &eat.info[0], &eat.info[1], eat.url, 
								   			   &eat.info[2], &eat.info[3], &eat.info[4], 
								   			   &eat.info[5], &eat.info[6], &eat.info[7], 
								    		   &eat.info[8], &eat.info[9], &usrid) != EOF){
		base[usrid].push_back(eat);

		put.info[0] = usrid;
		put.info[1] = eat.info[CLK];
		put.info[2] = eat.info[IMP];
		pbase[eat.info[ADID]].push_back(put);
		if(count % 1000000 == 0)
			printf("count = %d\n", count);
		count++;
	}
	t2 = clock();
	printf("%d : %lf\n", (int)((t2-t1)/(double)CLOCKS_PER_SEC/60), (t2-t1)/(double)CLOCKS_PER_SEC);

	int process;
	char order[15];
	char operation[4][15] = {"get", "clicked", "impressed", "profit"};
	scanf("%s", order);
	while(strcmp(order, "quit")){ 
		process = -1;
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
		case 2:
			impressed2(base);
			break;
		case 3:
			profit3(pbase);
			break;
		default:
			break;
		}

		scanf("%s", order);
	}

	return 0;
}


