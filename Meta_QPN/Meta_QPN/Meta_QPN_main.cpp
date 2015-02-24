// Meta_QPN.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "boost\spirit\home\classic\dynamic\impl\conditions.ipp"
#include "qpn_influence.h"
#include "meta_qpn.h"
#include "qpn_descriptor.h"
  #include <fstream> 

using namespace std;
using namespace boost;

int _tmain(int argc, _TCHAR* argv[])
	{
	meta_qpn< int> qpn_manager = meta_qpn< int>();
	qpn_descriptor<int , boost::bidirectionalS>* qpn =new qpn_influence<int>(); 
	qpn->addVertex("X1");
	qpn->addVertex("X2");
	qpn->addVertex("X3");
	qpn->addVertex("X4");
	qpn->addVertex("X5");

	vector<string> v = vector<string>();
	v.push_back("X1");
	v.push_back("X2");
	qpn_edge_influence* edge = new qpn_edge_influence(Sign::PLUS_SIGN);
	qpn->addEdge(edge, v);

	v = vector<string>();
	v.push_back("X1");
	v.push_back("X3");
	 edge = new qpn_edge_influence(Sign::MINUS_SIGN);
	qpn->addEdge(edge, v);

	 v = vector<string>();
	v.push_back("X3");
	v.push_back("X4");
	 edge = new qpn_edge_influence(Sign::MINUS_SIGN);
	qpn->addEdge(edge, v);

	v = vector<string>();
	v.push_back("X2");
	v.push_back("X4");
	edge = new qpn_edge_influence(Sign::PLUS_SIGN);
	qpn->addEdge(edge, v);

	v = vector<string>();
	v.push_back("X5");
	v.push_back("X2");
	edge = new qpn_edge_influence(Sign::MINUS_SIGN);
	qpn->addEdge(edge, v);

	qpn->observeNodeValue("X4",0);

	qpn_manager.addQpn(qpn);
	qpn_manager.observeNodeSign("X5",Sign::MINUS_SIGN);
	ofstream outf =ofstream("net.gv");
	qpn_manager.writeGraphViz(outf);
	return 0;
	}

