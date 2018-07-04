#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <time.h>
using namespace std;

struct dataset{
	int a[10];
	char s[20];
};
typedef struct dataset Data;

struct vec{
	int n;
	vector<Data> a;
	struct vec *next;
};
typedef struct vec Vec;

int main(void){
	clock_t t1, t2;
	t1 = clock();
/*	Data a;
	for(int i = 0; i < 10; i++)
		a.a[i] = i;
	strcpy(a.s, "asd");*/
//	int data[10000000];
//	int *data = new int[10000000];
//	vector <Data> a[1000000];	
//	map<int, map<int, pair<int, int> > >testmap;
	vector<Data> *b = new vector<Data> [1000000];
/*	vector<vector<Data> > test;
	test.reserve(400000000);
	vector<vector<Data> >::iterator i;
	i = test.begin();
	cout << (*i);
	test[123].push_back(a);
	cout << test[124][0].a[0];*/
/*	Vec *vec, *last = NULL;
	for(int i = 0; i < 100000000; i++){
		vec = new Vec;
		vec->next = last;
		vec->n = i;
		last = vec;
	}
*/
	t2 = clock();
	
	cout << (t2-t1)/(double)CLOCKS_PER_SEC << "\n";
	return 0;
}
