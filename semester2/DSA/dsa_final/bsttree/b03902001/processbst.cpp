#include "processbst.h"
#include "score.h"
using namespace std;
 
typedef set<INDEX<THistory> > Set;
//typedef Customer<THistory> customer;
const string b = "Hello",c = "fuck";
const customer cus_temp(b,c);


class TL{
public:
	string id;
	int score;
	bool operator<(const TL &a)const{
		if(score != a.score)
			return score < a.score;
		else
			return id < a.id;
	}
	TL(string str, int n){
		id = str;
		score = n;
	}
};

const string strtable = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

void all_digit_change(int h, vector<int> &NC, set<string> &listset2, string &sample, int pos, const string origin){
	if(h > (int)NC.size()){
		listset2.insert(sample);
		return;
	}
	for(int i = 0; i < 62; i++){
		if(strtable[i] == origin[pos-NC[h-1]])
			continue;
		sample[pos-NC[h-1]] = strtable[i];
		all_digit_change(h+1, NC, listset2, sample, pos, origin);
	}
}

void pick_or_not(int n, int h, vector<int> NC, set<string> &listset2, string sample, int pos){
	if(n < h && n != 0){
		
		return;
	}else if(n == 0){
			//cout << "yeah!!!" << endl;
		all_digit_change(1, NC, listset2, sample, pos, sample);
		return;
	}
	pick_or_not(n, h+1, NC, listset2, sample, pos); // not pick
	NC.push_back(h);
	pick_or_not(n-h, h+1, NC, listset2, sample, pos); // pick
	//cout << "fuck yeah!!!" << endl;
}

void extend(int cnt, int n_var, set<string> &listset2, string ID, int pos){
	if(cnt == 0){
		vector<int> needChange; 
		pick_or_not(n_var, 1, needChange, listset2, ID, pos);
		return;
	}
	for(int i = 0; i < 62; i++){
		string ex_string = ID + strtable[i];
		extend(cnt - 1, n_var, listset2, ex_string, pos);
	}
}

void clear_exist_ID(set<string> &listset2,struct bst_table *bst){
	set<string>::iterator ti;
	int count = 0;
	for(ti = listset2.begin(); ti != listset2.end(); ti++){
		INDEX<THistory> tmp(*ti);
		if(bst_find(bst, &tmp) != NULL)
			//cout <<"clear "<< *ti << endl;
			listset2.erase(ti);
		else
			count ++;
		if(count >= 10)
			return;
	}
}
void violencescore1(set<string> &listset2,const string &ID){
	string tmp (ID,0,((ID.size())-1));
	if(ID.size() > 1)
		listset2.insert(tmp);
	tmp += '@';
	int n = tmp.size() - 1;
	for(int i = 0; i < 62; i ++){
		tmp[n] = strtable[i];
		listset2.insert(tmp);
	}
	tmp = ID; tmp += '@';
	n = tmp.size() - 1;
	for(int i = 0; i < 62; i ++){
		tmp[n] = strtable[i];
		listset2.insert(tmp);
	}
	listset2.erase(ID);

}

