/*=============================================================================
 * File           : transformer.h
 * Author         : Romain RINCE
 * Creation       : Apr 08 2015
 
 *=============================================================================
 */

#pragma once
#include "qpn_sign.h"

		/*!
		*  \brief transformer class
		*
		*  \details This class header describe how a value of any type can be associate to a Sign
		*  \author  Romain RINCE
		*  \date      Apr 8, 2015
		*/
template<typename Val>
class transformer
	{
	public:

		transformer(void);

		~transformer(void);

		virtual inline Sign transform(Val value) const;

	};
template<typename Val>
transformer<Val>::transformer(void)
	{

	}


template<typename Val>
transformer<Val>::~transformer(void)
	{

	}



template<>
inline Sign transformer<bool>::transform(bool value) const
	{
	if(value)
		return Sign::PLUS_SIGN;
	else
		return Sign::MINUS_SIGN;
	}

template<>
inline Sign transformer<int>::transform(int value) const
	{
	if(value <= 0)
		return Sign::MINUS_SIGN;
	else
		return Sign::PLUS_SIGN;
	}

template<>
inline Sign transformer<double>::transform(double value) const
	{
	if(value <= 0.0)
		return Sign::MINUS_SIGN;
	else
		return Sign::PLUS_SIGN;
	}


template<typename Val>
inline Sign transformer<Val>::transform(Val value) const
	{
	return Sign::ZERO_SIGN;
	}
