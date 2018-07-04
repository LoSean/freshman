#include <iostream>
using namespace std;

struct MyInt{
		int a;
			int b;
};


int main(void){
		struct MyInt *ptr = new struct MyInt;
			ptr->a = 5;
				cout << ptr->a << endl;
					delete ptr;
						cout << ptr->a;
							return 0;	
}


