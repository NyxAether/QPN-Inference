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

	virtual void addEdge(qpn_edge* new_edge,  std::vector<std::string>& args );
	virtual void  writeGraphVizEdges(std::ostream& os);

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
void qpn_influence<NodeValue>::addEdge(qpn_edge* new_edge,  std::vector<std::string>& args)
	{
	if(args.size()<2)
		throw std::invalid_argument("Not enough arguments. 3 expected");
	if(!exists(args[0]))
		addVertex(args[0]);
	if(!exists(args[1]))
		addVertex(args[1]);
	Edge& e =boost::add_edge_by_label(args[0], args[1], qpn).first;
	edgeMap[e] = new_edge;
	//qpn_edge_influence* casted_edge = dynamic_cast<qpn_edge_influence *>(&new_edge);
	//if (NULL != casted_edge)
	//{
	//qpn_edge_influence&  edge_tmp= *casted_edge;
	//	qpn[e]= *casted_edge;
	//		cout<<edge_tmp<<std::endl;
	//	qpn[e]= edge_tmp;
	//}


	//cout<<new_edge<<std::endl;
	//cout<<qpn[e]<<std::endl;
	
	}

template < typename NodeValue>
void qpn_influence<NodeValue>::writeGraphVizEdges(std::ostream& os)
	{
	EIterator it, it_end;
	for (std::tie(it,it_end)=boost::edges(qpn); it!=it_end;it++)
		{
		qpn_edge& edge = *edgeMap[*it];
		qpn_node<NodeValue> source = boost::get(boost::vertex_bundle,qpn, boost::source(*it,qpn));
		qpn_node<NodeValue> target = boost::get(boost::vertex_bundle,qpn, boost::target(*it,qpn));
		os<<source.name<<"->"<<target.name<<"["<<edge<<"];"<<endl;
		}
	}








