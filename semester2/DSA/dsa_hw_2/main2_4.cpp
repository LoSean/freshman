#include "2_4.h"

int main(int argc, char *argv[]){
//	clock_t t1, t2;
//	t1 = clock();
	FILE *fp;
	fp = fopen(argv[1], "r");
	assert(fp != NULL);

	vector<DataSet> *base = new vector<DataSet> [25000000];
	vector< vector<ProSet> > pbase;
	pbase.reserve(25000000);
	DataSet eat;
	ProSet put;
	int usrid;
//	int count = 0;
	while(fscanf(fp, "%d%d%llu%d%d%d%d%d%d%d%d%d", &eat.info[0], &eat.info[1], &eat.url, 
			 			   &eat.info[2], &eat.info[3], &eat.info[4], 
			   			   &eat.info[5], &eat.info[6], &eat.info[7], 
				    		   &eat.info[8], &eat.info[9], &usrid) != EOF){
		base[usrid].push_back(eat);

		put.info[0] = usrid;
		put.info[1] = eat.info[CLK];
		put.info[2] = eat.info[IMP];
		pbase[eat.info[ADID]].push_back(put);
//		if(count % 1000000 == 0)
//			printf("count = %d\n", count);
//		count++;
	}
//	t2 = clock();
//	printf("%d : %d\n", 
//		(int)((t2-t1)/(double)CLOCKS_PER_SEC/60), ((int)((t2-t1)/(double)CLOCKS_PER_SEC))%60);

	process(base, pbase);

	return 0;
}


