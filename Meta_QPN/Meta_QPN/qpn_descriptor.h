#pragma once

#include <vector>
#include "qpn_sign.h"
#include "qpn_edge.h"
#include "qpn_node.h"
#include "boost/graph/labeled_graph.hpp"
#include "boost/graph/adjacency_list.hpp"


template < class NodeValue, class EdgeType>
class qpn_descriptor
	{
	typedef boost::labeled_graph<boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, qpn_node<NodeValue>, EdgeType>, std::string> GraphType;
	public:

		qpn_descriptor(void){};
		virtual ~qpn_descriptor(void){};

		virtual void addVertex(const std::string nName) = 0; 
		virtual void addEdge(EdgeType& new_edge, const std::vector<std::string>& args)= 0;
		virtual void observeNodeValue(const std::string nName, NodeValue value)= 0;
		virtual void observeNodeVariation(const std::string nName, const Sign& sign)= 0;
		//virtual typename boost::graph_traits<GraphType>::vertex_descriptor getNode(const std::string nName)= 0;
		virtual std::pair<typename boost::graph_traits<GraphType>::vertex_iterator,typename boost::graph_traits<GraphType>::vertex_iterator> nodes()=0;
		virtual bool exists(const std::string nName) const= 0;
	};

