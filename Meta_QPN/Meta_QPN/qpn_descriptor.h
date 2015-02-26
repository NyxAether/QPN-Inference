#pragma once

#include <vector>
#include "qpn_sign.h"
#include "qpn_edge.h"
#include "qpn_node.h"
#include "boost/graph/labeled_graph.hpp"
#include "boost/graph/adjacency_list.hpp"


template < typename NodeValue, typename Direction >
class qpn_descriptor
	{

	public:
		//Defining the graph type used for QPN instantiation
		typedef boost::labeled_graph<
			boost::adjacency_list<boost::vecS, boost::vecS,  boost::bidirectionalS, boost::property<boost::vertex_name_t, std::string>, qpn_edge*>, std::string> GraphType;

		//Defining vertices and edges for the graph
		typedef typename boost::graph_traits<GraphType>::vertex_descriptor Vertex;
		typedef typename boost::graph_traits<GraphType>::edge_descriptor Edge;

		//Defining vertex and edge iterators
		typedef typename boost::graph_traits<GraphType>::vertex_iterator VIterator;
		typedef typename boost::graph_traits<GraphType>::edge_iterator EIterator;
		typedef typename boost::graph_traits<GraphType>::in_edge_iterator InEIterator;
		typedef typename boost::graph_traits<GraphType>::out_edge_iterator OutEIterator;

	public:
		qpn_descriptor(void):qpn(GraphType()), nodeMap(std::map<std::string, qpn_node<NodeValue>*>()), edgeMap(std::map<Edge, qpn_edge*>()){};
		virtual ~qpn_descriptor(void){};

		virtual void addVertex(const std::string nName); 
		virtual void addVertex(qpn_node<NodeValue>* node); 
		virtual void addEdge(qpn_edge* new_edge,  std::vector<std::string>& args)= 0;
		virtual void observeNodeValue(const std::string nName, NodeValue value);
		virtual void observeNodeVariation(const std::string nName, const Sign& sign);


		virtual void propagate(const std::string nName, std::map<std::string, bool>& colorMap, bool fromChild, std::map<std::string, bool>& nextNodes);


		virtual typename qpn_node<NodeValue>* getNode(const std::string nName);
		virtual typename qpn_node<NodeValue>** getPNode(const std::string nName);
		virtual void setNode(const std::string nName, typename qpn_node<NodeValue>* node) ;

		virtual void getChildren(const std::string nName,  std::list< qpn_node<NodeValue>>& children);

		virtual std::list<std::string>* nodeNames();
		virtual bool exists(const std::string nName) const;

		virtual void  writeGraphVizNodes(std::ostream& os);
		virtual void  writeGraphVizEdges(std::ostream& os) =0;


	protected:
		GraphType qpn;
		std::map<Edge, qpn_edge*> edgeMap;
		std::map<std::string, qpn_node<NodeValue>*> nodeMap;
	};



template <typename NodeValue,  typename Direction>
void qpn_descriptor<NodeValue,Direction>::addVertex(const std::string nName)
	{
	Vertex v =boost::add_vertex(nName, qpn);
	get(boost::vertex_name, qpn)[v]=nName;
	nodeMap[nName] = new qpn_node<NodeValue>();
	nodeMap[nName]->name =nName;
	}

template <typename NodeValue,  typename Direction>
void qpn_descriptor<NodeValue,Direction>::addVertex(qpn_node<NodeValue>* node)
	{
	Vertex v =boost::add_vertex(node->name, qpn);
	get(boost::vertex_name, qpn)[v]=node->name;
	nodeMap[node->name] = node;
	}

template <typename NodeValue,  typename Direction>
void qpn_descriptor<NodeValue,Direction>::observeNodeValue(const std::string nName, NodeValue value)
	{
	nodeMap[nName]->setValue(value);
	}

template <typename NodeValue,  typename Direction>
void qpn_descriptor<NodeValue,Direction>::observeNodeVariation(const std::string nName, const Sign& sign)
	{
	nodeMap[nName]->sign = sign; //There is no more modification because it's the role of the meta_qpn to propagate the sign
	}

template <typename NodeValue,  typename Direction>
qpn_node<NodeValue>* qpn_descriptor<NodeValue, Direction>::getNode(const std::string nName)
	{
	return nodeMap[nName];
	}


template < typename NodeValue, typename Direction >
typename qpn_node<NodeValue>** qpn_descriptor<NodeValue, Direction>::getPNode(const std::string nName)
	{
		return &(nodeMap[nName]);
	}

template < typename NodeValue, typename Direction >
void qpn_descriptor<NodeValue, Direction>::setNode(const std::string nName, typename qpn_node<NodeValue>* node)
	{
	nodeMap[nName]=node;
	}



