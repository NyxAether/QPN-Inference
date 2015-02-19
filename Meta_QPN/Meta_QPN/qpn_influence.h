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
	public qpn_descriptor< NodeValue, qpn_edge_influence>
	{
		public:
	//Defining the graph type used for QPN instantiation
			typedef boost::labeled_graph<
				boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, qpn_node<NodeValue>, qpn_edge_influence>, std::string> QPN_INFLUENCE;

	//Defining vertices and edges for the graph
	typedef typename boost::graph_traits<QPN_INFLUENCE>::vertex_descriptor Vertex;
	typedef typename boost::graph_traits<QPN_INFLUENCE>::edge_descriptor Edge;

	//Defining vertex and edge iterators
	typedef typename boost::graph_traits<QPN_INFLUENCE>::vertex_iterator VIterator;
	typedef typename boost::graph_traits<QPN_INFLUENCE>::edge_iterator EIterator;


	qpn_influence(void):qpn(QPN_INFLUENCE())	{
		};

	~qpn_influence(void)	{
		};

	virtual void addVertex(const std::string nName)	{
		boost::add_vertex(nName, qpn);
		qpn[nName].name =nName;
		};

	virtual void addEdge(qpn_edge_influence& new_edge, const std::vector<std::string>& args )	{
		if(args.size()<2)
			throw std::invalid_argument("Not enough arguments. 3 expected");
		if(!exists(args[0]))
			addVertex(args[0]);
		if(!exists(args[1]))
			addVertex(args[1]);
		Edge e =add_edge_by_label(args[0], args[1], qpn).first;
		qpn[e] = new_edge;
		};

	virtual void observeNodeValue(const std::string nName, NodeValue value)	{
		qpn[nName].value = value;
		qpn[nName].sign =Sign::ZERO_SIGN; //sign is reseted but this behavior is not necessarily usefull
		};

	virtual void observeNodeVariation(const std::string nName, const Sign& sign)	{
		qpn[nName].sign = sign; //There is no more modification because it's the role of the meta_qpn to propagate the sign
		};

	//virtual qpn_node& getNode(Vertex node)	{
	//	return qpn.vertex(nName);

	//	};

	virtual std::pair<VIterator,VIterator> nodes()	{
		return vertices(qpn);
		};

	virtual bool exists(const std::string nName) const{
		return qpn.vertex(nName) != boost::graph_traits<QPN_INFLUENCE>::null_vertex();
		};

	protected:

		QPN_INFLUENCE qpn;
	};