void listing10(bool exist, string &ID,struct bst_table *bst){
	int i;
	struct bst_traverser *si = (struct bst_traverser *)malloc(sizeof(struct bst_traverser));
	INDEX<THistory> *get;
	set<TL> listset;
	set<TL>::iterator ti;
	if(exist){
		bst_t_init(si, bst);
		bst_t_first(si, bst);
		while(bst_t_cur(si) != NULL){
			get = (INDEX<THistory> *)bst_t_cur(si);
			listset.insert(TL(get->id, score(ID, get->id)));
			bst_t_next(si);
		}
		for(i = 0, ti = listset.begin(); i < 10 && ti != listset.end(); ti++){
			if(ti->score != 0){
				if(i == 9 || i == (int)listset.size() - 1){
					cout << ti->id << endl;
					break;
				}
				else
					cout << ti->id <<","/*<< ti->score << endl*/;
				i++;
			}
		}
	}else{
		set<string> listset2;
		set<string>::iterator tt;
		vector<int> needChange;
		int num_in_set = listset2.size(), lv, n_len, n_var, cnt;
		violencescore1(listset2,ID);
		clear_exist_ID(listset2, bst);
		num_in_set = listset2.size();
		if(num_in_set >= 10){
			int i;
			for(i = 0, tt = listset2.begin(); i < 9; tt++){
				cout << *tt <<","/*<< ti->score << endl*/;
				i++;
				
			}
			cout << *tt <<endl;
				return;
		}
		cout << "2 "<<endl;
		for(lv = 2; num_in_set < 10; lv++){
			/* shorten length */
			for(n_len = 1, cnt = 1; n_len <= lv; cnt++, n_len+=cnt){
				n_var = lv - n_len;
				if((int)ID.size() > cnt){
					string cut_string(ID, 0, ID.size()-cnt);
					pick_or_not(n_var, 1, needChange, listset2, cut_string, cut_string.size());
				}else
					break;
			}
			/* same length */
				pick_or_not(lv, 1, needChange, listset2, ID, ID.size());
			/* extend length */
			for(n_len = 1, cnt = 1; n_len <= lv; cnt++, n_len+=cnt){
				n_var = lv - n_len;
				extend(cnt, n_var, listset2, ID, ID.size());
			}
			clear_exist_ID(listset2, bst);
			for(tt = listset2.begin(); tt != listset2.end(); tt++){
				listset.insert(TL(*tt, lv));
			}
			needChange.clear();
			num_in_set = listset.size();
			if(num_in_set >= 10){
				for(i = 0, ti = listset.begin(); i < 9; ti++){
					if(ti->id != ID){
						if(i == 9)
							cout << ti->id << endl;
						else
							cout << ti->id <<","/*<< ti->score << endl*/;
						i++;
					}
				}
				break;
			}
		}
	}
}

#define MAX 100
enum prcsmode {CHR, QMK, STAR};

