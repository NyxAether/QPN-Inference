#pragma once
#include "qpn_sign.h"


template <typename NodeValue>
struct qpn_node
	{
	public:
		qpn_node(void):value(NULL), sign(Sign::ZERO_SIGN)
			{
			};
		virtual ~qpn_node(void){};
		friend std::ostream& operator<<(std::ostream& os,const qpn_node<NodeValue>& v);

		std::string name;
		Sign sign;
		NodeValue value;
	};

template <typename NodeValue>
std::ostream& operator<<(std::ostream& os, qpn_node<NodeValue>& node)
	{
	os<<"[label=\""<<node.name<<":";
	if(node.value!=NULL)
		os<<node.value<<"\",style=filled, color=\"0.75 0.75 0.75\"";
	else
		os<<node.sign<<"\"";
	os<<"]";
	return os;
	}