#pragma once

#include "boost\graph\adjacency_list.hpp"
#include "qpn_descriptor.h"
#include "qpn_edge_product_synergy.h"

template <typename NodeValue>
class qpn_product_synergy :
	public qpn_descriptor< NodeValue, boost::undirectedS>
	{
	public:



		qpn_product_synergy(void){};

		~qpn_product_synergy(void){};

		virtual void addEdge(qpn_edge* new_edge,  std::vector<std::string>& args );
		virtual void  writeGraphVizEdges(std::ostream& os);

	};

template <typename NodeValue>
void qpn_product_synergy<NodeValue>::addEdge(qpn_edge* new_edge, std::vector<std::string>& args)
	{
	if(args.size()!=3 )
		throw std::invalid_argument("wrong number of arguments. 4 expected");
	if(!exists(args[0]))
		addVertex(args[0]);
	if(!exists(args[1]))
		addVertex(args[1]);
	if(!exists(args[2]))
		addVertex(args[2]);
	Edge& e =boost::add_edge_by_label(args[0], args[1], qpn).first;
	qpn_edge_product_synergy<NodeValue> *cast_edge = dynamic_cast<qpn_edge_product_synergy<NodeValue> *>(new_edge);
	if (NULL != cast_edge)
		{
		cast_edge->linkedNode = &(nodeMap[args[2]]);
		edgeMap[e] = cast_edge;
		}
	}

template <typename NodeValue>
void qpn_product_synergy<NodeValue>::writeGraphVizEdges(std::ostream& os)
	{
	EIterator it, it_end;
	for (std::tie(it,it_end)=boost::edges(qpn); it!=it_end;it++)
		{
		qpn_edge& edge = *edgeMap[*it];
		qpn_node<NodeValue>* source = nodeMap[boost::get(boost::vertex_name,qpn, boost::source(*it,qpn))];
		qpn_node<NodeValue>* target = nodeMap[boost::get(boost::vertex_name,qpn, boost::target(*it,qpn))];
		os<<source->name<<"->"<<target->name<<"["<<edge<<"];"<<endl;
		}
	}
