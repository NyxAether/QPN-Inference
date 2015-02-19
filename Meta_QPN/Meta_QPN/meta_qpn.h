#pragma once
#include "qpn_descriptor.h"

template < class NodeValue, typename EdgeType>
class meta_qpn
	{
	public:
		typedef typename qpn_descriptor<  NodeValue, EdgeType> qpn_type;
		//TODO using some smart pointers for the qpns can be the good way to do things
		meta_qpn(void):qpn_directed(std::list<qpn_type>&>), qpn_undirected(std::list<qpn_descriptor< GraphType, NodeValue, EdgeType>&>){};
		~meta_qpn(void){};

		void addQpn(qpn_descriptor<NodeValue,EdgeType >& qpn, bool isDirected)	{
			if (isDirected)
				{
				if (qpn_directed.empty())
					{
					if(!qpn_undirected.empty())
						{
						for(qpn_type& it_qpn: qpn_undirected){
							copyNode(from, to);
							}
						}
					}
				qpn_directed.push_back(qpn);
				
				} 
			else
				{
				qpn_undirected.push_back(qpn);
				}

			};
		void observeNodeValue(std::string nName, NodeValue value){};
		void observeNodeSign(std::string nName, Sign sign){};

	protected:
		void copyNode(qpn_descriptor& from, qpn_descriptor& to)
			{

			};

	private:
		std::list<qpn_type>& qpn_directed;
		std::list<qpn_type>& qpn_undirected;
	};

