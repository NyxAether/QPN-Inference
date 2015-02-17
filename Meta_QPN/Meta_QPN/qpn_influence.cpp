#include "qpn_influence.h"

template <class NodeValue>
qpn_influence<NodeValue>::qpn_influence(void):qpn(QPN_INFLUENCE())
	{
	}

template <class NodeValue>
qpn_influence<NodeValue>::~qpn_influence(void)
	{
	}

template <class NodeValue>
void qpn_influence<NodeValue>::addVertex(const std::string nName)
	{
	add_vertex(name, qpn_influence);
	qpn_influence[name].name =name;
	}

template <class NodeValue>
void qpn_influence<NodeValue>::addEdge(qpn_edge& new_edge, const std::list<std::string>& args)
	{
	if(args.size()<2)
		throw std::length_error;
	if(!exists(args[0]))
		addVertex(args[0]);
	if(!exists(args[1]))
		addVertex(args[1]);
	Edge e =add_edge_by_label(from, to, qpn_influence).first;
	qpn[e] = new_edge;
	}


template <class NodeValue>
void qpn_influence<NodeValue>::observeNodeValue(const std::string nName, NodeValue value)
	{
	throw std::logic_error("The method or operation is not implemented.");
	}

template <class NodeValue>
void qpn_influence<NodeValue>::observeNodeVariation(const std::string nName, Sign sign)
	{
	throw std::logic_error("The method or operation is not implemented.");
	}

template <class NodeValue>
void qpn_influence<NodeValue>::getNode(const std::string vName)
	{
	throw std::logic_error("The method or operation is not implemented.");
	}

template <class NodeValue>
bool qpn_influence<NodeValue>::exists(const std::string vName)
	{
	throw std::logic_error("The method or operation is not implemented.");
	}
