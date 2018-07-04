#include <iostream>
#include <vector>
#include <cstring>
#include <stack>
#include <cstdio>
#include <cmath>
using namespace std;

struct opset{
	int pre;
	double num;
	int index;
	char c;
	char op[6];
};
typedef opset OpSet;

void vprint(vector<OpSet> line){
	vector<OpSet>::iterator i;
	printf("In vector: ");
	for(i = line.begin(); i != line.end(); i++){
		if((*i).pre == 0)
			printf("%f ", (*i).num);
		else
			printf("%s ", (*i).op);
	}
	putchar('\n');
}

void sprint(stack<OpSet> stmp){
	stack<OpSet> buffer;
	OpSet otmp;
	printf("In stack: ");
	while(!stmp.empty()){
		otmp = stmp.top();
		buffer.push(otmp);
		stmp.pop();
	}
	while(!buffer.empty()){
		otmp = buffer.top();
		if(otmp.pre == 0)
			printf("%f ", otmp.num);
		else if(otmp.pre > 0 && otmp.pre < 15)
			printf("%s ", otmp.op);
		stmp.push(otmp);
		buffer.pop();
	}
			putchar('\n');
}

void ansprint(vector<OpSet> line){
	vector<OpSet>::iterator i;
//	for(i = line.begin(); i != line.end(); i++)
//		printf("%d %d %d %s\n", (*i).pre, (*i).num, (*i).index, (*i).op);
	printf("Postfix Exp: ");
	for(i = line.begin(); i != line.end(); i++){
		if(i != line.begin())
			putchar(' ');
		if((*i).pre == 0)
			printf("%.6f", (*i).num);
		else
			printf("%s", (*i).op);
	}
	putchar('\n');
}

void cutspace(char *str){
	int i = 0, j = 0;
	char strtmp[1000005];
	while(str[i] != '\n'){
		if(!isspace(str[i])){
			strtmp[j] = str[i];
			j++;
		}
		i++;
	}
	strtmp[j] = '\n';
	strcpy(str, strtmp);
}

void fstore(char *str, int& i, vector<OpSet>& line){
	char spntest[] = "1234567890.";
	char *ptr = &str[i];
	int len = strspn(ptr, spntest);
	char buffer[100] = "";
	strncpy(buffer, ptr, len);

	OpSet vbuf;
	vbuf.num = atof(buffer);
	vbuf.pre = 0;
	line.push_back(vbuf);
	i += len;
}

void stackput(int j, OpSet *optest, vector<OpSet>& line, stack<OpSet>& stmp, int& i){
	if(stmp.empty())
		stmp.push(optest[j]);
	else{
		OpSet check = stmp.top();
		while(!stmp.empty()){
			check = stmp.top();
			if((optest[j].index == 10 || optest[j].index == 11) 
				 && (check.pre >= optest[j].pre))
				break;
			else if(check.pre > optest[j].pre)
				break;
			if(check.index == 16)
				break;
			line.push_back(check);
			stmp.pop();
		}
		stmp.push(optest[j]);
	}
	if(j >= 0 && j < 5)
		i += 3;
	else if(j >= 5 && j < 7)
		i += 4;
	else
		i++;
}

