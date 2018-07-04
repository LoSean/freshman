#include <iostream>
#include "md5.h"
using namespace std;
 
int main(int argc, char *argv[])
{
    cout << "md5 of '" << argv[1] << "': " << encode(argv[1]) << endl;
    string s;
    cin >> s;
    cout << encode(s) << "\n";
    return 0;
}
