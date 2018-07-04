#include <iostream>
#include <cstdio>
#include <stack>
#include <vector>
#include <cstring>
using namespace std;

struct opset{
	int pre;
	int num;
	int index;
	char c;
	char op[5];
};
typedef opset OpSet;

void vprint(vector<OpSet> line){
	vector<OpSet>::iterator i;
#ifdef PRINT
	printf("In vector: ");
#endif
	for(i = line.begin(); i != line.end(); i++){
		if(i != line.begin())
			putchar(' ');
		if((*i).pre == 0)
			printf("%d", (*i).num);
		else
			printf("%s", (*i).op);
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
			printf("%d ", otmp.num);
		else
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
			printf("%d", (*i).num);
		else
			printf("%s", (*i).op);
	}
	putchar('\n');
}

void operation(int index, stack<int>& numset){
	int num1, num2, num;
	switch(index){
		case 0:
			if(numset.top() == 0){
				numset.pop();
				numset.push(1);
			}
			else{
				numset.pop();
				numset.push(0);
			}
		break;
		case 1:
			num1 = numset.top();
			numset.pop();
			numset.push(~num1);
		break;
		case 2:
			num2 = numset.top();
			numset.pop();
			num1 = numset.top();
			numset.pop();
			numset.push(num1*num2);
		break;
		case 3:
			num2 = numset.top();
			numset.pop();
			num1 = numset.top();
			numset.pop();
			numset.push(num1/num2);
		break;
		case 4:
			num2 = numset.top();
			numset.pop();
			num1 = numset.top();
			numset.pop();
			num = num1 % num2;
			numset.push(num);
		break;
		case 5:
			num2 = numset.top();
			numset.pop();
			num1 = numset.top();
			numset.pop();
			numset.push(num1+num2);
		break;
		case 6:
			num2 = numset.top();
			numset.pop();
			num1 = numset.top();
			numset.pop();
			numset.push(num1-num2);
		break;
		case 7:
			num2 = numset.top();
			numset.pop();
			num1 = numset.top();
			numset.pop();
			numset.push(num1<<num2);
		break;
		case 8:
			num2 = numset.top();
			numset.pop();
			num1 = numset.top();
			numset.pop();
			numset.push(num1>>num2);
		break;
		case 9:
			num2 = numset.top();
			numset.pop();
			num1 = numset.top();
			numset.pop();
			numset.push(num1^num2);
		break;
		case 10:
			num2 = numset.top();
			numset.pop();
			num1 = numset.top();
			numset.pop();
			numset.push(num1&num2);
		break;
		case 11:
			num2 = numset.top();
			numset.pop();
			num1 = numset.top();
			numset.pop();
			numset.push(num1|num2);
		break;
		case 12:
			num1 = numset.top();
			numset.pop();
			numset.push(-num1);
		break;
		case 13:
			num2 = numset.top();
			numset.pop();
			num1 = numset.top();
			numset.pop();
			numset.push(((num1 != 0)&&(num2 != 0)));
		break;
		case 14:
		break;
		case 15:
			num1 = numset.top();
			numset.pop();
			num2 = numset.top();
			numset.pop();
			numset.push(((num1 != 0)||(num2 != 0)));
		break;
		default:
		break;
	}
}

void calculator(vector<OpSet>& line){
	stack<int> numset;
	vector<OpSet>::iterator i;
	for(i = line.begin(); i < line.end(); i++){
		if((*i).pre == 0)
			numset.push((*i).num);
		else
			operation((*i).index, numset);
	}
	printf("RESULT: %d\n", numset.top());
}

void stackput(int j, OpSet *optest, vector<OpSet>& line, stack<OpSet>& stmp, int& i){
	if(stmp.empty())
		stmp.push(optest[j]);
	else{
		OpSet check = stmp.top();
		while(!stmp.empty()){
			check = stmp.top();
			if((optest[j].index == 0 || optest[j].index == 1 || optest[j].index == 12 || optest[j].index == 14) 
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
	if(j == 7 || j == 8 || j == 13 || j == 15)
		i += 2;
	else
		i++;
}

void process(vector<OpSet>& line,stack<OpSet>& stmp,OpSet *optest, char *str){
	int i = 0;
#ifdef PRINT
	printf("+++++Infix to Postfix++++++\n");
#endif
	while(str[i] != '\n'){
		if(isdigit(str[i])){
			char spntest[] = "1234567890";
			char *ptr = &str[i];
			int len = strspn(ptr, spntest);
			char buffer[10] = "";
			strncpy(buffer, ptr, len);

			OpSet vbuf;
			vbuf.num = atoi(buffer);
			vbuf.pre = 0;
			line.push_back(vbuf);
			i += len;
		}
		else if((str[i] == '-' && i == 0) || 
				(str[i] == '-' && (str[i-1] != ')' && !isdigit(str[i-1])))){
			stackput(12, optest, line, stmp, i);
		}
		else if((str[i] == '+' && i == 0) || 
				(str[i] == '+' && (str[i-1] != ')' && !isdigit(str[i-1])))){
			stackput(14, optest, line, stmp, i);
		}
		else if(str[i] == '&' && str[i+1] == '&'){
			stackput(13, optest, line, stmp, i);
		}
		else if(str[i] == '|' && str[i+1] == '|'){
			stackput(15, optest, line, stmp, i);	
		}
		else{
			for(int j = 0; j < 12; j++){
				if(str[i] == optest[j].c){
					stackput(j, optest, line, stmp, i);
					break;
				}
			}
			if(str[i] == '('){
				stmp.push(optest[16]);
				i++;
			}
			else if(str[i] == ')'){
				OpSet check = stmp.top();
				while(check.c != '(' && !stmp.empty()){
					line.push_back(check);
					stmp.pop();
					check = stmp.top();
				} 
				stmp.pop();
				i++;
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

int main(void){
	char str[1000005];
	while(fgets(str, 1000005, stdin) != NULL){
		vector<OpSet> line;
		stack<OpSet> stmp;
		OpSet optest[18] = {{1, 0, 0, '!', "!"}, {1, 0, 1, '~', "~"}, {2, 0, 2, '*', "*"}, 
							{2, 0, 3, '/', "/"}, {2, 0, 4, '%', "\%"}, {3, 0, 5, '+', "+"}, 
							{3, 0, 6, '-', "-"}, {4, 0, 7, '<', "<<"}, {4, 0, 8, '>', ">>"}, 
							{7, 0, 9, '^', "^"}, {6, 0, 10, '&', "&"}, {8, 0, 11, '|', "|"}, 
							{1, 0, 12, '-', "-"}, {9, 0, 13, '&', "&&"}, {1, 0, 14, '+', "+"}, 
							{10, 0, 15, '|', "||"}, {11, 0, 16, '(', "("}, {11, 0, 16, ')', ")"}};
		//!, ~, 
		cutspace(str);
		process(line, stmp, optest, str);
		ansprint(line);
		calculator(line);
	}
	return 0;
}
