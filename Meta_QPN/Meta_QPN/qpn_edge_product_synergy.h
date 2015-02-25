#pragma once
#include "qpn_edge.h"
#include "qpn_product_synergy.h"
template <typename NodeValue>
struct qpn_edge_product_synergy :
	public qpn_edge
	{
	public:
		qpn_edge_product_synergy(void):signMap(std::map<NodeValue, Sign>()){};
		qpn_edge_product_synergy( std::map<NodeValue, Sign> signs):signMap(signs){};
		~qpn_edge_product_synergy(void){};

		Sign getSign();

		std::ostream& writeGraphVizFormat(std::ostream& os) const;
		qpn_node<NodeValue>** linkedNode;
		
		std::map<NodeValue, Sign> signMap;
	};

template <typename NodeValue>
std::ostream& qpn_edge_product_synergy<NodeValue>::writeGraphVizFormat(std::ostream& os) const
	{
	os<<"label=\""<<(*linkedNode)->name<<":";
	for (std::map<NodeValue, Sign>::const_iterator signs = signMap.cbegin(); signs!= signMap.cend(); )
	{
	os<<"["<<signs->first<<", "<<signs->second<<"]";
	if(++signs != signMap.cend())
		os<<",";
	}
	os<<"\",dir=none,style=dotted";
	return os;
	}

template <typename NodeValue>
Sign qpn_edge_product_synergy<NodeValue>::getSign()
	{
	return signMap[(*linkedNode)->value];
	}
