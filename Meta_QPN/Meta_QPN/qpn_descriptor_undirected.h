#pragma once

#include <vector>
#include "qpn_sign.h"
#include "qpn_edge.h"
#include "qpn_node.h"
#include "boost/graph/labeled_graph.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "i_qpn_descriptor.h"

template < typename NodeValue>
class qpn_descriptor_undirected:
	public i_qpn_descriptor<NodeValue, boost::undirectedS>
	{
	public:
		qpn_descriptor_undirected(void):i_qpn_descriptor(){};
		virtual ~qpn_descriptor_undirected(void){};

		virtual void addEdge(qpn_edge* new_edge,  std::vector<std::string>& args)= 0;
		
		virtual void propagate(const std::string nName, std::map<std::string, bool>& colorMap, bool fromChild, std::map<std::string, bool>& nextNodes);

		virtual void  writeGraphVizEdges(std::ostream& os)=0;

	};

template < typename NodeValue>
void qpn_descriptor_undirected< NodeValue>::propagate(const std::string nName, std::map<std::string, bool>& colorMap, bool fromChild, std::map<std::string, bool>& nextNodes)
	{
	Vertex vertex = qpn.vertex(nName);
	qpn_node<NodeValue>* node = (*nodeMap)[nName];

	OutEIterator out_it, out_end;
	for(boost::tie(out_it, out_end) = boost::out_edges(vertex,qpn); out_it != out_end ; out_it++){
		qpn_edge& edge=*edgeMap[*out_it] ;
		Vertex target = boost::target(*out_it,qpn);
		qpn_node<NodeValue>* target_node = (*nodeMap)[boost::get(boost::vertex_name,qpn,target)];
		std::cout<<node->getSign() << edge.getSign()<< target_node->getSign()<<std::endl;
		Sign newSign = (node->getSign() * edge.getSign()) + target_node->getSign();

		if(!target_node->isValObserved() && !colorMap[target_node->getName()] && newSign != target_node->getSign())
			{
			(*nodeMap)[target_node->getName()]->setSign(newSign);
			nextNodes[target_node->getName()] = true;//Define  where the sign come from;
			}
		}
	}



