// Learning_Bayesian_Network.cpp : définit le point d'entrée pour l'application console.
//
#pragma once
#include "stdafx.h"
#include "n_matrix.h"
#include <iostream>
#include <string>
#include "poset_forest.h"
#include "qpn_sign.h"
#include "meta_qpn_controller.h"
#include "bayesian_factory.h"
#include "pilgrim\general\pmBayesianNetwork.h"





using namespace PILGRIM;
using namespace std;

plMt19937 plMt19937::generator_;

int _tmain(int argc, _TCHAR* argv[])
{ 
//// Variable definitions
plSymbol A("A", PL_BINARY_TYPE);
//plSymbol B("B", PL_BINARY_TYPE);
//plSymbol C("C", PL_BINARY_TYPE);
//plSymbol D("D", PL_BINARY_TYPE);
//plSymbol E("E", PL_BINARY_TYPE);
cout<<A.name()<<endl;
////
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
//	//n_matrix m = n_matrix("n_matrix_test.txt");
//	//pair<unsigned int, unsigned int> a =m.get(1,1,0);
//	//cout<< a.first <<":"<<a.second<<endl;
//
//
	//poset_forest<bool> p = poset_forest<bool>();
	//map<string, pair<bool,Sign>>* p_A=new map<string, pair<bool,Sign>>();
	//map<string, pair<bool,Sign>>* p_A2=new map<string, pair<bool,Sign>>();
	//map<string, pair<bool,Sign>>* p_A3=new map<string, pair<bool,Sign>>();
	//map<string, pair<bool,Sign>>* p_A4=new map<string, pair<bool,Sign>>();
	//map<string, pair<bool,Sign>>* p_A5=new map<string, pair<bool,Sign>>();
	//map<string, pair<bool,Sign>>* p_A6=new map<string, pair<bool,Sign>>();
	//map<string, pair<bool,Sign>>* p_A7=new map<string, pair<bool,Sign>>();
	//map<string, pair<bool,Sign>>* p_A8=new map<string, pair<bool,Sign>>();
	//Sign s = Sign::ZERO_SIGN;
	////pair<bool,Sign> youpi =make_pair(false,Sign::PLUS_SIGN);
	//(*p_A)["X1"]=make_pair(true,Sign::PLUS_SIGN);
	//(*p_A)["X2"]=make_pair(true,Sign::MINUS_SIGN);
	//(*p_A)["X3"]=make_pair(true,Sign::QMARK_SIGN);

	//(*p_A2)["X1"]=make_pair(true,Sign::PLUS_SIGN);
	//(*p_A2)["X2"]=make_pair(false,Sign::PLUS_SIGN);
	//(*p_A2)["X3"]=make_pair(true,Sign::QMARK_SIGN);

	//(*p_A3)["X1"]=make_pair(false,Sign::MINUS_SIGN);
	//(*p_A3)["X2"]=make_pair(true,Sign::MINUS_SIGN);
	//(*p_A3)["X3"]=make_pair(true,Sign::QMARK_SIGN);

	//(*p_A4)["X1"]=make_pair(false,Sign::MINUS_SIGN);
	//(*p_A4)["X2"]=make_pair(false,Sign::PLUS_SIGN);
	//(*p_A4)["X3"]=make_pair(true,Sign::QMARK_SIGN);

	//(*p_A5)["X1"]=make_pair(true,Sign::PLUS_SIGN);
	//(*p_A5)["X2"]=make_pair(true,Sign::MINUS_SIGN);
	//(*p_A5)["X3"]=make_pair(false,Sign::QMARK_SIGN);

	//(*p_A6)["X1"]=make_pair(true,Sign::PLUS_SIGN);
	//(*p_A6)["X2"]=make_pair(false,Sign::PLUS_SIGN);
	//(*p_A6)["X3"]=make_pair(false,Sign::QMARK_SIGN);

	//(*p_A7)["X1"]=make_pair(false,Sign::MINUS_SIGN);
	//(*p_A7)["X2"]=make_pair(true,Sign::MINUS_SIGN);
	//(*p_A7)["X3"]=make_pair(false,Sign::QMARK_SIGN);

	//(*p_A8)["X1"]=make_pair(false,Sign::MINUS_SIGN);
	//(*p_A8)["X2"]=make_pair(false,Sign::PLUS_SIGN);
	//(*p_A8)["X3"]=make_pair(false,Sign::QMARK_SIGN);

	//parents_sign_state<bool>* pss = new parents_sign_state<bool>("A",p_A);
	//parents_sign_state<bool>* pss2 = new parents_sign_state<bool>("A",p_A2);
	//parents_sign_state<bool>* pss3 = new parents_sign_state<bool>("A",p_A3);
	//parents_sign_state<bool>* pss4 = new parents_sign_state<bool>("A",p_A4);
	//parents_sign_state<bool>* pss5 = new parents_sign_state<bool>("A",p_A5);
	//parents_sign_state<bool>* pss6 = new parents_sign_state<bool>("A",p_A6);
	//parents_sign_state<bool>* pss7 = new parents_sign_state<bool>("A",p_A7);
	//parents_sign_state<bool>* pss8 = new parents_sign_state<bool>("A",p_A8);
	//poset_forest<bool> poset = poset_forest<bool>();
	//poset.addState(pss);
	//poset.addState(pss2);
	//poset.addState(pss3);
	//poset.addState(pss4);
	//poset.addState(pss5);
	//poset.addState(pss6);
	//poset.addState(pss7);
	//poset.addState(pss8);
//
//	//vector<vector<parents_sign_state<bool>*>> lowerSets =vector<vector<parents_sign_state<bool>*>>();
//	//poset.findLowerSets(lowerSets);
//
//	//PILGRIM::LoadDataSet loader = PILGRIM::LoadDataSet("data_node_A.csv");
//	// size_t nb =1;
//	// size_t nb2 = 5;
//	//pmCSVDataSet* dataset = loader.LoadData(nb, nb2, ';');
//	//vector<bool> col = vector<bool>();
//	//dataset->get_column_values(4,col);
//	//for (auto c=col.begin();c!=col.end();c++)
//	//{
//	//cout<<*c<<endl;
//	//}
//	//cout<<dataset->get_num_fields()<<endl;
//	//cout<<dataset->get_n_records()<<endl;

	meta_qpn_controller qpn = meta_qpn_controller();

	//qpn.addInfluence("A","B", Sign::PLUS_SIGN);
	//qpn.addInfluence("A","C", Sign::MINUS_SIGN);
	qpn.addInfluence("C","D", Sign::QMARK_SIGN);

	qpn.addInfluence("E","D", Sign::MINUS_SIGN);
	qpn.addInfluence("F","D", Sign::PLUS_SIGN);

	//qpn.addProductSynergy("B","C","D",Sign::MINUS_SIGN);
	//qpn.addProductSynergy("B","E","D",Sign::MINUS_SIGN,Sign::PLUS_SIGN);

	//qpn.addProductSynergy("C","F","D",Sign::PLUS_SIGN,Sign::PLUS_SIGN);

	//qpn.addContextSpecific("B","D","context.txt");

	qpn.observeNodeValue("E",true);
	qpn.observeNodeValue("F",false);
	//qpn.observeNodeSign("B",Sign::PLUS_SIGN);

	qpn_node<bool>* n_e= *(qpn.getNode("E"));
	qpn_node<bool>* n_f= *(qpn.getNode("F")); 
	cout<<n_e->getSign()<<n_f->getSign()<<endl;

	qpn.writeGraphViz("net.gv");

	//plSymbol pl_A = plSymbol("A", PL_BINARY_TYPE);
	//plSymbol pl_B = plSymbol("B", PL_BINARY_TYPE);
	//plSymbol pl_C = plSymbol("C", PL_BINARY_TYPE);
	//plSymbol pl_D = plSymbol("D", PL_BINARY_TYPE);
	//plSymbol pl_E = plSymbol("E", PL_BINARY_TYPE);
	//plSymbol pl_F = plSymbol("F", PL_BINARY_TYPE);
	//plVariablesConjunction variable = pl_C ^ pl_E ^ pl_F ^ pl_D;
	//plCSVFileDataDescriptor<int>* ds =new plCSVFileDataDescriptor<int>("data_node_A.csv", variable, true, ';');
	//pmFrequencyCounter<plCSVFileDataDescriptor<int>::CSVDescRowDataType>* fc= new	pmFrequencyCounter<plCSVFileDataDescriptor<int>::CSVDescRowDataType>(ds, variable);
	//vector<plFloat> values = vector<plFloat>();
	//vector<unsigned int> variableSet = vector<unsigned int>();
	//variableSet.push_back(variable.get_symbol_position(pl_D));
	//variableSet.push_back(variable.get_symbol_position(pl_E));
	//variableSet.push_back(variable.get_symbol_position(pl_C));
	//variableSet.push_back(variable.get_symbol_position(pl_F));	
	//fc->frequencyCount(variableSet, values);
	//cout<<pl_D.name();
	//for (auto i = variable.begin(); i!= variable.end();i++)
	//{
	//cout<<i->name();
	//}

	bayesian_factory bf = bayesian_factory(&qpn); 
	bf.addData("D", "data_node_A.csv");



		//return 0; 
}