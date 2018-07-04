#ifndef BIGINTEGER_FOR_EUCLID

#define BIGINTEGER_FOR_EUCLID

class BigInteger{
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
  void dumpzero();
  bool operator<(const BigInteger& bignum) const;
  const BigInteger operator%(const BigInteger& bignum) const;
  BigInteger& operator=(const BigInteger& bignum);
  bool iszero() const;

  friend std::ostream& operator<<(std::ostream& out, const BigInteger& bignum);

};


#endif
