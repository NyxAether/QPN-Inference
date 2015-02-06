#include "qpn_graph.h"
#include "boost/graph/graphviz.hpp"


using namespace boost;
using namespace std;

Qpn_graph::Qpn_graph(void)
{
	qpn_influence = QPN_INFLUENCE();
	vNames = get(vertex_name, qpn_influence);
	vSigns = get(vertex_sign, qpn_influence);
	vValues = get(vertex_value, qpn_influence);
	eSigns = get(edge_sign, qpn_influence);
}


Qpn_graph::~Qpn_graph(void)
{
}
 
void Qpn_graph::addVertex(string name)
{
	Vertex v = add_vertex(name, qpn_influence);
	vNames[v] = name;
	Sign s = {'0'};
	vSigns[v] = s;
	vValues[v] = -1;

	
}

//void Qpn_graph::addFixedVertex(std::string name, bool value)
//{
//	Vertex v = add_vertex(name, qpn_influence);
//	vNames[v] = name;
//	vValues[v] =value;
//}

void Qpn_graph::addInfluence(string from, string to, Sign sign)
{
	if(!existV(from))
		addVertex(from);
	if(!existV(to))
		addVertex(to);
	Edge e = add_edge_by_label(from, to, qpn_influence).first;
	eSigns[e] = sign;
}

//void Qpn_graph::addProductSynergy(std::string from, std::string to, std::string linkedNode, std::map<bool,Sign>& mapValue)
//{
//	if(!existV(from))
//		addVertex(from);
//	if(!existV(to))
//		addVertex(to);
//	if(!existV(linkedNode))
//		addVertex(linkedNode);
//	Edge e = add_edge_by_label(from, to, qpn).first;
//	eSigns[e] = NULL;
//
//}

void Qpn_graph::writeGraphViz(ostream& out)
{
	
	write_graphviz(out, qpn_influence,make_label_writer(vSigns),
		make_label_writer(get(edge_sign, qpn_influence)));
}

void Qpn_graph::observeVertexValue(std::string vName, int value)
{
	Vertex v = qpn_influence.vertex(vName);
	vValues[v] = value;
	Sign sign = {'+'} ;
	if(value == 1)
	 sign.c ='+';
	else
		sign.c = '-';
	vSigns[v] = sign;
	map<string, bool> colorMap =  map<string, bool>();

	//fromChild of the propagateSign is set to true to ensure we can propagate the sign toward the parent of the vertex 
	propagateSign(v,colorMap, true);


}

void Qpn_graph::propagateSign(Vertex& v, map<string, bool> colorMap, bool fromChild)
{
		colorMap[vNames[v]] = true;
	list<Edge> neighbours =list<Edge>(); 
	Sign vSign = vSigns[v];
	findNeighbours(v, colorMap, fromChild,neighbours);
	for(list<Edge>::iterator it = neighbours.begin(); it!=neighbours.cend(); it++)
	{
		Vertex currentV;
		bool isParent = source(*it,qpn_influence)!=v;
		if(isParent)
			currentV = source(*it,qpn_influence);
		else
			currentV= target(*it,qpn_influence);
		Sign newSign = vSigns[currentV] + (vSign * eSigns[*it]);
		if (newSign != vSigns[currentV])
		{
		vSigns[currentV] = vSigns[currentV] + (vSign * eSigns[*it]);
		propagateSign(currentV, map<string, bool>(colorMap), isParent);
		}
	}
}

void Qpn_graph::findNeighbours(Vertex &v,  std::map<std::string, bool> colorMap, bool fromChild, list<Edge>& neighbours)
{
	if (fromChild)
	{
		in_edge_iterator in_i, in_end;
		for(boost::tie(in_i, in_end) = in_edges(v, qpn_influence); in_i !=in_end; in_i++)
		{
			Vertex currentV = source(*in_i, qpn_influence);
			string currentVName = vNames[currentV];
			if(! colorMap[currentVName] && vValues[currentV] == -1)
			{
				neighbours.push_back(*in_i);
			}
		}
	}
	out_edge_iterator out_i, out_end;
	for(boost::tie(out_i, out_end) = out_edges(v, qpn_influence); out_i !=out_end; out_i++){
		Vertex currentV =target(*out_i, qpn_influence);
		string currentVName = vNames[currentV];
		if(! colorMap[currentVName]  && vValues[currentV] == -1)e
		{
			neighbours.push_back(*out_i);
		}
	}
}

bool Qpn_graph::hasObservedDescendant(Vertex& v)
{
	//TODO This information can be put in the property of each vertex and changed only when a node is observed
	out_edge_iterator  out_i, out_end;
	for(boost::tie(out_i, out_end) = out_edges(v, qpn_influence); out_i !=out_end; out_i++){
		Vertex currentV =target(*out_i, qpn_influence);
		string currentVName = vNames[currentV];
		if(vValues[currentV] != -1)
			return true;
		if (hasObservedDescendant(currentV))
		return true;
	}
	return false;
}

bool Qpn_graph::existV(std::string vName)
{
	return qpn_influence.vertex(vName) != graph_traits<QPN_INFLUENCE>::null_vertex();
}




Sign Sign::operator+(const Sign & s)
{
	Sign r;
	if (c == s.c)
		r.c = c;
	else if(c == '?' || s.c == '?')
		r.c = '?';
	else if (c=='+' && s.c=='-' || c=='-' && s.c=='+')
		r.c = '?';
	else if (c=='0')
		r.c = s.c;
	else 
		r.c = c;
	return r;

}

Sign Sign::operator*(const Sign & s)
{
	Sign r;
	if (c == '0' || s.c == '0')
		r.c = '0';
	else if(c == '?' || s.c == '?')
		r.c = '?';
	else if (c == s.c)
		r.c = '+';
	else 
		r.c = '-';
	return r;

}

bool Sign::operator==(const Sign & s)
{
	return (c == s.c);
}

bool Sign::operator!=(const Sign & s)
{
	return (c != s.c);
}

 ostream& operator<< (ostream& os, const Sign& s)
{
	os << s.c;
	return os;
}





