#include <iostream>
#include <string>
#include "biginteger_for_binary.h"
using namespace std;

int intlen(int num){
	int count = 1;
	int c;
	while((c = (num / 10)) != 0){
		count++;
		num = c;
	}
	return count;
}

int power(int index){
        int p = 1;
        for(int i = 0; i < index; i++)
                p *= 10; 
        return p;
}

BigInteger::BigInteger(){
        size = 1000;
        digits = new int[size];
        for(int i = 0; i < size; i++)
                digits[i] = 0;
	realsize = howbig();
}

BigInteger::BigInteger(const int& num){
        size = 1000;
        digits = new int[size];
        for(int i = 0; i < intlen(num); i++)
                digits[i] = num % (power(i+1)) / (power(i)); // need to be modified
	realsize = howbig();
} 

BigInteger::BigInteger(const string& s){ 
        size = 1000;
        digits = new int[size];
	int ssize = s.size();
//	cout << "ssize = " << ssize << "\n";
	for(int i = 0; i < ssize; i++)   
                digits[i] = s[ssize - i - 1] - '0'; //need to be modified
	for(int i = ssize; i < size; i++)
		digits[i] = 0;
//	cout << "big s *this = " << *this << "\n"; 
	realsize = howbig();
}

BigInteger::BigInteger(const BigInteger& bignum){
        size = 1000;
        digits = new int[size];
        for(int i = 0; i < bignum.howbig(); i++)
                digits[i] = bignum.digits[i];
	for(int i = bignum.howbig(); i < size; i++)
		digits[i] = 0;
	realsize = howbig();
}

BigInteger::~BigInteger(){delete [] digits;}

int BigInteger::howbig() const{
	int count = size;
	while(count > 0 && digits[count-1] == 0)
		count--;
	return count;
}

void BigInteger::dumpzero(){
	BigInteger out;
	int count = size - 1;
	while(digits[count] == 0)
		count--;
//	cout << "malloc-82" << "\n";
	out.chgsize(count+1);
//	cout << "84out.size = " << out.size << "\n";
	for(int i = 0; i < out.size; i++)
		out.digits[i] = digits[i];
	*this = out;
}

void BigInteger::chgsize(const int num){
	delete [] digits;
	size = num;
	digits = new int[size];
	for(int i = 0; i < size; i++)
		digits[i] = 0;
}

bool BigInteger::operator<(const BigInteger& bignum) const{
        int thiscount = realsize - 1;
        int bigcount = bignum.realsize - 1;
	while(digits[thiscount] == 0)
        	thiscount--;
        while(bignum.digits[bigcount] == 0)
        	bigcount--;
//        cout << "105thiscount = " << thiscount << " ";
//        cout << "106bigcount = " << bigcount << "\n";
        if(thiscount < bigcount)
        	return 1;
        else if(thiscount > bigcount)
        	return 0;
        else{
        	for(int i = thiscount; i >= 0; i--){
               	if(digits[i] < bignum.digits[i])
               	        return 1;
               	else if(digits[i] > bignum.digits[i])
               	        return 0;
               	else
           	            continue;
      		}
        }
        return 0;
}

const BigInteger BigInteger::operator-(const BigInteger& bignum) const{
//	cout << "-this = " << *this << "\n";
	BigInteger out(*this);
//	for(int i = size-1; i >= bignum.realsize; i++)
//		out.digits[i] = 0;
//	cout << "-(1)out = " << out << "\n";
	for(int i = 0; i < bignum.realsize; i++)
                out.digits[i] = digits[i] - bignum.digits[i];
//	cout << "-(2)out = " << out << "\n";
        for(int i = 0; i < realsize; i++)
                if(out.digits[i] < 0){
                        out.digits[i] += 10;
                        out.digits[i+1] -= 1;
                }
//	cout << "-(3)out = " << out << "\n";
	out.realsize = out.howbig();
//	cout << "-(4)out = " << out << "\n";
//        out.dumpzero();
        return out;
}

