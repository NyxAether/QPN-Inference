#pragma once
#include "qpn_edge.h"
template <typename NodeValue>
struct qpn_edge_product_synergy :
	public qpn_edge
	{
	public:
		qpn_edge_product_synergy(void):sign(Sign::ZERO_SIGN),isSimple(true){};
		qpn_edge_product_synergy(qpn_node<NodeValue>** linkedNode, std::map<NodeValue, Sign> signs):linkedNode(linkedNode),signMap(signs),isSimple(false){};
		qpn_edge_product_synergy(qpn_node<NodeValue>** linkedNode, Sign sign):linkedNode(linkedNode),sign(sign),isSimple(true){};
		~qpn_edge_product_synergy(void){};

		virtual Sign getSign();

		std::ostream& writeGraphVizFormat(std::ostream& os) const;

	private:
		qpn_node<NodeValue>** linkedNode;
		bool isSimple;
		std::map<NodeValue, Sign> signMap;
		Sign sign;
	};



template <typename NodeValue>
Sign qpn_edge_product_synergy<NodeValue>::getSign()
	{
	//std::cout<<((*linkedNode)->getName())<<(*linkedNode)->isObserved()<<sign<<std::endl;
	if(isSimple){
		if((*linkedNode)->isObserved())
			return sign;
		else
			return Sign::ZERO_SIGN;
		}
	else{
		if((*linkedNode)->isValObserved())
			return signMap[(*linkedNode)->getValue()];
		else
			return Sign::ZERO_SIGN;
		}
	}

template <typename NodeValue>
std::ostream& qpn_edge_product_synergy<NodeValue>::writeGraphVizFormat(std::ostream& os) const
	{
	os<<"label=\""<<(*linkedNode)->getName()<<":";
	if (isSimple)
		{
		os<<sign;
		}
	else
		{
		for (std::map<NodeValue, Sign>::const_iterator signs = signMap.cbegin(); signs!= signMap.cend(); )
			{
			os<<"["<<signs->first<<", "<<signs->second<<"]";
			if(++signs != signMap.cend())
				os<<",";
			}
		}
	os<<"\",dir=none,style=dotted";
	return os;
	}