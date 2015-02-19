#pragma once
#include "qpn_sign.h"


template <typename NodeValue>
struct qpn_node
	{
	public:
		qpn_node(void):value(NULL), sign(Sign::MINUS_SIGN)
			{
			};
		virtual ~qpn_node(void){};

		std::string name;
		Sign sign;
		NodeValue value;
	};
