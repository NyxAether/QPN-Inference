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
	qpn[nName].value = value;
	qpn[nName].sign =Sign::ZERO_SIGN; //sign is reseted but this behavior is not necessarily usefull
	}

template <class NodeValue>
void qpn_influence<NodeValue>::observeNodeVariation(const std::string nName, const Sign& sign)
	{
	qpn[nName].sign = sign; //There is no more modification because it's the role of the meta_qpn to propagate the sign
	}

template <class NodeValue>
Vertex qpn_influence<NodeValue>::getNode(const std::string vName)
	{
	throw std::logic_error("The method or operation is not implemented.");
	return NULL;
	}


template <class NodeValue>
std::pair<VIterator,VIterator> qpn_influence<NodeValue>::nodes()
	{
	typedef graph_traits<Graph>::vertex_iterator vertex_iter;
	std::pair<vertex_iter, vertex_iter> vp;
	for (vp = vertices(g); vp.first != vp.second; ++vp.first)
		std::cout << city_name[*vp.first] << " " << city_index2[*vp.first] << std::endl;
	std::cout << std::endl;
	return NULL;
	}


template <class NodeValue>
bool qpn_influence<NodeValue>::exists(const std::string nName)
	{
	return qpn.vertex(nName) != graph_traits<QPN_INFLUENCE>::null_vertrex();
	}
