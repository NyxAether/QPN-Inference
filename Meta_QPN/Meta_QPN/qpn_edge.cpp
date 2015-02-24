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

//qpn_edge& qpn_edge::operator=(qpn_edge& edge)
//	{
//		edge.assign(*this);
//		return edge;
//	}

//inline void qpn_edge::assign( qpn_edge& edge)
//	{
//	edge.name = name;
//	}


 std::ostream& operator<<(std::ostream& os, const qpn_edge& edge)
	{
	return edge.writeGraphVizFormat(os);

	}
