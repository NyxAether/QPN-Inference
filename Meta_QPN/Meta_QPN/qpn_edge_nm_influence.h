#pragma once
#include "qpn_edge.h"




template <typename NodeValue>
struct qpn_edge_nm_influence :
	public qpn_edge
	{
	typedef std::tuple<qpn_node<NodeValue>**, qpn_edge_additive_synergy*, std::map<NodeValue, Sign>> provoker_type;
		typedef std::list<provoker_type> provokers_type;
	public:


		qpn_edge_nm_influence(void):provokers(provokers_type()){};
		qpn_edge_nm_influence(provokers_type provokers):provokers(provokers){};
		~qpn_edge_nm_influence(void){};

		Sign getSign();

		std::ostream& writeGraphVizFormat(std::ostream& os) const;
	private:
		provokers_type provokers;

	};

template <typename NodeValue>
Sign qpn_edge_nm_influence<NodeValue>::getSign()
	{
	Sign toReturn = Sign::ZERO_SIGN;
	for(provokers_type::iterator provoker = provokers.begin(); begin!= provokers.cend(); provoker++)
		{
		qpn_node<NodeValue>* node_p = *(std::get<0>(*provoker));

		if (node_p->valIsSet)
			{
			qpn_edge_additive_synergy* edge_p = std::get<1>(*provoker);
			std::map<NodeValue, Sign> signs_p = std::get<2>(*provoker);
			toReturn = toReturn + (edge_p->getRealSign() * signs_p[node_p->value])
			}
		else
			return Sign::QMARK_SIGN
		}
	return toReturn;
	}


template <typename NodeValue>
std::ostream& qpn_edge_nm_influence<NodeValue>::writeGraphVizFormat(std::ostream& os) const
	{

	os<<"label=\"";
	for(provokers_type::iterator provoker = provokers.begin(); begin!= provokers.cend(); )
		{
		qpn_node<NodeValue>* node_p = *(std::get<0>(*provoker));
		std::map<NodeValue, Sign> signs_p = std::get<2>(*provoker);

		os<<"~"<<node_p->name<<":";
		for (std::map<NodeValue, Sign>::const_iterator sign_p = signs_p.cbegin(); sign_p!= signs_p.cend(); )
			{
			os<<"["<<sign_p->first<<", "<<sign_p->second<<"]";
			if(++sign_p != signs_p.cend())
				os<<",";
			}

		if(++provoker != provokers.cend())
			os<<"\n";
		}
	os<<"\"";
	return os;
	}

