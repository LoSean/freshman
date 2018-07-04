#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cassert>
#include <ctime>
#define Y 0
#define N 1
using namespace std;

using std::string;

struct learn{
	int label = 0;
	double feature[1025] = {0};
};
typedef learn Learn;

struct treenode{
	int feature = 0;
	double threshold = 0;
	int decision = 0;
	double total[2] = {0};
	struct treenode *left;
	struct treenode *right;
};
typedef treenode TreeNode;

void vprint(vector<Learn>& data, int maxindex){
	vector<Learn>::iterator i;
	cout << "........\n";
	for(i = data.begin(); i != data.end(); i++){
		cout << (*i).label << " ";
		for(int j = 0; j < maxindex+1; j++)
			cout << (*i).feature[j] << " ";
		putchar('\n');
	}
	cout << "........\n";
}

void getsample(ifstream& input, int& maxindex, vector<Learn>& data, TreeNode& head, int& count){
	string str;

	while(getline(input, str)){
		char *cstr, *tmp;
		Learn lbuff;

		cstr = new char[str.size()+1];
		strncpy(cstr, str.c_str(), str.size()+1);

		tmp = strtok(cstr, ": ");
		lbuff.label = atoi(tmp);
		tmp = strtok(NULL, ": ");
		if(lbuff.label > 0)
			head.total[Y]++;
		else
			head.total[N]++;

		while(tmp != NULL){
			int index = atoi(tmp);
			tmp = strtok(NULL, ": ");
			lbuff.feature[index] = atof(tmp);
			tmp = strtok(NULL, ": ");
			if(index > maxindex)
				maxindex = index;
		}
		data.push_back(lbuff);
		count++;
		delete[] cstr;
	}
}

bool isnoise(vector<Learn>& data, const int maxindex){
	vector<Learn>::iterator i;
	for(int j = 1; j < maxindex+1; j++)
		for(i = data.begin(); i != data.end()-1; i++)
			if((*i).feature[j] != (*(i+1)).feature[j])
				return false;
	return true;
}

void getconfusion(vector<pair<int, double> >& pairbuff, TreeNode *head, double& minconfusion, int feature){
	double accumulateY = 0, accumulateN = 0;
	double confusion = 0; 
	double total = head->total[Y] + head->total[N];
	vector<pair<int, double> >::iterator k;
	for(k = pairbuff.begin(); k != pairbuff.end()-1; k++){
		if((*k).first > 0)
			accumulateY++;
		else
			accumulateN++;
		if((*k).second == (*(k+1)).second)
			continue;
		else{
			double totalaccumulate = accumulateY + accumulateN;
			double leftconfusion = 1 - accumulateY / totalaccumulate * accumulateY / totalaccumulate
									 - accumulateN / totalaccumulate * accumulateN / totalaccumulate; 	
			double rightconfusion = 1 - (head->total[Y] - accumulateY) / (total - totalaccumulate) * (head->total[Y] - accumulateY) / (total - totalaccumulate)
									  - (head->total[N] - accumulateN) / (total - totalaccumulate) * (head->total[N] - accumulateN) / (total - totalaccumulate);
			
			confusion = totalaccumulate / total * leftconfusion + (total - totalaccumulate) / total * rightconfusion;
				if(confusion < minconfusion){
				minconfusion = confusion;
				head->threshold = ((*k).second + (*(k+1)).second) / 2;
				head->feature = feature;
			}
		}
	}
}

bool compare(pair<int, double>& a, pair<int, double>& b){
	return (a.second < b.second);
}

void findminconfusion(TreeNode *head, vector<Learn>& data, const int maxindex){
	vector<Learn>::iterator i;
	vector<pair<int, double> > pairbuff;
	double minconfusion = 1;
	for(int j = 1; j < maxindex+1; j++){
		for(i = data.begin(); i != data.end(); i++)
			pairbuff.push_back(make_pair((*i).label, (*i).feature[j]));

		sort(pairbuff.begin(), pairbuff.end(), compare);

		getconfusion(pairbuff, head, minconfusion, j);	
		pairbuff.clear();
	}
}

