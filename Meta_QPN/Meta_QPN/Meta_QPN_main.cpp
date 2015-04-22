// Meta_QPN.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "meta_qpn_controller.h"
#include "pl.h"
#include "pilgrim\general\pmBayesianNetwork.h"



using namespace std;
using namespace PILGRIM;
using namespace boost;

plMt19937 plMt19937::generator_;

int _tmain(int argc, _TCHAR* argv[])
	{
//	meta_qpn< bool> qpn_manager = meta_qpn< bool>();

	////Influences
	//qpn_descriptor<bool , boost::bidirectionalS>* qpn_influences =new qpn_influence<bool>(); 
	//qpn_influences->addVertex("X1");
	//qpn_influences->addVertex("X2");
	//qpn_influences->addVertex("X3");
	//qpn_influences->addVertex("X4");
	//qpn_influences->addVertex("X5");

	//vector<string> v = vector<string>();
	//v.push_back("X1");
	//v.push_back("X2");
	//qpn_edge_influence* edge = new qpn_edge_influence(Sign::PLUS_SIGN);
	//qpn_influences->addEdge(edge, v);

	//v = vector<string>();
	//v.push_back("X1");
	//v.push_back("X3");
	//edge = new qpn_edge_influence(Sign::MINUS_SIGN);
	//qpn_influences->addEdge(edge, v);

	//v = vector<string>();
	//v.push_back("X3");
	//v.push_back("X4");
	//edge = new qpn_edge_influence(Sign::MINUS_SIGN);
	//qpn_influences->addEdge(edge, v);

	//v = vector<string>();
	//v.push_back("X2");
	//v.push_back("X4");
	//edge = new qpn_edge_influence(Sign::PLUS_SIGN);
	//qpn_influences->addEdge(edge, v);


	////v = vector<string>();
	////v.push_back("X5");
	////v.push_back("X2");
	////edge = new qpn_edge_influence(Sign::MINUS_SIGN);
	////qpn_influences->addEdge(edge, v);


	//qpn_manager.addQpn(qpn_influences);

	////Product Synergies
	//qpn_descriptor<bool , boost::undirectedS>* qpn_synergies =new qpn_product_synergy<bool>(); 

	//v = vector<string>();
	//v.push_back("X2");
	//v.push_back("X3");
	//v.push_back("X4");
	//map<bool,Sign> signMap = map<bool,Sign>();
	//signMap[0]=Sign::MINUS_SIGN;
	//signMap[1]=Sign::PLUS_SIGN;
	//qpn_edge_product_synergy<bool>* esyn = new qpn_edge_product_synergy<bool>(signMap);
	//qpn_synergies->addEdge(esyn, v);
	//qpn_manager.addQpn(qpn_synergies);

	////Additive Synergies
	//qpn_synergies =new qpn_additive_synergy<bool>(); 
	//v = vector<string>();
	//v.push_back("X1");
	//v.push_back("X5");
	//qpn_edge_additive_synergy* eas1 = new qpn_edge_additive_synergy(Sign::PLUS_SIGN, "X2");
	//qpn_synergies->addEdge(eas1,v);
	//v = vector<string>();
	//v.push_back("X6");
	//v.push_back("X5");
	//qpn_edge_additive_synergy* eas2 = new qpn_edge_additive_synergy(Sign::MINUS_SIGN, "X2");
	//qpn_synergies->addEdge(eas2,v);
	//qpn_manager.addQpn(qpn_synergies);

	////Non-monotonic influences

	//typedef tuple<qpn_node<bool>**, qpn_edge_additive_synergy*, map<bool, Sign>> provoker_type;
	//typedef list<provoker_type> provokers_type;
	//qpn_influences = new qpn_nm_influence<bool>();
	//v = vector<string>();
	//v.push_back("X5");
	//v.push_back("X2");
	//
	//provokers_type provokers = provokers_type();
	//provokers.push_back(provoker_type(qpn_manager.getNode("X1"),eas1, signMap));
	//map<bool,Sign> signMap2 = map<bool,Sign>();
	//signMap2[0]=Sign::PLUS_SIGN;
	//signMap2[1]=Sign::ZERO_SIGN;
	//provokers.push_back(provoker_type(qpn_manager.getNode("X6"),eas2, signMap2));
	//qpn_edge_nm_influence<bool>* enmi = new qpn_edge_nm_influence<bool>(provokers);
	//qpn_influences->addEdge(enmi, v);
	//qpn_manager.addQpn(qpn_influences);

	////{qpn_manager.observeNodeValue("X1",0);
	//qpn_manager.observeNodeValue("X4",0);
	//	qpn_manager.observeNodeValue("X6",0);
	//qpn_manager.observeNodeSign("X3",Sign::MINUS_SIGN); 
	
	//qpn_descriptor_directed<bool>* qpn_influences =new qpn_influence<bool>(); 

	//vector<string> v = vector<string>();
	//v.push_back("U");
	//v.push_back("W");
	//qpn_edge_influence* edge = new qpn_edge_influence(Sign::PLUS_SIGN);
	//qpn_influences->addEdge(edge, v);

	//v = vector<string>();
	//v.push_back("M");
	//v.push_back("D");
	//edge = new qpn_edge_influence(Sign::PLUS_SIGN);
	//qpn_influences->addEdge(edge, v);

	//v = vector<string>();
	//v.push_back("L");
	//v.push_back("W");
	//edge = new qpn_edge_influence(Sign::PLUS_SIGN);
	//qpn_influences->addEdge(edge, v);

	//v = vector<string>();
	//v.push_back("W");
	//v.push_back("D");
	//edge = new qpn_edge_influence(Sign::PLUS_SIGN);
	//qpn_influences->addEdge(edge, v);

	////v = vector<string>();
	////v.push_back("L");
	////v.push_back("D");
	////edge = new qpn_edge_influence(Sign::MINUS_SIGN);
	////qpn_influences->addEdge(edge, v);


	//qpn_manager.addQpn(qpn_influences);

	////Product Synergies
	//qpn_descriptor_undirected<bool>* qpn_synergies =new qpn_product_synergy<bool>(); 

	//v = vector<string>();
	//v.push_back("U");
	//v.push_back("L");
	//v.push_back("W");
	//map<bool,Sign> signMap = map<bool,Sign>();
	//signMap[0]=Sign::MINUS_SIGN;
	//signMap[1]=Sign::MINUS_SIGN;
	//qpn_edge_product_synergy<bool>* esyn = new qpn_edge_product_synergy<bool>(signMap);
	//qpn_synergies->addEdge(esyn, v);
	//qpn_manager.addQpn(qpn_synergies);


	////Context specific
	//qpn_descriptor_directed<bool>* qpn_contexts =new qpn_context_specific<bool>(); 

	//list<pair<list<pair<string,bool>>,Sign>> contexts = list<pair<list<pair<string,bool>>,Sign>>();
	//pair<string,bool> d, _m, _w, _m_w;
	////d = make_pair("D",true);
	//_m = make_pair("M",false);
	//_w = make_pair("W",false);
	////list<pair<string,bool>> dC = list<pair<string,bool>>();
	//list<pair<string,bool>> _mC = list<pair<string,bool>>();
	//list<pair<string,bool>> _wC = list<pair<string,bool>>();
	//	list<pair<string,bool>> _m_wC = list<pair<string,bool>>();
	////dC.push_back(d);
	//_mC.push_back(_m);
	//_wC.push_back(_w);
	//_m_wC.push_back(_m);
	//_m_wC.push_back(_w);
	////contexts.push_back(make_pair(dC,Sign::PLUS_SIGN));
	//contexts.push_back(make_pair(_mC,Sign::MINUS_SIGN));
	//contexts.push_back(make_pair(_wC,Sign::PLUS_SIGN));
	//contexts.push_back(make_pair(_m_wC,Sign::ZERO_SIGN));

	//list<qpn_node<bool>**> nodes = list<qpn_node<bool>**>();
	//nodes.push_back(qpn_manager.getNode("M"));
	//nodes.push_back(qpn_manager.getNode("W"));
	//qpn_edge_context_specific<bool>* ecs = new qpn_edge_context_specific<bool>(nodes,contexts);

	//v = vector<string>();
	//v.push_back("L");
	//v.push_back("D");
	//qpn_contexts->addEdge(ecs,v);

	//qpn_manager.addQpn(qpn_contexts);

	//qpn_manager.observeNodeValue("M",false);
	//qpn_manager.observeNodeSign("D",Sign::PLUS_SIGN);
	//ofstream outf =ofstream("net.gv");
	//qpn_manager.writeGraphViz(outf);
	
	meta_qpn_controller qpn = meta_qpn_controller();

	qpn.addInfluence("A","B", Sign::PLUS_SIGN);
	qpn.addInfluence("A","C", Sign::MINUS_SIGN);
	qpn.addInfluence("C","D", Sign::ZERO_SIGN);

	qpn.addInfluence("E","D", Sign::MINUS_SIGN);
	qpn.addInfluence("F","D", Sign::PLUS_SIGN);

	qpn.addProductSynergy("B","C","D",Sign::MINUS_SIGN);
	qpn.addProductSynergy("B","E","D",Sign::MINUS_SIGN,Sign::PLUS_SIGN);

	qpn.addProductSynergy("C","F","D",Sign::PLUS_SIGN,Sign::PLUS_SIGN);
	
	//qpn.addContextSpecific("B","D","context.txt");

	qpn.observeNodeValue("E",true);
	qpn.observeNodeValue("F",true);
	qpn.observeNodeSign("B",Sign::MINUS_SIGN);


	qpn.writeGraphViz("net.gv");

//plSymbol A("A", PL_BINARY_TYPE);
//plSymbol B("B", PL_BINARY_TYPE);
//plSymbol C("C", PL_BINARY_TYPE);
//plSymbol D("D", PL_BINARY_TYPE);
//plSymbol E("E", PL_BINARY_TYPE);
//
//cout<<A.name()<<endl;
//// Probability table of A
//plProbValue tableA[] = {0.4,0.6};
//plProbTable P_A(A, tableA);
//
//// Probability table of B
//plProbValue tableB[] = {0.18,0.82};
//plProbTable P_B(B, tableB);
//
//// Probability table of C
//plProbValue tableC[] = {0.75,0.25};
//plProbTable P_C(C, tableC);
//
//// Probability table of D, which depends on A and B
//plProbValue tableD_knowingA_B[] = {
//	0.6,0.4,
//	0.3,0.7,
//	0.1,0.9,
//	0.5,0.5
//	};
//plDistributionTable P_D(D,A^B,tableD_knowingA_B);
//
//// Probability table of E, which depends on C and D
//plProbValue tableE_knowingC_D[] = {
//	0.59,0.41,
//	0.25,0.75,
//	0.8,0.2,
//	0.35,0.65
//	};
//plDistributionTable P_E(E,C^D,tableE_knowingC_D);
//
//// Joint distribution
//plJointDistribution jd(A^B^C^D^E, P_A*P_B*P_C*P_D*P_E);
//
//// Creation and print of the bayesian network
//pmBayesianNetwork bn(jd);
//bn.summary();
	return 0; 
	}

