#include "2_4.h"

void get0(vector<DataSet> base[]){
//	clock_t t1, t2;
//	t1 = clock();
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
//	t2 = clock();
//	printf("get = %lf(s)\n", (t2-t1)/(double)CLOCKS_PER_SEC);
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
//	clock_t t1, t2;
//	t1 = clock();
	int usrid;
	scanf("%d", &usrid);

	vector<DataSet>::iterator i;
	vector<pair<int, int> > ans;
	for(i = base[usrid].begin(); i != base[usrid].end(); i++){
		if((*i).info[CLK] > 0){
				ans.push_back(make_pair((*i).info[ADID], (*i).info[QUERY]));		
		}
	}
	sort(ans.begin(), ans.end(), anscmp);

	vector<pair<int, int> >::iterator ansmax;
	ansmax = unique(ans.begin(), ans.end());
	
//	printf("%d\n", (int)(ansmax-ans.begin()));

	vector<pair<int, int> >::iterator j;
	for(j = ans.begin(); j < ansmax; j++)
		printf("%d %d\n", (*j).first, (*j).second);
	printf("********************\n");
//	t2 = clock();
//	printf("clicked = %lf(s)\n", (t2-t1)/(double)CLOCKS_PER_SEC);
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
	else
		return (a.url < b.url);
}

bool unicmp(ImpSet& a, ImpSet& b){
	return ((a.info[0] == b.info[0]) && (a.info[1] == b.info[1]) &&
		(a.info[2] == b.info[2]) && (a.info[3] == b.info[3]) &&
		(a.url == b.url));
}

void impressed2(vector<DataSet> base[]){
//	clock_t t1, t2;
//	t1 = clock();
	int usrid1, usrid2;
	scanf("%d%d", &usrid1, &usrid2);

	if(usrid1 != 0)
		sort(base[usrid1].begin(), base[usrid1].end(), impcmp);
	if(usrid2 != 0)
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
			adid = (*i).info[ADID];
			printf("%d\n", adid);
			assert(adid == (*j).info[ADID]);
			while((*i).info[ADID] == adid){
				data.info[0] = (*i).info[ADER];
				data.info[1] = (*i).info[KEY];
				data.info[2] = (*i).info[TITLE];
				data.info[3] = (*i).info[DSP];
				data.url = (*j).url;
				set.push_back(data);
				i++;
			}
			while((*j).info[ADID] == adid){
				data.info[0] = (*j).info[ADER];
				data.info[1] = (*j).info[KEY];
				data.info[2] = (*j).info[TITLE];
				data.info[3] = (*j).info[DSP];
				data.url = (*j).url;
				set.push_back(data);
				j++;
			}
			sort(set.begin(), set.end(), setcmp);

			vector<ImpSet>::iterator maxset;
			maxset = unique(set.begin(), set.end(), unicmp);

			vector<ImpSet>::iterator uni;
			for(uni = set.begin(); uni != maxset; uni++){
				printf("\t%llu ", (*uni).url);
				printf("%d %d %d %d\n", (*uni).info[0], (*uni).info[1], 
						(*uni).info[2], (*uni).info[3]);
			}
		}
	}
	printf("********************\n");
//	t2 = clock();
//	printf("impressed = %lf(s)\n", (t2-t1)/(double)CLOCKS_PER_SEC);
}

bool procmp(ProSet& a, ProSet& b){
	return (a.info[0] < b.info[0]);
}

void profit3(vector< vector<ProSet> >& pbase){
//	clock_t t1, t2;
//	t1 = clock();
	int adid;
	double theta;
	scanf("%d%lf", &adid, &theta);

	sort(pbase[adid].begin(), pbase[adid].end(), procmp);

	int clksum = 0, impsum = 0;
	vector<ProSet>::iterator i;
	i = pbase[adid].begin();
	clksum += (*i).info[1];
	impsum += (*i).info[2];
	i++;
	while(i != pbase[adid].end()){
		if((*(i-1)).info[0] == (*i).info[0]){
			clksum += (*i).info[1];
			impsum += (*i).info[2];
		}
		else{
			if(((double)clksum/(double)impsum) >= theta)
				printf("%d\n", (*(i-1)).info[0]);
			clksum = impsum = 0;
			clksum += (*i).info[1];
			impsum += (*i).info[2];
		}
		i++;
	}
	if(((double)clksum/(double)impsum) >= theta)
				printf("%d\n", (*(i-1)).info[0]);
	printf("********************\n");
//	t2 = clock();
//	printf("profit = %lf(s)\n", (t2-t1)/(double)CLOCKS_PER_SEC);
}

void process(vector<DataSet> base[], vector< vector<ProSet> >& pbase){
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
		printf("********************\n");	
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
}