void FIND(string user, string test, struct bst_table *bst){
	int mode = -1;
//	bool found = false;
	bool firstprint = true;
	struct bst_traverser *si = (struct bst_traverser *)malloc(sizeof(struct bst_traverser));
	INDEX<THistory> *get;


	if(test.find("*") == string::npos && test.find("?") == string::npos){
		bst_t_init(si, bst);
		bst_t_first(si, bst);
		while(bst_t_cur(si) != NULL){
			get = (INDEX<THistory> *)bst_t_cur(si);
			if(test == get->id){
				if(firstprint){
					cout << get->id;
					firstprint = false;
				}else
					cout<<',' << get->id;
//				found = true;
			}
			bst_t_next(si);
		}
		return;
	}
	vector<string> fragment;
	string current;
	//size_t bottom; // top, bottom not always exist
	bool top_exist = true, bottom_exist = true, all_qmk = false;// for non-star
	int D[MAX] = {0}, bottom_dis = 0; // for qmk
	// process the search string
	if(test[0] == '*')
		top_exist = false; 
	for(int i = 0; i <(int) test.size(); i++){ 
		if(test[i] == '*'){
			if(mode == -1){
				mode = STAR;
				continue;
			}
			mode = STAR;
			fragment.push_back(current);
			current.clear();
			D[fragment.size()] = 0;
		}else if(test[i] == '?'){
			if(mode == CHR){ 
				fragment.push_back(current);
				current.clear();
				D[fragment.size()] = 2;
				mode = QMK;
			}else if(mode == -1){ // head = ? condition
				D[0]++;
			}else {
				D[fragment.size()]++;
				mode = QMK;
			}
		}else {
			current += test[i];
			mode = CHR;
		}
	}
	if(mode == CHR){ // push the last fragment
		fragment.push_back(current);
		current.clear();
		bottom_dis = 0;
	}else if(mode == QMK){
		bottom_dis = D[fragment.size()]-1;
	}else if(mode == STAR)
		bottom_exist = false; 
	if(fragment.size() == 0 && mode == -1){
		//cout << "all qmk, " << D[0] << endl;
		all_qmk = true;
	}

	
	// go through our idset
	vector<string>::iterator fi;
	int count = 0;
	
	/*for(fi = fragment.begin(), count = 0; fi != fragment.end(); fi++, count++){
		cout << (*fi) << ", " << D[count] << ", " << endl;
	}*/
	
	if(all_qmk){
		bst_t_init(si, bst);
		bst_t_first(si, bst);
		while(bst_t_cur(si) != NULL){
			get = (INDEX<THistory> *)bst_t_cur(si);
			if((int)(get->id).size() == D[0]){
				if(firstprint){
					cout << get -> id;
					firstprint = false;
				}else
					cout <<','<< get -> id;
			}
			bst_t_next(si);
		}	
		return;
	}

	bst_t_init(si, bst);
	bst_t_first(si, bst);
	while(bst_t_cur(si) != NULL){
		get = (INDEX<THistory> *)bst_t_cur(si);
		size_t last = 0;
		bool can_print = true;
		bool top_accord = true; // assumed it will be ok
		bool bottom_accord = true; // assumed it will be ok
		bool mid_accord = true; // assumed it will be ok
		bool find = true; // assumed it will be ok
		for(fi = fragment.begin(), count = 0; fi != fragment.end(); fi++, count++){
			size_t start = 0, current;
			while(1){
				if((current = (get->id).find(*fi, start)) == string::npos){
					find = false;
					break;
				}
				if(fi == fragment.begin()){ // check top
					if(top_exist && (int)current < D[0]){
						start = current+1;
						continue;
					}else if(top_exist && (int)current > D[0]){
						top_accord = false;
						break;
					}
					if(fi == fragment.end() - 1 && bottom_exist){ // check bottom
						if(current+(*fi).size()+bottom_dis < (get->id).size()){
							start = current+1;
							continue;
						}else if(current+(*fi).size()+bottom_dis > (get->id).size())
							bottom_accord = false;
					}
					break;
				}
				if(D[count] <= 0){ // check fragment after *
					if(current <= last){
						start = current+1;
						continue;
					}
					if(fi == fragment.end() - 1 && bottom_exist){ // check bottom
						if(current+(*fi).size()+bottom_dis < (get->id).size()){
							start = current+1;
							continue;
						}else if(current+(*fi).size()+bottom_dis > (get->id).size())
							bottom_accord = false;
					}
					break;
				}else{ // check fragment after ?
					if((int)(current-last) < D[count]){
						start = current+1;
						continue;
					}else if((int)(current-last) > D[count]){
						mid_accord = false;
						break;
					}
					if(fi == fragment.end() - 1 && bottom_exist){ // check bottom
						if(current+(*fi).size()+bottom_dis < (get->id).size()){
							start = current+1;
							continue;
						}else if(current+(*fi).size()+bottom_dis > (get->id).size())
							bottom_accord = false;
					}
					break;
				}
			}
			last = current + (*fi).size() - 1;
			if(!find || !top_accord || !mid_accord || !bottom_accord){
				can_print = false;
				break;
			}
		}
		if(can_print && get->id != user){
			/* print out the according word */
			if(firstprint){
				cout << get -> id;
				firstprint = false;
			}else
				cout << ',' << get->id;
//			found = true;
		}
		bst_t_next(si);
	}	
}

void processLogin(struct bst_table *bst,customer** user_now){

	bool success = false;
	string ID, PW;
	cin >> ID >> PW;
	INDEX<THistory> new_index(ID);
	INDEX<THistory> *tmp = (INDEX<THistory> *)bst_find(bst, &new_index); 
	if(tmp == NULL)
		cout <<"ID "<< ID <<" not found"<< endl;
	else if(! tmp-> cu_ptr -> authenticated(PW))
		cout <<"wrong password"<< endl;
	else {
		success = true;
		cout <<"success"<< endl;
	}
	if(success)
		*user_now = (tmp -> cu_ptr);
}

