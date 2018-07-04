#include <vector>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <assert.h>
using namespace std;

struct singletransferinfo{
        char id[200];
        int priority;
        bool tofrom;
        unsigned long long money;
        struct singletransferinfo *bro;	
};
typedef struct singletransferinfo STI;

bool cmp(STI *a, STI *b);

void mymerge(vector<STI>& owner, vector<STI>& belong, vector<STI>& tmp, string& ID);

class THistory{
public:
	vector<STI> stilist;
		
	THistory(){
		stilist.clear();
		stilist.reserve(10000);
	}
	THistory(string i, int p, bool t, unsigned long long m){
		STI stitmp; 
		strncpy(stitmp.id, i.c_str(), sizeof(stitmp.id));
		stitmp.priority = p;
		stitmp.tofrom = t;
		stitmp.money = m;
		stitmp.bro = NULL;
		stilist.push_back(stitmp);
		stilsit.reserve(10000);
	}	
	~THistory(){
		stilist.clear();
	}
	void hadd(string i, int p, bool t, int m){	
		STI stitmp; 
		strncpy(stitmp.id, i.c_str(), sizeof(stitmp.id));
		stitmp.priority = p;
		stitmp.tofrom = t;
		stitmp.money = m;
		stitmp.bro = NULL;
		stilist.push_back(stitmp);
	}
	void hpair(THistory& b){
		(*(stilist.end()-1)).bro = &(*(b.stilist.end()-1));
		(*(b.stilist.end()-1)).bro = &(*(stilist.end()-1));			
	}
	void hmerge(THistory& b, string ID){
		vector<STI>::iterator i;
		cout << "success before change ID.\n";
		vector<STI> vtmp;
		vtmp.reserve(stilist.size()+b.stilist.size()+1);
		cout << "success before merge.\n";
		mymerge(stilist, b.stilist, vtmp, ID);
		stilist.clear();
		stilist.reserve(vtmp.size()+1);
		cout << "success before copy.\n";
		for(i = vtmp.begin(); i != vtmp.end(); i++){
			STI tmp = (*i);
			stilist.push_back(tmp);
		}
	}
	void hsearch(string ID){
		vector<STI>::iterator i;
		int flag = 0;
		for(i = stilist.begin(); i != stilist.end(); i++)
			if(!strcmp(ID.c_str(), (*i).id)){
				if((*i).tofrom)		
					printf("To ");
				else
					printf("From ");
				printf("%s %llu\n", (*i).id, (*i).money);
				flag = 1;
			}
		if(!flag)
			printf("no record\n");
	}
/*	void hdelete(){
		vector<STI>::iterator i;
		for(i = stilist.begin(); i != stilist.end(); i++){
			delete (*i);
			(*i) = NULL;
		}	
	}*/
};           
