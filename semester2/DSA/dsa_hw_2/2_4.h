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
	unsigned long long url;
};
typedef struct dataset DataSet;

struct impset{
	int info[4];
	unsigned long long url;
};
typedef struct impset ImpSet;

struct proset{
	int info[3];
};
typedef struct proset ProSet;

void get0(vector<DataSet> base[]);
void clicked1(vector<DataSet> base[]);
void impressed2(vector<DataSet> base[]);
void profit3(vector< vector<ProSet> >& pbase);
void process(vector<DataSet> base[], vector< vector<ProSet> >& pbase);