template < typename NodeValue, typename Direction >
void qpn_descriptor<NodeValue, Direction>::getChildren(const std::string nName,  std::list<  qpn_node<NodeValue>>& children)
	{
	OutEIterator out_it, out_end;
	for(boost::tie(out_it, out_end) = boost::out_edges(qpn.vertex(nName),qpn); out_it != out_end ; out_it++){
		children.push_back(*(nodeMap[boost::get(boost::vertex_name,qpn,boost::target(*out_it,qpn))]));
		}
	}

template <typename NodeValue,  typename Direction>
std::list<std::string>* qpn_descriptor<NodeValue, Direction>::nodeNames()
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
bool qpn_descriptor<NodeValue, Direction>::exists(const std::string nName) const
	{
	return qpn.vertex(nName) != boost::graph_traits<GraphType>::null_vertex();
	}


template < typename NodeValue,  typename Direction >
void qpn_descriptor<NodeValue, Direction>::propagate(const std::string nName, std::map<std::string, bool>& colorMap, bool fromChild, std::map<std::string, bool>& nextNodes)
	{
	Vertex vertex = qpn.vertex(nName);
	qpn_node<NodeValue>* node = nodeMap[nName];
	if(fromChild){
		InEIterator in_it, in_end;
		for(boost::tie(in_it, in_end) = boost::in_edges(vertex,qpn); in_it != in_end ; in_it++){
			qpn_edge& edge=*edgeMap[*in_it] ;
			Vertex source = boost::source(*in_it,qpn);
			qpn_node<NodeValue>* source_node = nodeMap[boost::get(boost::vertex_name,qpn,source)];
			Sign newSign = (node->sign * edge.getSign()) + source_node->sign;
			if(!source_node->valIsSet && !colorMap[source_node->name] && newSign != source_node->sign)
				{
				nodeMap[source_node->name]->sign = newSign;
				nextNodes[source_node->name] = true;//Define  where the sign come from;
				}
			}
		}
	OutEIterator out_it, out_end;
	for(boost::tie(out_it, out_end) = boost::out_edges(vertex,qpn); out_it != out_end ; out_it++){
		qpn_edge& edge=*edgeMap[*out_it] ;
		Vertex target = boost::target(*out_it,qpn);
		qpn_node<NodeValue>* target_node = nodeMap[boost::get(boost::vertex_name,qpn,target)];
		Sign newSign = (node->sign * edge.getSign()) + target_node->sign;
		if(!target_node->valIsSet && !colorMap[target_node->name] && newSign != target_node->sign)
			{
			nodeMap[target_node->name]->sign = newSign;
			nextNodes[target_node->name] = false;//Define  where the sign come from;
			}
		}
	}


template < typename NodeValue,  typename Direction >
void qpn_descriptor<NodeValue, Direction>::writeGraphVizNodes(std::ostream& os)
	{
	VIterator it, it_end;
	for(std::tie(it,it_end) = boost::vertices(qpn); it!=it_end; it++)
		{
		qpn_node<NodeValue>* node =nodeMap[boost::get(boost::vertex_name, qpn, *it)];
		os<<node->name<<(*node)<<";"<<endl;
		}
	}







template < typename NodeValue>
class qpn_descriptor <NodeValue, boost::undirectedS>
	{
	public:
		//Defining the graph type used for QPN instantiation
		typedef boost::labeled_graph<
			boost::adjacency_list<boost::vecS, boost::vecS,  boost::undirectedS, boost::property<boost::vertex_name_t, std::string>, qpn_edge*>, std::string> GraphType;

		//Defining vertices and edges for the graph
		typedef typename boost::graph_traits<GraphType>::vertex_descriptor Vertex;
		typedef typename boost::graph_traits<GraphType>::edge_descriptor Edge;

		//Defining vertex and edge iterators
		typedef typename boost::graph_traits<GraphType>::vertex_iterator VIterator;
		typedef typename boost::graph_traits<GraphType>::edge_iterator EIterator;
		typedef typename boost::graph_traits<GraphType>::in_edge_iterator InEIterator;
		typedef typename boost::graph_traits<GraphType>::out_edge_iterator OutEIterator;

	public:
		qpn_descriptor(void):qpn(GraphType()),nodeMap(std::map<std::string, qpn_node<NodeValue>*>()),edgeMap(std::map<Edge, qpn_edge*>()){};
		virtual ~qpn_descriptor(void){};

		virtual void addVertex(const std::string nName); 
		virtual void addVertex(qpn_node<NodeValue>* node); 
		virtual void addEdge(qpn_edge* new_edge,  std::vector<std::string>& args)= 0;
		virtual void observeNodeValue(const std::string nName, NodeValue value);
		virtual void observeNodeVariation(const std::string nName, const Sign& sign);


		virtual void propagate(const std::string nName, std::map<std::string, bool>& colorMap, bool fromChild, std::map<std::string, bool>& nextNodes);


		virtual typename qpn_node<NodeValue>* getNode(const std::string nName);
		virtual void setNode(const std::string nName, typename qpn_node<NodeValue>* node);
		virtual std::list<std::string>* nodeNames();
		virtual bool exists(const std::string nName) const;

		virtual void  writeGraphVizNodes(std::ostream& os);
		virtual void  writeGraphVizEdges(std::ostream& os)=0;

	protected:
		GraphType qpn;
		std::map<Edge, qpn_edge*> edgeMap;
		std::map<std::string, qpn_node<NodeValue>*> nodeMap;
	};

