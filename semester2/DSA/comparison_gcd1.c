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

int euclid(int num1, int num2){
	int c, temp, count = 0;
#ifdef PRINT
	printf("Case (%d, %d): ", num1, num2);
#endif
	while((c = num1 % num2) != 0){
		temp = num2;
		num2 = c;
		num1 = temp;
		count++;
	}
#ifdef PRINT
	printf("GCD-By-Euclid = %d, taking %d iterations\n", num2, count);
#endif
	return count;
}

int binary(int num1, int num2){
	int n, m, ans = 1, temp, count = 0;
#ifdef PRINT
	printf("Case (%d, %d): ", num1, num2);
#endif
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
#ifdef PRINT
	printf("GCD-By-Binary = %d, taking %d iterations\n", n * ans, count);
#endif
	return count;
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

int reverse(int num1, int num2){
	int i = min(num1, num2), count = 0;
#ifdef PRINT
	printf("Case (%d, %d): ", num1, num2);
#endif
	while(i != 0){
		count++;
		if((num1 % i) == 0 && (num2 % i) == 0){
#ifdef PRINT
			printf("GCD-By-Reverse-Search = %d, taking %d iterations\n", i, count);
#endif
			return count;
		}
		i--;
	}
	return 0;
}

int main(void){
	int num1 = 11260, num2 = 52000, count = 0, iteration = 0;
	float reverse_sum = 0, filter_sum = 0, fast_sum = 0, binary_sum = 0, euclid_sum = 0;
	while(num2 != 54261){
#ifdef PRINT
		putchar('\n');
#endif
		reverse_sum += reverse(num1, num2);
		count = 0;
#ifdef PRINT
		printf("Case (%d, %d): ", num1, num2);
		printf("GCD-By-Filter = %d, taking %d iterations\n", filter(num1, num2, &count), count);
#else
		filter(num1, num2, &count);
#endif
		filter_sum += count;
		count = 0;
#ifdef PRINT 
		printf("Case (%d, %d): ", num1, num2);
		printf("GCD-By-Fast-Filter = %d, taking %d iterations\n", fast(num1, num2, 2, &count), count);
#else
		fast(num1, num2, 2, &count);
#endif
		fast_sum += count;
		binary_sum += binary(num1, num2);
		euclid_sum += euclid(num1, num2);
		num2++;
		iteration++;
	}	
	printf("reverse-gcd: %f\nfilter-gcd: %f\nfast-filter-gcd: %f\nbinary-gcd: %f\neuclid-gcd: %f\n",
 		reverse_sum/iteration, filter_sum/iteration, fast_sum/iteration,
		binary_sum/iteration, euclid_sum/iteration);
	return 0;
}
