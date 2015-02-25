#pragma once

#include "qpn_edge_influence.h"


qpn_edge_influence::qpn_edge_influence(void):qpn_edge(),sign(Sign::ZERO_SIGN)
	{
	name = "qpn_edge_influence";
	}

qpn_edge_influence::qpn_edge_influence(const Sign& sign):sign(sign)
	{
	name = "qpn_edge_influence";
	}

qpn_edge_influence::~qpn_edge_influence(void)
	{
	}

Sign qpn_edge_influence::getSign(void)
	{
	return sign;
	}



std::ostream& qpn_edge_influence::writeGraphVizFormat(std::ostream& os) const
	{
	os<<"label=\""<<sign<<"\"";
	return os;
	}




