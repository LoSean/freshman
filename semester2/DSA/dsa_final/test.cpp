#include "history.h"
using namespace std;

void historyprint(THistory t1, string stmp){
	cout << "start of the container " << stmp << " ++++++++++++++++++++\n";
	vector<STI>::iterator j;
	for(j = t1.stilist.begin(); j != t1.stilist.end(); j++){
		cout << (*j).id << " "  << (*j).priority << " " 
		     << (*j).tofrom << " " << (*j).money << endl;
		if((*j).bro != NULL)
			cout << "brother : " << (*j).bro->id << endl;
	}
	cout << "end of the container " << stmp << " ++++++++++++++++++++\n";
	return;
}

int main(void){
	THistory t1("sean", 0, true, 1000);
	THistory t2("marry", 2, true, 20);
	t1.hpair(t2);
	t1.hadd("jean", 1, false, 3022);
	t2.hadd("daniel", 3, false, 3255);
	t1.hpair(t2);
	historyprint(t1, "t1");
	historyprint(t2, "t2");
	t1.hmerge(t2, "john");
		
	THistory t0;
	
	t1.hsearch("john");
//	t1.hdelete();
	historyprint(t1, "t1");
	return 0;
}
