#pragma once

#include <vector>
#include "qpn_sign.h"
#include "qpn_edge.h"
#include "qpn_node.h"
#include "boost/graph/labeled_graph.hpp"
#include "boost/graph/adjacency_list.hpp"

template < typename NodeValue, typename Direction >
class i_qpn_descriptor
	{

	public:
		//Defining the graph type used for QPN instantiation
		typedef boost::labeled_graph<
			boost::adjacency_list<boost::vecS, boost::vecS, Direction, boost::property<boost::vertex_name_t, std::string>, qpn_edge*>, std::string> GraphType;

		//Defining vertices and edges for the graph
		typedef typename boost::graph_traits<GraphType>::vertex_descriptor Vertex;
		typedef typename boost::graph_traits<GraphType>::edge_descriptor Edge;

		//Defining vertex and edge iterators
		typedef typename boost::graph_traits<GraphType>::vertex_iterator VIterator;
		typedef typename boost::graph_traits<GraphType>::edge_iterator EIterator;
		typedef typename boost::graph_traits<GraphType>::in_edge_iterator InEIterator;
		typedef typename boost::graph_traits<GraphType>::out_edge_iterator OutEIterator;

	public:
		i_qpn_descriptor(void):qpn(GraphType()), nodeMap(new std::map<std::string, qpn_node<NodeValue>*>()), edgeMap(std::map<Edge, qpn_edge*>()){};
		virtual ~i_qpn_descriptor(void){};

		virtual void addVertex(const std::string nName); 
		virtual void addVertex(qpn_node<NodeValue>* node); 
		virtual void addEdge(qpn_edge* new_edge,  std::vector<std::string>& args)= 0;
		virtual void observeNodeValue(const std::string nName, NodeValue value);
		virtual void observeNodeVariation(const std::string nName, const Sign& sign);


		virtual void propagate(const std::string nName, std::map<std::string, bool>& colorMap, bool fromChild, std::map<std::string, bool>& nextNodes)=0;


		virtual typename qpn_node<NodeValue>* getNode(const std::string nName);
		virtual typename qpn_node<NodeValue>** getPNode(const std::string nName);
		virtual void setNode(const std::string nName, typename qpn_node<NodeValue>* node) ;
		virtual void setNodeMap(std::map<std::string, qpn_node<NodeValue>*>* nodeMap);

		qpn_edge* getEdge(std::string fromN, std::string toN);

		virtual void getChildren(const std::string nName,  std::list< qpn_node<NodeValue>>& children);
		virtual void getParents(const std::string nName,  std::list< qpn_node<NodeValue>>& parents);

		virtual std::list<std::string>* nodeNames();
		virtual bool exists(const std::string nName) const;

		virtual void  writeGraphVizNodes(std::ostream& os);
		virtual void  writeGraphVizEdges(std::ostream& os) =0;


	protected:
		GraphType qpn;
		std::map<Edge, qpn_edge*> edgeMap;
		std::map<std::string, qpn_node<NodeValue>*>* nodeMap;
	};



template <typename NodeValue,  typename Direction>
void i_qpn_descriptor<NodeValue,Direction>::addVertex(const std::string nName)
	{
	Vertex v =boost::add_vertex(nName, qpn);
	get(boost::vertex_name, qpn)[v]=nName;
	(*nodeMap)[nName] = new qpn_node<NodeValue>();
	(*nodeMap)[nName]->setName(nName);
	}

template <typename NodeValue,  typename Direction>
void i_qpn_descriptor<NodeValue,Direction>::addVertex(qpn_node<NodeValue>* node)
	{
	Vertex v =boost::add_vertex(node->getName(), qpn);
	get(boost::vertex_name, qpn)[v]=node->getName();
	((*nodeMap))[node->getName()] = node;
	}

template <typename NodeValue,  typename Direction>
void i_qpn_descriptor<NodeValue,Direction>::observeNodeValue(const std::string nName, NodeValue value)
	{
	(*nodeMap)[nName]->setValue(value);
	}

