#pragma once
#include "../../header/simple_qpn/qpn_edge.h"


qpn_edge::qpn_edge()
	{
	sign=Sign::Sign(Sign::ZERO_SIGN);
	}

qpn_edge::qpn_edge( const Sign& s)
	{
	sign = s;
	}


qpn_edge::~qpn_edge(void)
	{
	}

const Sign qpn_edge::get_sign()
	{
	return sign;
	}

void qpn_edge::set_sign(const Sign& s)
	{
	sign = s;
	}

std::ostream& qpn_edge::display(std::ostream& os)const
	{
	os<<"[label=\""<<sign<<"\"]";
	return os;
	}

std::ostream& operator<<(std::ostream& os, const qpn_edge& edge)
	{
	return edge.display(os);
	}
