#pragma once


#include "boost\graph\adjacency_list.hpp"
#include "boost\graph\labeled_graph.hpp"
#include "boost\property_map\property_map.hpp"

#include "qpn_node.h"
#include "qpn_edge.h"
#include "qpn_edge_influence.h"
#include "qpn_descriptor.h"


template <typename NodeValue>
class qpn_influence :
	public qpn_descriptor< NodeValue, boost::bidirectionalS>
	{
		public:



	qpn_influence(void);

	~qpn_influence(void);

	virtual void addEdge(qpn_edge& new_edge, const std::vector<std::string>& args );


	};


template <typename NodeValue>
qpn_influence<NodeValue>::qpn_influence(void) :qpn_descriptor()
	{

	}

template <typename NodeValue>
qpn_influence<NodeValue>::~qpn_influence(void)
	{

	}



template <typename NodeValue>
void qpn_influence<NodeValue>::addEdge(qpn_edge& new_edge, const std::vector<std::string>& args)
	{
	if(args.size()<2)
		throw std::invalid_argument("Not enough arguments. 3 expected");
	if(!exists(args[0]))
		addVertex(args[0]);
	if(!exists(args[1]))
		addVertex(args[1]);
	Edge e =add_edge_by_label(args[0], args[1], qpn).first;
	qpn[e] = new_edge;
	}










