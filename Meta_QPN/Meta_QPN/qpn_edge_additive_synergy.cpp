#pragma once

#include "qpn_edge_additive_synergy.h"




Sign qpn_edge_additive_synergy::getSign()
	{
	return Sign::ZERO_SIGN;
	}

Sign qpn_edge_additive_synergy::getRealSign()
	{
	return sign;
	}



const std::string qpn_edge_additive_synergy::getAffectedNode() const
	{
	return affected_node;
	}

std::ostream& qpn_edge_additive_synergy::writeGraphVizFormat(std::ostream& os) const
	{

	return os;
	}