template <typename NodeValue,  typename Direction>
void i_qpn_descriptor<NodeValue,Direction>::observeNodeVariation(const std::string nName, const Sign& sign)
	{
	(*nodeMap)[nName]->setSign(sign); //There is no more modification because it's the role of the meta_qpn to propagate the sign
	(*nodeMap)[nName]->setSignObserved(true);
	}

template <typename NodeValue,  typename Direction>
qpn_node<NodeValue>* i_qpn_descriptor<NodeValue, Direction>::getNode(const std::string nName)
	{
	return (*nodeMap)[nName];
	}


template < typename NodeValue, typename Direction >
typename qpn_node<NodeValue>** i_qpn_descriptor<NodeValue, Direction>::getPNode(const std::string nName)
	{
	return &((*nodeMap)[nName]);
	}

template < typename NodeValue, typename Direction >
void i_qpn_descriptor<NodeValue, Direction>::setNode(const std::string nName, typename qpn_node<NodeValue>* node)
	{
	(*nodeMap)[nName]=node;
	}


template < typename NodeValue, typename Direction >
void i_qpn_descriptor<NodeValue, Direction>::setNodeMap(std::map<std::string, qpn_node<NodeValue>*>* nodeMap)
	{
	delete this->nodeMap;
	this->nodeMap = nodeMap;
	}


template < typename NodeValue, typename Direction >
qpn_edge* i_qpn_descriptor<NodeValue, Direction>::getEdge(std::string fromN, std::string toN)
	{
	if (exists(fromN) && exists(toN))
		{
		OutEIterator out_it, out_end;
		for(boost::tie(out_it, out_end) = boost::out_edges(qpn.vertex(fromN),qpn); out_it != out_end ; out_it++){
			if (boost::get(boost::vertex_name,qpn,boost::target(*out_it,qpn)) == toN)
				return edgeMap[*out_it];
			}
		}
	return nullptr;
	}


template < typename NodeValue, typename Direction >
void i_qpn_descriptor<NodeValue, Direction>::getChildren(const std::string nName,  std::list<  qpn_node<NodeValue>>& children)
	{
	if (exists(nName))
		{

		OutEIterator out_it, out_end;
		for(boost::tie(out_it, out_end) = boost::out_edges(qpn.vertex(nName),qpn); out_it != out_end ; out_it++){
			children.push_back(*((*nodeMap)[boost::get(boost::vertex_name,qpn,boost::target(*out_it,qpn))]));
			}
		}
	}


template < typename NodeValue, typename Direction >
void i_qpn_descriptor<NodeValue, Direction>::getParents(const std::string nName, std::list< qpn_node<NodeValue>>& parents)
	{
	if (exists(nName))
		{
		InEIterator in_it, in_end;
		for(boost::tie(in_it, in_end) = boost::in_edges(qpn.vertex(nName),qpn); in_it != in_end ; in_it++){
			parents.push_back(*((*nodeMap)[boost::get(boost::vertex_name,qpn,boost::source(*in_it,qpn))]));
			}
		}
	}


template <typename NodeValue,  typename Direction>
std::list<std::string>* i_qpn_descriptor<NodeValue, Direction>::nodeNames()
	{
	std::list<std::string>* nNames = new std::list<std::string>();
	VIterator it, it_end;
	for(boost::tie(it, it_end) = vertices(qpn); it!=it_end; it++)
		{
		nNames->push_back(boost::get(boost::vertex_name,qpn, *it));
		}
	return nNames;
	}

template <typename NodeValue,  typename Direction>
bool i_qpn_descriptor<NodeValue, Direction>::exists(const std::string nName) const
	{
	return qpn.vertex(nName) != boost::graph_traits<GraphType>::null_vertex();
	}



template < typename NodeValue,  typename Direction >
void i_qpn_descriptor<NodeValue, Direction>::writeGraphVizNodes(std::ostream& os)
	{
	VIterator it, it_end;
	for(std::tie(it,it_end) = boost::vertices(qpn); it!=it_end; it++)
		{
		qpn_node<NodeValue>* node =(*nodeMap)[boost::get(boost::vertex_name, qpn, *it)];
		os<<node->getName()<<(*node)<<";"<<std::endl;
		}
	}