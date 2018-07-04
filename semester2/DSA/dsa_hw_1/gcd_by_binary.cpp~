#include <iostream>

#include "biginteger_for_binary.h"

using namespace std;

BigInteger gcd_by_binary(const BigInteger& a, BigInteger& b){
  BigInteger n, m;
  BigInteger ans(1);
//  cout << "before (a < b) a = " << a << ", b = " << b << ", ans = " << ans << "\n";
  if (a < b){
    n = a; m = b;
  }
  else{
    n = b; m = a;
  }
//  cout << "before while m = " << m << ", n = " << n << ", ans = " << ans << "\n";
  while(!n.iszero() && !m.iszero()){
//    cout << "before if m = " << m << ", n = " << n << ", ans = " << ans << "\n";
    if (n.iseven()){
      if (m.iseven()){
        ans *= 2;
        n /= 2;
        m /= 2;
      }
      else{
        n /= 2;
      }
    }
    else if (m.iseven()){
      m /= 2;
    }
//    cout << "before temp m = " << m << ", n = " << n << ", ans = " << ans <<"\n";
    if (m < n){
//	    cout << "success" << "\n";
      BigInteger tmp;
      tmp = n; n = m; m = tmp;
    }
//    cout << "before minus m = " << m << ", n = " << n << ", ans = " << ans << "\n";
    m = m - n;
  }
  
  return (n * ans);
}

int main(){
  string sa, sb;
  cin >> sa >> sb;
  BigInteger a(sa), b(sb);
//  cout << "main() a = " << a << ", b = " << b << "\n";
  cout << gcd_by_binary(a, b) << endl;

  return 0;
}
