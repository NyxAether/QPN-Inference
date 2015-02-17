#pragma once
#include "stdafx.h"
#include "boost\graph\adjacency_list.hpp"
#include "boost\graph\labeled_graph.hpp"

#include "qpn_node.h"
#include "qpn_edge.h"
#include "qpn_descriptor.h"

template <class NodeValue>
class qpn_influence :
	public qpn_descriptor<NodeValue>
	{
	//Defining the graph type used for QPN instantiation
	typedef boost::labeled_graph<
		boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, qpn_node<NodeValue>, qpn_edge>, std::string> QPN_INFLUENCE;
	//Defining vertices and edges for the graph
	typedef typename boost::graph_traits<QPN_INFLUENCE>::vertex_descriptor Vertex;
	typedef typename boost::graph_traits<QPN_INFLUENCE>::edge_descriptor Edge;

	public:
		qpn_influence(void);
		~qpn_influence(void);

		virtual void addVertex(const std::string nName);

		virtual void addEdge(qpn_edge& new_edge, const std::list<std::string>& args );

		virtual void observeNodeValue(const std::string nName, NodeValue value);

		virtual void observeNodeVariation(const std::string nName, Sign sign);

		virtual void getNode(const std::string vName);

		virtual bool exists(const std::string vName);


		QPN_INFLUENCE qpn;
	};

