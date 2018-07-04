#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cassert>
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

void treepost(TreeNode *head, int direction){
	if(head->left == NULL && head->right == NULL){
		cout << "\t\t<leaf>\n";
		printf("decision = %d\n", head->decision);
	}
	else{
		if(direction == 0)
			cout << "\t\t<root>\n";
		else if(direction == 1)
			cout << "\t\t<right child>\n";
		else
			cout << "\t\t<left child>\n";
		printf("head->threshold = %f,head->feature = %d\n", head->threshold, head->feature);
		treepost(head->left, -1);
		treepost(head->right, 1);
	}
}

void pairprint(vector<pair<int, double> >& pairbuff){
	vector<pair<int, double> >::iterator i;
	cout << "======================\n";
	for(i = pairbuff.begin(); i != pairbuff.end(); i++)
		cout << (*i).first << "," << (*i).second << "\n";
	cout << "======================\n";
}

void getsample(ifstream& input, int& maxindex, vector<Learn>& data, TreeNode& head){
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

		delete[] cstr;
	}
}

bool isnoise(vector<Learn>& data, const int maxindex){
	vector<Learn>::iterator i;
	for(int j = 1; j < maxindex+1; j++)
		for(i = data.begin(); i != data.end()-1; i++)
			if((*i).feature[j] != (*(i+1)).feature[j])
				return false;
//	cout << "noise occurs!\n";
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
/*			cout << "(" << totalaccumulate << ")" << "-" <<
					"leftconfusion = " << leftconfusion << 
					",rightconfusion = " << rightconfusion << 
					",confusion = " << confusion << "\n\n";
*/			if(confusion < minconfusion){
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
//	cout << totalY << "," << totalN << "\n";
	double confusion = 1 - (totalY / (totalY + totalN)) * (totalY / (totalY + totalN))
						 - (totalN / (totalY + totalN)) * (totalN / (totalY + totalN));
//	cout << confusion << "\n";
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
//		printf("head->threshold = %f,head->feature = %d\n", head->threshold, head->feature);
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
		printf("return %d;\n", head->decision);
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

void creatfunction(TreeNode *head){
	printf("int tree_predict(double *attr){\n");
	makedecision(head, 1);
	printf("}\n");
}

int main(int argc, char *argv[]){
	vector<Learn> data;
	ifstream input;
	input.open(argv[1]);
	double epsilon = atof(argv[2]); 
	int maxindex = 0;
	double total[2];
	TreeNode head;


	getsample(input, maxindex, data, head);

	buildtree(&head, data, maxindex, epsilon);

//	treepost(&head, 0);

	creatfunction(&head);

	return 0;
}
