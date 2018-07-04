#include "history.h"

bool cmp(STI *a, STI *b){
	assert(a != NULL);
	assert(b != NULL);
	return (a->priority < b->priority);
}

void mymerge(vector<STI>& owner, vector<STI>& belong, vector<STI>& tmp, string& ID){
	vector<STI>::iterator i, j;
	i = owner.begin();
	j = belong.begin();
	while(i != owner.end() || j != belong.end()){
		if((*i).priority <= (*j).priority)
			tmp.push_back((*i));
		else{
			tmp.push_back((*j));
			if((*j).bro != NULL){
				strncpy((*j).bro->id, ID.c_str(), sizeof((*j).bro->id));
				(*j).bro->bro = &(*(tmp.end()-1));	
			}
		}
		i++;
		j++;
	}
	while(i != owner.end()){
		tmp.push_back((*i));
		i++;
	}
	while(j != belong.end()){
		tmp.push_back((*j));
		if((*j).bro != NULL){
			strncpy((*j).bro->id, ID.c_str(), sizeof((*j).bro->id));
			(*j).bro->bro = &(*(tmp.end()-1));	
		}
		j++;
	}
}