void processCreate(struct bst_table *bst){

	string ID, PW;
	cin >> ID >> PW;
	
	INDEX<THistory> *new_index = (INDEX<THistory> *)new INDEX<THistory>(ID, PW);	
	//cout << (int)new_index->id.size() << endl;
	//cout << (int)new_index->id.capacity() << endl;
	//new_index->id = ID;
	//new_index->cu_ptr = new Customer<THistory>(ID,PW);
	void **position = bst_probe(bst, new_index);
	if(*position == new_index){
		cout <<"success"<< endl;
	}else{
		cout <<"ID "<< ID <<" exists, ";
		listing10(false, ID, bst);
		delete new_index;
	}
}

void processDelete(struct bst_table *bst){

	string ID, PW;
	cin >> ID >> PW;
	INDEX<THistory> new_index(ID, PW);
	INDEX<THistory> *tmp = (INDEX<THistory> *)bst_find(bst, &new_index);
	if(tmp == NULL)
		cout <<"ID "<< ID <<" not found"<< endl;
	else if(!tmp-> cu_ptr -> authenticated(PW))
		cout <<"wrong password"<< endl;
	else {
//		(*tmp).cu_ptr->deletehistory();
		delete (*tmp).cu_ptr;
		bst_delete(bst, &new_index);
		cout <<"success"<< endl;
	}
	return;
}
void processMerge(struct bst_table *bst){

	unsigned long long X = 0;
	string ID1, ID2, PW1, PW2;
	cin >> ID1 >> PW1 >> ID2 >> PW2;
	INDEX<THistory> new_index1(ID1, PW1);
	INDEX<THistory> new_index2(ID2, PW2);
	INDEX<THistory> *tmp1 = (INDEX<THistory> *)bst_find(bst, &new_index1);
	INDEX<THistory> *tmp2 = (INDEX<THistory> *)bst_find(bst, &new_index2);
	if(tmp1 == NULL)
		cout <<"ID "<< ID1 <<" not found"<< endl;
	else if(tmp2 == NULL)
		cout <<"ID "<< ID2 <<" not found"<< endl;
	else if(!tmp1-> cu_ptr -> authenticated(PW1))
		cout <<"wrong password1"<< endl;
	else if(!tmp2->cu_ptr -> authenticated(PW2))
		cout <<"wrong password2"<< endl;
	else {
		tmp1->cu_ptr->mergehistory(*(tmp2->cu_ptr));
		X = tmp1->cu_ptr->dollars();
		cout <<"success, "<< ID1 <<" has "<< X <<" dollars"<< endl;
		delete (*tmp2).cu_ptr;
		bst_delete(bst, &new_index2);
	}
}

void processDeposit(customer* user_now){

	unsigned long long num = 0, X = 0;
	cin >> num;
	user_now->Deposit(num);
	X = user_now->dollars();
	cout <<"success, "<< X <<" dollars in current account"<< endl;
}
void processWithdraw(customer* user_now){

	unsigned long long num = 0, X = user_now->dollars();
	cin >> num;
	if(num > X)
		cout << "fail, "<< X <<" dollars only in current account"<< endl;
	else{
		user_now->withdraw(num);
		X = user_now->dollars();
		cout << "success, "<< X <<" dollars left in current account"<< endl;
	}
}

void processTransfer(customer* user_now, int& TIME_CNT, struct bst_table *bst){
			
	unsigned long long num = 0, X = user_now->dollars();
	string ID;
	cin >>  ID >> num;
	INDEX<THistory> new_index(ID);
	INDEX<THistory> *tmp = (INDEX<THistory> *)bst_find(bst, &new_index);
	if(tmp == NULL){
		cout <<"ID "<< ID <<" not found, ";
		listing10(true, ID, bst);
	}else if(num > user_now->dollars()){
		cout <<"fail, "<< X <<" dollars only in current account"<< endl;
	}else{
		user_now->transfer(tmp->cu_ptr, num, TIME_CNT);
		X = user_now->dollars();
		cout << "success, "<< X <<" dollars left in current account"<< endl;
		TIME_CNT++;
	}
}
void processFind(customer* user_now, struct bst_table *bst){

	string wild_card_ID;
	cin >> wild_card_ID;
	//FIND(user_now->ID, wild_card_ID, bst);
	cout << endl;
}

void processSearch(customer* user_now){

	string ID;
	cin >> ID;
	user_now->search(ID);
}
