#pragma once
#include "qpn_edge.h"


qpn_edge::qpn_edge(void):name("qpn_edge")
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
		return os<<"test";
	}



 std::ostream& operator<<(std::ostream& os, const qpn_edge& edge)
	{
	return edge.writeGraphVizFormat(os);

	}
