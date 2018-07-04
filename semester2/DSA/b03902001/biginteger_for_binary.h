#ifndef BIGINTEGER_FOR_BINARY

#define BIGINTEGER_FOR_BINARY

class BigInteger{
private:
  int *digits;
  int size;
  int realsize;
public:
  BigInteger();
  BigInteger(const int& num);
  BigInteger(const std::string& s); 
  BigInteger(const BigInteger& bignum);
  ~BigInteger();
  
  int howbig() const;
  void chgsize(const int num);
  bool operator<(const BigInteger& bignum) const;
  void dumpzero();
  const BigInteger operator-(const BigInteger& bignum) const;
  const BigInteger operator*(const BigInteger& bignum) const;
  BigInteger& operator*=(int num);
  BigInteger& operator/=(int num);
  BigInteger& operator=(const BigInteger& bignum);
  bool iseven();
  bool iszero();

  friend std::ostream& operator<<(std::ostream& out, const BigInteger& bignum);

};

#endif
