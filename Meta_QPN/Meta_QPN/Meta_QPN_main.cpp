// Meta_QPN.cpp : définit le point d'entrée pour l'application console.
//

#include "boost\spirit\home\classic\dynamic\impl\conditions.ipp"
#include "qpn_influence.h"
#include "qpn_product_synergy.h"
#include "meta_qpn.h"
#include "qpn_descriptor.h"
  #include <fstream> 

using namespace std;
using namespace boost;

int main(int argc, char* argv[])
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

	v = vector<string>();
	v.push_back("X5");
	v.push_back("X2");
	edge = new qpn_edge_influence(Sign::MINUS_SIGN);
	qpn_influences->addEdge(edge, v);


	qpn_manager.addQpn(qpn_influences);

	//Synergies
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
	
	//Observe values and signs
	qpn_manager.observeNodeValue("X4",1);
	qpn_manager.observeNodeSign("X5",Sign::MINUS_SIGN); 
	ofstream outf =ofstream("net.gv");
	qpn_manager.writeGraphViz(outf);
	return 0;
	}

