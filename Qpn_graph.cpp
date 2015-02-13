#include "qpn_graph.h"
#include "boost/graph/graphviz.hpp"
#include "QpnEdgeWriter.h"
#include "boost/property_map/property_map.hpp"
#include <boost/graph/depth_first_search.hpp>
#include "QpnVertexWriter.h"
#include "observed_descendant_dfs_visitor.h"




using namespace boost;
using namespace std;


Qpn_graph::Qpn_graph(void)
	{
	qpn_influence = QPN_INFLUENCE();
	qpn_synergy = QPN_SYNERGY();
	}


Qpn_graph::~Qpn_graph(void)
	{ 
	}

void Qpn_graph::addVertex(string name)
	{
	Vertex v = add_vertex(name, qpn_influence);
	qpn_influence[name].name =name;
	}

void Qpn_graph::addInfluence(string from, string to, const Sign& sign)
	{
	if(!existV(from, qpn_influence))
		addVertex(from);
	if(!existV(to, qpn_influence))
		addVertex(to);
	Influence e = add_edge_by_label(from, to, qpn_influence).first;
	qpn_influence[e] =qpn_edge(sign);
	//qpn_influence[e].sign =sign;

	}


void Qpn_graph::addIntercausalLink(std::string v1, std::string v2, std::string linked_v, std::map<int, Sign>& signMap)
	{
	if(!existV(v1, qpn_synergy)){
		if(!existV(v1, qpn_influence))
			addVertex(v1);
		add_vertex(v1,qpn_synergy);
		qpn_synergy[v1]=qpn_influence[v1];
		}
	if(!existV(v2, qpn_synergy)){
		if(!existV(v2, qpn_influence))
			addVertex(v2);
		add_vertex(v2,qpn_synergy);
		qpn_synergy[v2]=qpn_influence[v2];
		}
	Synergy e = add_edge_by_label(v1, v2, qpn_synergy).first;
	qpn_synergy[e] = intercausal_link(&qpn_influence[linked_v],signMap);
	//qpn_edge& inter1 =intercausal_link(&qpn_influence[linked_v],signMap);
	//qpn_edge& inter2 =intercausal_link(&qpn_influence[linked_v],signMap);
	//qpn_influence[e1] = intercausal_link(qpn_influence[linked_v],signmap);
	//qpn_influence[e2] = intercausal_link(qpn_influence[linked_v],signmap);
	}


void Qpn_graph::writeGraphViz(ostream& out)
	{
	QpnEdgeWriter<QPN_INFLUENCE> ew1(qpn_influence);
	QpnVertexWriter<QPN_INFLUENCE> vw1(qpn_influence);
	boost::write_graphviz(out
		,qpn_influence,vw1,ew1);
	QpnEdgeWriter<QPN_SYNERGY> ew2(qpn_synergy);
	QpnVertexWriter<QPN_SYNERGY> vw2(qpn_synergy);
	boost::write_graphviz(out
		,qpn_synergy,vw2,ew2);
	}

void Qpn_graph::observeVertexValue(std::string vName, int value)
	{
	qpn_vertex& v = qpn_influence[vName];
	v.set_value(value);
	Sign sign;
	if(value == 1)
		sign= Sign('+');
	else
		sign = Sign('-');
	v.set_sign(sign);


	//TODO Is it necessary to propagate a sign variation when a value is observed.
	//map<string, bool> colorMap =  map<string, bool>();

	////fromChild of the propagateSign is set to true to ensure we can propagate the sign toward the parent of the vertex 
	//propagateSign(vName,colorMap, true);
	}

void Qpn_graph::observeVertexVariation(std::string vName, Sign sign)
	{
	qpn_influence[vName].set_sign(sign);
	map<string, bool> colorMap =  map<string, bool>();

	//fromChild of the propagateSign is set to true to ensure we can propagate the sign toward the parent of the vertex 
	propagateSign(vName,colorMap, true);
	}


void Qpn_graph::propagateSign(string vName, map<string, bool> colorMap, bool fromChild)
	{
	colorMap[vName] = true;
	qpn_vertex& vertex = qpn_influence[vName];
	Vertex v = qpn_influence.vertex(vName);
	VertexSyn vS = qpn_synergy.vertex(vName);
	list<Influence> activeInfluences =list<Influence>(); 
	list<Synergy> activesSynergies =list<Synergy>(); 
	Sign vSign = vertex.get_sign();

	findNeighbours(vName, colorMap, fromChild,activeInfluences, activesSynergies);
	for(list<Influence>::iterator it = activeInfluences.begin(); it!=activeInfluences.cend(); it++)
		{
		Vertex currentV;
		bool isParent = source(*it,qpn_influence)!=v;
		if(isParent)
			currentV = source(*it,qpn_influence);
		else
			currentV= target(*it,qpn_influence);
		qpn_vertex&  current_vertex = qpn_influence[getVName(currentV,qpn_influence)];
		cout<<"INFL source "<<vName<<" "<<vertex.get_sign()<<" target "<<current_vertex.name<<" "<<current_vertex.get_sign()<<endl;
		Sign newSign = current_vertex.get_sign() + (vSign * qpn_influence[*it].get_sign());
		if (newSign != current_vertex.get_sign())
			{
			current_vertex.set_sign(newSign);
			propagateSign(current_vertex.name, map<string, bool>(colorMap), isParent);
			}
		}
	for(list<Synergy>::iterator it = activesSynergies.begin(); it!=activesSynergies.cend(); it++)
		{
		VertexSyn currentV;
		bool isParent = source(*it,qpn_synergy)!=vS;
		if(isParent)
			currentV = source(*it,qpn_synergy);
		else
			currentV= target(*it,qpn_synergy);
		qpn_vertex&  current_vertex = qpn_influence[getVName(currentV,qpn_synergy)];
		cout<<"SYN source "<<vName<<" "<<vertex.get_sign()<<" target "<<current_vertex.name<<" "<<current_vertex.get_sign()<<endl;
		Sign newSign = current_vertex.get_sign() + (vSign * qpn_synergy[*it].get_sign());
		if (newSign != current_vertex.get_sign())
			{
			current_vertex.set_sign(newSign);
			//always return true for the fromChild value because synergies are undirected
			propagateSign(current_vertex.name, map<string, bool>(colorMap), true);
			}
		}
	}