template <typename NodeValue>
void qpn_descriptor<NodeValue,boost::undirectedS>::addVertex(const std::string nName)
	{
	Vertex v =boost::add_vertex(nName, qpn);
	get(boost::vertex_name, qpn)[v]=nName;
	nodeMap[nName] = new qpn_node<NodeValue>();
	nodeMap[nName]->name =nName;
	}

template <typename NodeValue>
void qpn_descriptor<NodeValue,boost::undirectedS>::addVertex(qpn_node<NodeValue>* node)
	{
	Vertex v =boost::add_vertex(node->name, qpn);
	get(boost::vertex_name, qpn)[v]=node->name;
	nodeMap[node->name] = node;
	}

template <typename NodeValue>
void qpn_descriptor<NodeValue,boost::undirectedS>::observeNodeValue(const std::string nName, NodeValue value)
	{
	nodeMap[nName]->setValue(value);
	}

template <typename NodeValue>
void qpn_descriptor<NodeValue,boost::undirectedS>::observeNodeVariation(const std::string nName, const Sign& sign)
	{
	nodeMap[nName]->sign = sign; //There is no more modification because it's the role of the meta_qpn to propagate the sign
	}

template <typename NodeValue>
qpn_node<NodeValue>* qpn_descriptor<NodeValue, boost::undirectedS>::getNode(const std::string nName)
	{
	return nodeMap[nName];
	}

template < typename NodeValue>
void qpn_descriptor<NodeValue, boost::undirectedS>::setNode(const std::string nName, typename qpn_node<NodeValue>* node)
	{
	nodeMap[nName]=node;
	}

template <typename NodeValue>
std::list<std::string>* qpn_descriptor<NodeValue, boost::undirectedS>::nodeNames()
	{
	std::list<std::string>* nNames = new std::list<std::string>();
	VIterator it, it_end;
	for(boost::tie(it, it_end) = vertices(qpn); it!=it_end; it++)
		{
		nNames->push_back(boost::get(boost::vertex_name,qpn, *it));
		}
	return nNames;
	}

template <typename NodeValue>
bool qpn_descriptor<NodeValue, boost::undirectedS>::exists(const std::string nName) const
	{
	return qpn.vertex(nName) != boost::graph_traits<GraphType>::null_vertex();
	}




template < typename NodeValue>
void qpn_descriptor<NodeValue, boost::undirectedS>::writeGraphVizNodes(std::ostream& os)
	{
	VIterator it, it_end;
	for(std::tie(it,it_end) = boost::vertices(qpn); it!=it_end; it++)
		{
		qpn_node<NodeValue>* node =nodeMap[boost::get(boost::vertex_name, qpn, *it)];
		os<<node->name<<(*node)<<";"<<endl;
		}
	}



template < typename NodeValue>
void qpn_descriptor< NodeValue, boost::undirectedS>::propagate(const std::string nName, std::map<std::string, bool>& colorMap, bool fromChild, std::map<std::string, bool>& nextNodes)
	{
	Vertex vertex = qpn.vertex(nName);
	qpn_node<NodeValue>* node = nodeMap[nName];

	OutEIterator out_it, out_end;
	for(boost::tie(out_it, out_end) = boost::out_edges(vertex,qpn); out_it != out_end ; out_it++){
		qpn_edge& edge=*edgeMap[*out_it] ;
		Vertex target = boost::target(*out_it,qpn);
		qpn_node<NodeValue>* target_node = nodeMap[boost::get(boost::vertex_name,qpn,target)];
		Sign newSign = (node->sign * edge.getSign()) + target_node->sign;

		if(!target_node->valIsSet && !colorMap[target_node->name] && newSign != target_node->sign)
			{
			nodeMap[target_node->name]->sign = newSign;
			nextNodes[target_node->name] = true;//Define  where the sign come from;
			}
		}
	}



