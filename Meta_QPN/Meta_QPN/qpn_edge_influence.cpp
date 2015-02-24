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

//qpn_edge_influence& qpn_edge_influence::operator=(qpn_edge& edge)
//	{
//
//	assign(edge);
//
//
//	return *this;
//	}
//
//void qpn_edge_influence::assign( qpn_edge& edge)
//	{
//	qpn_edge::assign(edge);
//	qpn_edge_influence* cast_edge = dynamic_cast< qpn_edge_influence*>(&edge);
//	if(cast_edge !=NULL){
//		cast_edge->sign =sign;
//		std::cout<<cast_edge->sign;
//		}
//	}