const BigInteger BigInteger::operator*(const BigInteger& bignum) const{
        BigInteger out;
//        out.chgsize(size+bignum.size);
//        cout << "op* before add *this = " << *this << ", bignum = " << bignum << ", out = " << out << "\n";
	for(int i = 0; i < realsize; i++)
                for(int j = 0; j < bignum.realsize; j++)
                        out.digits[i+j] += digits[i] * bignum.digits[j];
//        cout << "op* before carry *this = " << *this << ", bignum = " << bignum << ", out = " << out << "\n";
	out.realsize = out.howbig();
	for(int i = 0; i < out.realsize; i++)
                if(out.digits[i] > 9){
                		out.digits[i+1] += out.digits[i] / 10;
                        out.digits[i] %= 10;
		}
//        cout << "op* before return *this = " << *this << ", bignum = " << bignum << ", out = " << out << "\n";
	out.realsize = out.howbig();
	return out;
}

BigInteger& BigInteger::operator*=(int num){
	BigInteger chgform(num);
        BigInteger out;
        out.chgsize(size+chgform.size);
//	cout << "before for loop num = " << num << ", out = " << out << ", *this = " << *this << "\n";
	for(int i = 0; i < realsize; i++)
                for(int j = 0; j < chgform.realsize; j++)
                        out.digits[i+j] += digits[i] * chgform.digits[j];
//        cout << "165out = " << out << " ";
        for(int i = 0; i < out.realsize; i++)
                if(out.digits[i] > 9){
                	    out.digits[i+1] += out.digits[i] / 10; 
                        out.digits[i] %= 10;
                }
//	out.realsize = out.howbig();
//        cout << "malloc-176" << "\n";
        delete [] digits;
        size = 1000;
//        cout << "173size = " << size << " "; 
        digits = new int[size];
	for(int i = 0; i < size; i++)
		digits[i] = 0;
        for(int i = 0; i < realsize; i++)
            digits[i] = out.digits[i];
	realsize = howbig();
//	cout << "*= real = " << realsize << "\n";
//	cout << "*= *this = " << *this << "\n";
	return *this;
}

BigInteger& BigInteger::operator/=(int num){
	BigInteger chgform(num);
        BigInteger out;
        out.chgsize(size);
//        cout << "/= outsize = " << out.size << "\n";
//	dumpzero();
        for(int i = realsize - 1; i >= 0; i--){
                out.digits[i] = digits[i] / chgform.digits[0];
                if(i != 0)
                        digits[i-1] += digits[i] % chgform.digits[0] * 10;
        }
//        out.dumpzero();
	out.realsize = out.howbig();
//	cout << "/= out.real = " << out.realsize << "\n";
//	cout << "/= out = " << out << "\n";
	delete [] digits;
        size = 1000;
//        cout << "196size = " << size << " "; 
        digits = new int[size];
	for(int i = 0; i < size; i++)
		digits[i] = 0;
        for(int i = 0; i < out.realsize; i++)
                digits[i] = out.digits[i];
//	cout << "/= *this = " << *this << "\n";
	realsize = howbig();
	return *this;
}


BigInteger& BigInteger::operator=(const BigInteger& bignum){
//        cout << "malloc-190" << "\n";
        if(digits != NULL)
        	delete [] digits;
        size = 1000;
        digits = new int[size];
	for(int i = 0; i < size; i++)
		digits[i] = 0;
	for(int i = 0; i < bignum.realsize; i++)
                digits[i] = bignum.digits[i];
	realsize = howbig();
        return *this;
}

bool BigInteger::iseven(){
	if(digits[0] % 2 == 0)
                return true;
        else
                return false;
}

bool BigInteger::iszero(){
	for(int i = 0; i < realsize; i++)
                if(digits[i] != 0)
                        return false;
        return true;
}

std::ostream& operator<<(std::ostream& out, const BigInteger& bignum){
        int count = bignum.size-1;
        while(bignum.digits[count] == 0)
	       	count--;
        for(int i = count; i >= 0; i--)
                out << bignum.digits[i];//need to be modified
        return out;
}
