#include "qpn_edge_influence.h"


qpn_edge_influence::qpn_edge_influence(void):sign(Sign::ZERO_SIGN)
	{
	}

qpn_edge_influence::qpn_edge_influence(const Sign& sign):sign(sign)
	{
	}

qpn_edge_influence::~qpn_edge_influence(void)
	{
	}

Sign qpn_edge_influence::getSign(void)
	{
	return sign;
	}
