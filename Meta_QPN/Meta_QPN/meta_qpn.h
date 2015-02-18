#pragma once
#include "qpn_descriptor.h"

template <class NodeValue, typename GraphType>
class meta_qpn
	{
	public:
		meta_qpn(void);
		~meta_qpn(void);

		void addQpn(qpn_descriptor<NodeValue, GraphType>& qpn, bool isDirected);
		void observeNodeValue(std::string nName, NodeValue value);
		void observeNodeSign(std::string nName, Sign sign);

	protected:
		void copyNode(qpn_descriptor& from, qpn_descriptor& to);

	private:
		std::list<qpn_descriptor<NodeValue, GraphType>&> qpn_directed;
		std::list<qpn_descriptor<NodeValue, GraphType>&> qpn_undirected;
	};