void process(vector<OpSet>& line,stack<OpSet>& stmp,OpSet *optest, char *str){
	int i = 0;
#ifdef PRINT
	printf("+++++Infix to Postfix++++++\n");
#endif
	while(str[i] != '\n'){
		if(isdigit(str[i]) || str[i] == '.'){
			fstore(str, i, line);
		}
		else if((str[i] == '-' && i == 0) || 
				(str[i] == '-' && (str[i-1] != ')' && !isdigit(str[i-1])))){
			stackput(10, optest, line, stmp, i);
		}
		else if((str[i] == '+' && i == 0) || 
				(str[i] == '+' && (str[i-1] != ')' && !isdigit(str[i-1])))){
			stackput(11, optest, line, stmp, i);
		}
		else if(str[i] == '('){
			stmp.push(optest[12]);
			i++;
		}
		else if(str[i] == ','){
			OpSet check = stmp.top();
			while(check.c != '(' && !stmp.empty()){
				line.push_back(check);
				stmp.pop();
				check = stmp.top();
			} 
			stmp.pop();
			stmp.push(optest[14]);
			i++;
		}
		else if(str[i] == ')'){
			OpSet check = stmp.top();
			while((check.c != '(' && check.c != ',') && !stmp.empty()){
				line.push_back(check);
				stmp.pop();
				check = stmp.top();
			} 
			stmp.pop();
			i++;
		}
		else if(str[i] == 's' && str[i+1] == 'q'){
			stackput(5, optest, line, stmp, i);
		}
		else{
			for(int j = 0; j < 10; j++){
				if(str[i] == optest[j].c){
					stackput(j, optest, line, stmp, i);
					break;
				}
			}
		}
#ifdef PRINT
		printf("---------------------------\n");
		vprint(line);
		sprint(stmp);
		printf("---------------------------\n");
#endif
	}
	while(!stmp.empty()){
		OpSet check = stmp.top();
		line.push_back(check);
		stmp.pop();
	}
#ifdef PRINT
	printf("+++++Transform completed+++\n");
#endif
}

void operation(int index, stack<double>& numset){
	double num1, num2, num;
	switch(index){
		case 0:
			num = numset.top();
			numset.pop();
			numset.push(sin(num));
		break;
		case 1:
			num = numset.top();
			numset.pop();
			numset.push(cos(num));
		break;
		case 2:
			num = numset.top();
			numset.pop();			
			numset.push(exp(num));
		break;
		case 3:
			num = numset.top();
			numset.pop();
			numset.push(log(num));
		break;
		case 4:
			num2 = numset.top();
			numset.pop();
			num1 = numset.top();
			numset.pop();
			numset.push(pow(num1, num2));
		break;
		case 5:
			num = numset.top();
			numset.pop();
			numset.push(sqrt(num));
		break;
		case 6:
			num = numset.top();
			numset.pop();
			numset.push(fabs(num));
		break;
		case 7:
			num2 = numset.top();
			numset.pop();
			num1 = numset.top();
			numset.pop();
			numset.push(num1*num2);
		break;
		case 8:
			num2 = numset.top();
			numset.pop();
			num1 = numset.top();
			numset.pop();
			numset.push(num1+num2);
		break;
		case 9:
			num2 = numset.top();
			numset.pop();
			num1 = numset.top();
			numset.pop();
			numset.push(num1-num2);
		break;
		case 10:
			num = numset.top();
			numset.pop();
			numset.push(-num);
		break;
		case 11:
		break;
		default:
		break;
	}
}

void calculator(vector<OpSet>& line){
	stack<double> numset;
	vector<OpSet>::iterator i;
	for(i = line.begin(); i < line.end(); i++){
		if((*i).pre == 0)
			numset.push((*i).num);
		else
			operation((*i).index, numset);
	}
	printf("RESULT: %.6f\n", numset.top());
}

int main(void){
	char str[1000005];
	while(fgets(str, 1000005, stdin) != NULL){
		vector<OpSet> line;
		stack<OpSet> stmp;
		OpSet optest[15] = {{1, 0, 0, 's', "sin"}, {1, 0, 1, 'c', "cos"}, {1, 0, 2, 'e', "exp"},
							{1, 0, 3, 'l', "log"}, {1, 0, 4, 'p', "pow"}, {1, 0, 5, 's', "sqrt"},   
							{1, 0, 6, 'f', "fabs"}, {3, 0, 7, '*', "*"}, {4, 0, 8, '+', "+"},
							{4, 0, 9, '-', "-"}, {2, 0, 10, '-', "-"}, {2, 0, 11, '+', "+"}, 
							{10, 0, 16, '(', "("}, {10, 0, 16, ')', ")"}, {10, 0, 17, ',', ","}};
		cutspace(str);
		process(line, stmp, optest, str);
		ansprint(line);
		calculator(line);
	}
	return 0;
}