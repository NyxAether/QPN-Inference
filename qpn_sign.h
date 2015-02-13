#pragma once
#include <iostream>

typedef struct Sign Sign;

struct Sign
	{

	static const Sign PLUS_SIGN;
	static const Sign MINUS_SIGN;
	static const Sign ZERO_SIGN;
	static const Sign QMARK_SIGN;
	char c;

	Sign(char c) 
		{
		this->c = c;
		}

	Sign(const Sign& s) 
		{
		c= s.c;
		}
	Sign(void){
		c='0';
		}
	~Sign(void)
		{
		}
	const Sign  operator+( const  Sign & s) const{
		if (c == s.c)
			return *this;
		else if(c == '?' || s.c == '?')
			return QMARK_SIGN;
		else if (c=='+' && s.c=='-' || c=='-' && s.c=='+')
			return QMARK_SIGN;
		else if (c=='0')
			return s;
		else 
			return *this;
		}
	const Sign operator*( const  Sign & s) const{
		if (c == '0' || s.c == '0')
			return ZERO_SIGN;
		else if(c == '?' || s.c == '?')
			return QMARK_SIGN;
		else if (c == s.c)
			return PLUS_SIGN;
		else 
			return MINUS_SIGN;

		}
	bool operator==( const  Sign & s)	{
		return (c == s.c);
		}
	bool operator!=( const  Sign & s)	{
		return (c != s.c);
		}
	friend std::ostream& operator<< (std::ostream& os, const Sign& s)	{
		os << s.c;
		return os;
		}


	};