void dividedata(TreeNode *head, vector<Learn>& data, vector<Learn>& new1, vector<Learn>& new2){
	vector<Learn>::iterator i;
	for(i = data.begin(); i != data.end(); i++){
		if((*i).feature[head->feature] > head->threshold){
			new1.push_back((*i));
			if((*i).label > 0)
				head->right->total[Y]++;
			else
				head->right->total[N]++;
		}
		else {
			new2.push_back((*i));
			if((*i).label > 0)
				head->left->total[Y]++;
			else
				head->left->total[N]++;
		}
	}

}

void buildtree(TreeNode *head, vector<Learn> data, const int maxindex, const double epsilon){
	double totalY = head->total[Y];
	double totalN = head->total[N];
	assert(totalY+totalN != 0);
	double confusion = 1 - (totalY / (totalY + totalN)) * (totalY / (totalY + totalN))
						 - (totalN / (totalY + totalN)) * (totalN / (totalY + totalN));

	if(confusion <= epsilon || isnoise(data, maxindex)){
		if(totalY > totalN)
			head->decision = 1;
		else
			head->decision = -1;
		head->left = NULL;
		head->right = NULL;
		return;
	}
	else{
		head->left = new TreeNode;
		head->right = new TreeNode;
		vector<Learn> new1, new2;
		findminconfusion(head, data, maxindex);
		dividedata(head, data, new1, new2);
		data.clear();
		buildtree(head->right, new1, maxindex, epsilon);
		buildtree(head->left, new2, maxindex, epsilon);		
	}
}

void makedecision(TreeNode *head, int tab){
	for(int i = 0; i < tab; i++)
		printf("\t");
	if(head->right == NULL && head->left == NULL){
		if(head->decision > 0)
			printf("c++;\n");
		else
			printf("c--;\n");
	}
	else{
		printf("if(attr[%d] > %f){\n", head->feature, head->threshold);
		makedecision(head->right, tab+1);
		for(int i = 0; i < tab; i++)
			printf("\t");
		printf("}else{\n");
		makedecision(head->left, tab+1);
		for(int i = 0; i < tab; i++)
			printf("\t");
		printf("}\n");
	}
}

void creatfunction(TreeNode *head, int i){
	printf("tree%d_predict:\n", i);
	makedecision(head, 1);
}

void randomdata(vector<Learn>& data, vector<Learn>& rdata, int count){
	int *randset;
	
	randset = new int [count];
	for(int i = 0; i < count; i++)
		randset[i] = i;
	for(int i = count-1; i > 0; i--){
		int changeindex = rand() % i;
		int tmp = randset[changeindex];
		randset[changeindex] = randset[i];
		randset[i] = tmp; 
	}
	vector<Learn>::iterator j = data.begin();
	for(int i = 0; i < count / 3; i++)
		rdata.push_back(j[randset[i]]);
	//vprint(rdata, 2);
	delete [] randset;
}

void votingcompare(){
	printf("\tif (c > 0)\n");
	printf("\t\treturn 1;\n");
	printf("\telse\n");
	printf("\t\treturn -1;\n");
}

void buildforest(TreeNode *head, vector<Learn>& data, int maxindex, int epsilon, const int T, int count){
	vector<Learn> rdata;
	srand(time(NULL));
	printf("int forest_predict(double *attr){\n");
	printf("\tint c = 0;\n");
	for(int i = 0; i < T; i++){
		randomdata(data, rdata, count);
		buildtree(head, rdata, maxindex, epsilon);
		creatfunction(head, i+1);
		rdata.clear();
	}
	printf("voting:\n");
	votingcompare();
	printf("}\n");
}

int main(int argc, char *argv[]){
	vector<Learn> data;
	ifstream input;
	input.open(argv[1]);
	double epsilon = 0;
	int T = atoi(argv[2]); 
	int maxindex = 0;
	double total[2];
	int count = 0;
	TreeNode head;

	getsample(input, maxindex, data, head, count);

	buildforest(&head, data, maxindex, epsilon, T, count);
	
	return 0;
}