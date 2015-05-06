#include "strange_rational.h"


strange_rational::strange_rational(void):num(0),denom(1)
	{
	}

strange_rational::strange_rational(int numerator):num(numerator),denom(1)
	{

	}

strange_rational::strange_rational(int numerator, int denumerator):num(numerator),denom(denumerator)
	{

	}

strange_rational::strange_rational(const strange_rational& sr):num(sr.numerator()),denom(sr.denominator())
	{

	}


strange_rational::~strange_rational(void)
	{
	}

int strange_rational::numerator() const
	{
	return num;
	}

int strange_rational::denominator() const
	{
	return denom;
	}

double strange_rational::value() const
	{
	return ((double) num)/denom;
	}

strange_rational& strange_rational::operator+=(const strange_rational sr)
	{
	if (num!=0 && sr.numerator()!=0)
	{
	num+= sr.numerator();
	denom+= sr.denominator();
	}
	else if(num == 0 && sr.numerator()==0)
		{
		num=0;
		denom=1;
		}
	else
		{
		num+= sr.numerator();
		denom+= sr.denominator()-1;
		}
	return *this;
	}



 strange_rational strange_rational::operator+(const strange_rational& sr) const
	{
	strange_rational result = strange_rational(*this);
	result+=sr;
	return result;
	}

 bool strange_rational::operator<(const strange_rational& sr) const
	 {
	 return value()<sr.value();
	 }

 bool strange_rational::operator==(const strange_rational& sr) const
	 {
	 int gcd1 = gcd(num, denom);
	 int gcd2 = gcd(sr.numerator(), sr.denominator());

	 return (num/gcd1 == sr.numerator()/gcd2) && (denom/gcd1 == sr.denominator()/gcd2);
	 }

 int  strange_rational::gcd(int a, int b) const
	 {
	 int c = a % b;
	 while(c != 0)
		 {
		 a = b;
		 b = c;
		 c = a % b;
		 }
	 return b;
	 }