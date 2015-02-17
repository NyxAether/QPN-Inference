#pragma once
#include "qpn_sign.h"


template <class NodeValue>
struct qpn_node
	{
	public:
		qpn_node(void);
		virtual ~qpn_node(void);

		std::string name;
		Sign sign;
		NodeValue value;
	};

