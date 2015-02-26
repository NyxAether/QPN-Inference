// Meta_QPN.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "boost\spirit\home\classic\dynamic\impl\conditions.ipp"
#include "qpn_influence.h"
#include "qpn_product_synergy.h"
#include "qpn_additive_synergy.h"
#include "qpn_nm_influence.h"
#include "meta_qpn.h"
#include "qpn_descriptor.h"
#include <fstream> 

using namespace std;
using namespace boost;

int _tmain(int argc, _TCHAR* argv[])
	{
	meta_qpn< int> qpn_manager = meta_qpn< int>();

	//Influences
	qpn_descriptor<int , boost::bidirectionalS>* qpn_influences =new qpn_influence<int>(); 
	qpn_influences->addVertex("X1");
	qpn_influences->addVertex("X2");
	qpn_influences->addVertex("X3");
	qpn_influences->addVertex("X4");
	qpn_influences->addVertex("X5");

	vector<string> v = vector<string>();
	v.push_back("X1");
	v.push_back("X2");
	qpn_edge_influence* edge = new qpn_edge_influence(Sign::PLUS_SIGN);
	qpn_influences->addEdge(edge, v);

	v = vector<string>();
	v.push_back("X1");
	v.push_back("X3");
	edge = new qpn_edge_influence(Sign::MINUS_SIGN);
	qpn_influences->addEdge(edge, v);

	v = vector<string>();
	v.push_back("X3");
	v.push_back("X4");
	edge = new qpn_edge_influence(Sign::MINUS_SIGN);
	qpn_influences->addEdge(edge, v);

	v = vector<string>();
	v.push_back("X2");
	v.push_back("X4");
	edge = new qpn_edge_influence(Sign::PLUS_SIGN);
	qpn_influences->addEdge(edge, v);


	//v = vector<string>();
	//v.push_back("X5");
	//v.push_back("X2");
	//edge = new qpn_edge_influence(Sign::MINUS_SIGN);
	//qpn_influences->addEdge(edge, v);


	qpn_manager.addQpn(qpn_influences);

	//Product Synergies
	qpn_descriptor<int , boost::undirectedS>* qpn_synergies =new qpn_product_synergy<int>(); 

	v = vector<string>();
	v.push_back("X2");
	v.push_back("X3");
	v.push_back("X4");
	map<int,Sign> signMap = map<int,Sign>();
	signMap[0]=Sign::MINUS_SIGN;
	signMap[1]=Sign::PLUS_SIGN;
	qpn_edge_product_synergy<int>* esyn = new qpn_edge_product_synergy<int>(signMap);
	qpn_synergies->addEdge(esyn, v);
	qpn_manager.addQpn(qpn_synergies);

	//Additive Synergies
	qpn_synergies =new qpn_additive_synergy<int>(); 
	v = vector<string>();
	v.push_back("X1");
	v.push_back("X5");
	qpn_edge_additive_synergy* eas1 = new qpn_edge_additive_synergy(Sign::PLUS_SIGN, "X2");
	qpn_synergies->addEdge(eas1,v);
	v = vector<string>();
	v.push_back("X6");
	v.push_back("X5");
	qpn_edge_additive_synergy* eas2 = new qpn_edge_additive_synergy(Sign::MINUS_SIGN, "X2");
	qpn_synergies->addEdge(eas2,v);
	qpn_manager.addQpn(qpn_synergies);

	//Non-monotonic influences

	typedef std::tuple<qpn_node<int>**, qpn_edge_additive_synergy*, map<int, Sign>> provoker_type;
	typedef list<provoker_type> provokers_type;
	qpn_influences = new qpn_nm_influence<int>();
	v = vector<string>();
	v.push_back("X5");
	v.push_back("X2");
	
	provokers_type provokers = provokers_type();
	provokers.push_back(provoker_type(qpn_manager.getNode("X1"),eas1, signMap));
	map<int,Sign> signMap2 = map<int,Sign>();
	signMap2[0]=Sign::PLUS_SIGN;
	signMap2[1]=Sign::ZERO_SIGN;
	provokers.push_back(provoker_type(qpn_manager.getNode("X6"),eas2, signMap2));
	qpn_edge_nm_influence<int>* enmi = new qpn_edge_nm_influence<int>(provokers);
	qpn_influences->addEdge(enmi, v);
	qpn_manager.addQpn(qpn_influences);

	qpn_manager.observeNodeValue("X1",1);
	qpn_manager.observeNodeValue("X4",0);
		qpn_manager.observeNodeValue("X6",0);
	qpn_manager.observeNodeSign("X3",Sign::MINUS_SIGN); 
	ofstream outf =ofstream("net.gv");
	qpn_manager.writeGraphViz(outf);
	return 0;
	}

