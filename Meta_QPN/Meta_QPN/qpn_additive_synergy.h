#pragma once

#include <string>
#include "boost\graph\adjacency_list.hpp"
#include "qpn_descriptor_undirected.h"
#include "qpn_edge_additive_synergy.h"

template <typename NodeValue>
class qpn_additive_synergy :
	public qpn_descriptor_undirected< NodeValue>
	{
	public:



		qpn_additive_synergy(void){};

		~qpn_additive_synergy(void){};

		virtual void addEdge(qpn_edge* new_edge,  std::vector<std::string>& args );
		virtual void  writeGraphVizEdges(std::ostream& os);

	};

template <typename NodeValue>
void qpn_additive_synergy<NodeValue>::addEdge(qpn_edge* new_edge, std::vector<std::string>& args)
	{
	if(args.size()!=2 )
		throw std::invalid_argument("wrong number of arguments. 3 expected");
	if(!exists(args[0]))
		addVertex(args[0]);
	if(!exists(args[1]))
		addVertex(args[1]);
	Edge& e =boost::add_edge_by_label(args[0], args[1], qpn).first;

		edgeMap[e] = new_edge;
	}

template <typename NodeValue>
void qpn_additive_synergy<NodeValue>::writeGraphVizEdges(std::ostream& os)
	{
	EIterator it, it_end;
	for (std::tie(it,it_end)=boost::edges(qpn); it!=it_end;it++)
		{
		qpn_edge_additive_synergy* edge = dynamic_cast<qpn_edge_additive_synergy *>(edgeMap[*it]);
		qpn_node<NodeValue>* source = nodeMap[boost::get(boost::vertex_name,qpn, boost::source(*it,qpn))];
		qpn_node<NodeValue>* target = nodeMap[boost::get(boost::vertex_name,qpn, boost::target(*it,qpn))];
		std::string dummy = source->name + target->name + edge->getAffectedNode();
		os<<dummy<<"[shape=diamond, width=0, label=\""<<edge->getRealSign()<<"\"];"<<endl;
		os<<source->name<<"->"<<dummy<<"[dir=none,color=\"firebrick\"];"<<endl;
		os<<target->name<<"->"<<dummy<<"[dir=none,color=\"firebrick\"];"<<endl;
		os<<dummy<<"->"<<edge->getAffectedNode()<<"[style=dashed];"<<endl;
		}
	}
