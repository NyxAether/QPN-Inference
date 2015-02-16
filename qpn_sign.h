#pragma once
#include <iostream>

typedef struct Sign Sign;

/**********************************************************************************************//**
\struct	Sign qpn_sign.h qpn_sign.h

\brief	Defines the signs on a QPN. 
		This sign can be :
		- PLUS_SIGN used to describe the augmentation in probability of a value or a positive dependence between two nodes.<br/>
		- MINUS_SIGN used to describe the reduction in probability of a value or a negative dependence between two nodes.<br/>
		- ZERO_SIGN used to describe that no variation of a value is the most probable. If set on an edge, this edge will is equivalent to an independence. So, such edge as no reason to be created because it's equivalent to no edge.<br/>
		- QMARK_SIGN used to describe ambiguous value or dependence. Can be understood as "We don' know how a value has changed or how two nodes interact".<br/>
\author	Romain RINCE
\date	16/02/2015
 **************************************************************************************************/

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

	/**********************************************************************************************//**
	\fn	const Sign operator+( const Sign & s) const
	
	\brief	Addition operator :
				|	+	|	-	|	0	|	?<br/>
			+	|	+	|	?	|	+	|	?<br/>
			-	|	?	|	-	|	-	|	?<br/>
			0	|	+	|	-	|	0	|	?<br/>
			?	|	?	|	?	|	?	|	?<br/>
	
	\author	Romain RINCE
	\date	16/02/2015
	
	\param	s	second part of the operand +
	
	\return	The result of the operation.
	 **************************************************************************************************/

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

	/**********************************************************************************************//**
	\fn	const Sign operator*( const Sign & s) const
	
	\brief	Multiplication operator:
				|	+	|	-	|	0	|	?<br/>
			+	|	+	|	-	|	0	|	?<br/>
			-	|	-	|	+	|	0	|	?<br/>
			0	|	0	|	0	|	0	|	0<br/>
			?	|	?	|	?	|	0	|	?<br/>
	
	\author	Romain RINCE
	\date	16/02/2015
	
	\param	s	The const Sign &amp; to process.
	
	\return	The result of the operation.
	 **************************************************************************************************/

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

