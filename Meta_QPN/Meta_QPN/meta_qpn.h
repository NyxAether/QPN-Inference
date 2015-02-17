#pragma once
#include "qpn_descriptor.h"

template <class NodeValue>
class meta_qpn
	{
	public:
		meta_qpn(void);
		~meta_qpn(void);

		void addQpn(qpn_descriptor<NodeValue>& qpn);
		void observeNodeValue(std::string nName, NodeValue value);
		void observeNodeSign(std::string nName, Sign sign);
	};

