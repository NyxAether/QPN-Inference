#pragma once
#include "qpn_edge.h"


qpn_edge::qpn_edge(void)
	{
	}


qpn_edge::~qpn_edge(void)
	{
	}

Sign qpn_edge::getSign()
	{
	return Sign::ZERO_SIGN;
	}

std::ostream& qpn_edge::writeGraphVizFormat(std::ostream& os)const
	{
		return os;
	}

 std::ostream& operator<<(std::ostream& os, const qpn_edge& edge)
	{
	os<< edge.writeGraphVizFormat(os);
	}
