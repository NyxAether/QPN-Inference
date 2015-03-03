#pragma once
#include "qpn_sign.h"


template <typename NodeValue>
struct qpn_node
	{
	public:
		qpn_node(void):value(NULL), sign(Sign::ZERO_SIGN), valIsSet(false)
			{
			};
		virtual ~qpn_node(void){};
		friend std::ostream& operator<<(std::ostream& os,const qpn_node<NodeValue>& v);
		virtual void setValue(NodeValue val);
		
		std::string name;
		bool valIsSet;
		Sign sign;
		NodeValue value;
	};

template <typename NodeValue>
void qpn_node<NodeValue>::setValue(NodeValue val)
	{
	value =  NodeValue(val);
	valIsSet=true;
	}

template <typename NodeValue>
std::ostream& operator<<(std::ostream& os, qpn_node<NodeValue>& node)
	{
	os<<"[label=\""<<node.name<<":";
	if(node.valIsSet)
		os<<node.value<<"\",style=filled, color=\"0.75 0.75 0.75\"";
	else
		os<<node.sign<<"\"";
	os<<"]";
	return os;
	}