void Qpn_graph::findNeighbours(string& vName,  map<std::string, bool>& colorMap, bool fromChild, list<Influence>& activesInfluences, list<Synergy>& activesSynergies)
	{
	Vertex v = qpn_influence.vertex(vName); 
	if (fromChild)
		{
		findSourcesByEdgeType(vName,qpn_influence,colorMap,in_edges(v,qpn_influence),activesInfluences);
		//in_influence_iterator in_i, in_end;
		//for(boost::tie(in_i, in_end) = in_edges(v, qpn_influence); in_i !=in_end; in_i++)
		//	{
		//	Vertex currentV = source(*in_i, qpn_influence);
		//	qpn_vertex& current_vertex = get(vertex_bundle,qpn_influence, currentV);
		//	string currentVName = current_vertex.name;
		//	if(! colorMap[currentVName] && current_vertex.get_value() == -1)
		//		{
		//		activesInfluences.push_back(*in_i);
		//		}
		//	}
		}
	findTargetsByEdgeType(vName,qpn_influence,colorMap,out_edges(v,qpn_influence),activesInfluences);
	//out_influence_iterator out_i, out_end;
	//for(boost::tie(out_i, out_end) = out_edges(v, qpn_influence); out_i !=out_end; out_i++){
	//	Vertex currentV =target(*out_i, qpn_influence);
	//	qpn_vertex& current_vertex = get(vertex_bundle,qpn_influence, currentV);
	//	string currentVName =current_vertex.name;
	//	if(! colorMap[currentVName]  && current_vertex.get_value() == -1)
	//		{
	//		activesInfluences.push_back(*out_i);
	//		}
	//	}
	VertexSyn vS = qpn_synergy.vertex(vName); 
	if (existV(vName,qpn_synergy))
		findTargetsByEdgeType(vName,qpn_synergy,colorMap,out_edges(vS,qpn_synergy),activesSynergies);

	}

template<typename G,typename E, typename IteratorType>
void Qpn_graph::findTargetsByEdgeType(string& vName, G& qpn,  map<string, bool>& colorMap, pair<IteratorType,IteratorType> iters, list<E>& activesEdges)
	{
	graph_traits<G>::vertex_descriptor v = qpn.vertex(vName);
	IteratorType it, end;
	for(boost::tie(it, end) = iters; it !=end; it++)
		{
		graph_traits<G>::vertex_descriptor currentV = target(*it, qpn);
		auto& current_vertex = get(vertex_bundle,qpn, currentV);
		string currentVName = current_vertex.name;
		if(! colorMap[currentVName] && current_vertex.get_value() == -1)
			{
			activesEdges.push_back(*it);
			}
		}
	}

template<typename G,typename E, typename IteratorType>
void Qpn_graph::findSourcesByEdgeType(string& vName, G& qpn,  map<string, bool>& colorMap, pair<IteratorType,IteratorType> iters, list<E>& activesEdges)
	{
	graph_traits<G>::vertex_descriptor v = qpn.vertex(vName);
	IteratorType it, end;
	for(boost::tie(it, end) = iters; it !=end; it++)
		{
		graph_traits<G>::vertex_descriptor currentV = source(*it, qpn);
		auto& current_vertex = get(vertex_bundle,qpn, currentV);
		string currentVName = current_vertex.name;
		if(! colorMap[currentVName] && current_vertex.get_value() == -1)
			{
			activesEdges.push_back(*it);
			}
		}
	}


bool Qpn_graph::hasObservedDescendant(Vertex& v, map<Vertex, bool>& colorMap)
	{

	//TODO Implement this method with the BGL dfs algorithm using a visitor
	//observed_descendant_dfs_visitor vis = observed_descendant_dfs_visitor();
	//std::map<Vertex, boost::default_color_type> c_m; 
	//boost::depth_first_search(qpn_influence, vis);
	//cout<<vis.hasDescendant;
	//TODO This information can be put in the property of each vertex and changed only when a node is observed
	out_influence_iterator  out_i, out_end;
	for(boost::tie(out_i, out_end) = out_edges(v, qpn_influence); out_i !=out_end; out_i++){
		Vertex currentV =target(*out_i, qpn_influence);
		if (! colorMap[currentV])
			{
			colorMap[currentV]= true;
			qpn_vertex& current_vertex = get(vertex_bundle,qpn_influence, currentV);
			if(current_vertex.get_value() != -1)
				return true;
			if (hasObservedDescendant(currentV,map<Vertex, bool>(colorMap)))
				return true;
			}
		}
	return false;
	}

bool Qpn_graph::hasObservedDescendant(Vertex& v)
	{
	map<Vertex, bool> colorMap = map<Vertex, bool>();
	return hasObservedDescendant(v,colorMap);
	}

template <typename Graph>
bool Qpn_graph::existV(std::string vName, Graph& g)
	{
	return g.vertex(vName) != graph_traits<Graph>::null_vertex();
	}

template <typename G, typename V>
std::string Qpn_graph::getVName(V& v, G& g)
	{
	return get(vertex_bundle,g, v).name;
	}
