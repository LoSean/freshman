#include <stdio.h>

int min(int num1, int num2){
	if(num1 > num2)
		return num2;
	else
		return num1;
}

int max(int num1, int num2){
	if(num1 > num2)
		return num1;
	else
		return num2;
}

void euclid(int num1, int num2){
	int c, temp, count = 0;
	printf("Case (%d, %d): ", num1, num2);
	while((c = num1 % num2) != 0){
		temp = num2;
		num2 = c;
		num1 = temp;
		count++;
	}
	printf("GCD-By-Euclid = %d", num2);
	printf(", taking %d iterations\n", count);
}

void binary(int num1, int num2){
	int n, m, ans = 1, temp, count = 0;
	printf("Case (%d, %d): ", num1, num2);
	m = max(num1, num2);
	n = min(num1, num2);
	while(m != 0 && n != 0){
		if((n % 2) == 0){
			if((m % 2) == 0){
				m /= 2;
				n /= 2;
				ans *= 2;
			}else{
				n /= 2;	
			}	
		}else if((m % 2) == 0){
			m /= 2;
		}
		if(m < n){
			temp = m;
			m = n;
  			n = temp;
		}
		m -= n;
		count++;
	}
	printf("GCD-By-Binary = %d, taking %d iterations\n", n * ans, count);
}

int fast(int num1, int num2, int s, int *count){
	int i;
	for(i = s; i <= min(num1, num2); i++){
		*count += 1;
		if((num1 % i) == 0 && (num2 % i) == 0)
			return i * fast((num1 / i), (num2 / i), i, count);
	}	
	return 1;
}

int filter(int num1, int num2, int *count){
	int i;
	for(i = 2; i <= min(num1, num2); i++){
		*count += 1;
		if((num1 % i) == 0 && (num2 % i) == 0)
			return i * filter((num1 / i), (num2 / i), count);
	}
	return 1;
}

void reverse(int num1, int num2){
	int i = min(num1, num2), count = 0;
	printf("Case (%d, %d): ", num1, num2);
	while(i != 0){
		count++;
		if((num1 % i) == 0 && (num2 % i) == 0){
			printf("GCD-By-Reverse-Search = %d, taking %d iterations\n", i, count);
			return;
		}
		i--;
	}
}

int main(void){
	int num1, num2, count = 0;
	scanf("%d", &num1);
	while(num1 != 0){
		scanf("%d", &num2);
		reverse(num1, num2);
		printf("Case (%d, %d): ", num1, num2);
		printf("GCD-By-Filter = %d, taking %d iterations\n", filter(num1, num2, &count), count);
		count = 0;
		printf("Case (%d, %d): ", num1, num2);
		printf("GCD-By-Fast-Filter = %d, taking %d iterations\n", fast(num1, num2, 2, &count), count);
		binary(num1, num2);
		euclid(num1, num2);
	scanf("%d", &num1);
	}	
	return 0;
}
