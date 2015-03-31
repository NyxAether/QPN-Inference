// Learning_Bayesian_Network.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "n_matrix.h"
#include <iostream>
#include <string>
#include "poset_forest.h"
#include "qpn_sign.h"






using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{

	n_matrix m = n_matrix("n_matrix_test.txt");
	pair<unsigned int, unsigned int> a =m.get(1,1,0);
	cout<< a.first <<":"<<a.second<<endl;


	poset_forest<bool> p = poset_forest<bool>();
	map<string, pair<bool,Sign>>* p_A=new map<string, pair<bool,Sign>>();
	map<string, pair<bool,Sign>>* p_A2=new map<string, pair<bool,Sign>>();
	map<string, pair<bool,Sign>>* p_A3=new map<string, pair<bool,Sign>>();
	map<string, pair<bool,Sign>>* p_A4=new map<string, pair<bool,Sign>>();
	map<string, pair<bool,Sign>>* p_A5=new map<string, pair<bool,Sign>>();
	map<string, pair<bool,Sign>>* p_A6=new map<string, pair<bool,Sign>>();
	map<string, pair<bool,Sign>>* p_A7=new map<string, pair<bool,Sign>>();
	map<string, pair<bool,Sign>>* p_A8=new map<string, pair<bool,Sign>>();
	Sign s = Sign::ZERO_SIGN;
	//pair<bool,Sign> youpi =make_pair(false,Sign::PLUS_SIGN);
	(*p_A)["X1"]=make_pair(true,Sign::PLUS_SIGN);
	(*p_A)["X2"]=make_pair(true,Sign::MINUS_SIGN);
	(*p_A)["X3"]=make_pair(true,Sign::QMARK_SIGN);

	(*p_A2)["X1"]=make_pair(true,Sign::PLUS_SIGN);
	(*p_A2)["X2"]=make_pair(false,Sign::PLUS_SIGN);
	(*p_A2)["X3"]=make_pair(true,Sign::QMARK_SIGN);

	(*p_A3)["X1"]=make_pair(false,Sign::MINUS_SIGN);
	(*p_A3)["X2"]=make_pair(true,Sign::MINUS_SIGN);
	(*p_A3)["X3"]=make_pair(true,Sign::QMARK_SIGN);

	(*p_A4)["X1"]=make_pair(false,Sign::MINUS_SIGN);
	(*p_A4)["X2"]=make_pair(false,Sign::PLUS_SIGN);
	(*p_A4)["X3"]=make_pair(true,Sign::QMARK_SIGN);

	(*p_A5)["X1"]=make_pair(true,Sign::PLUS_SIGN);
	(*p_A5)["X2"]=make_pair(true,Sign::MINUS_SIGN);
	(*p_A5)["X3"]=make_pair(false,Sign::QMARK_SIGN);

	(*p_A6)["X1"]=make_pair(true,Sign::PLUS_SIGN);
	(*p_A6)["X2"]=make_pair(false,Sign::PLUS_SIGN);
	(*p_A6)["X3"]=make_pair(false,Sign::QMARK_SIGN);

	(*p_A7)["X1"]=make_pair(false,Sign::MINUS_SIGN);
	(*p_A7)["X2"]=make_pair(true,Sign::MINUS_SIGN);
	(*p_A7)["X3"]=make_pair(false,Sign::QMARK_SIGN);

	(*p_A8)["X1"]=make_pair(false,Sign::MINUS_SIGN);
	(*p_A8)["X2"]=make_pair(false,Sign::PLUS_SIGN);
	(*p_A8)["X3"]=make_pair(false,Sign::QMARK_SIGN);

	parents_sign_state<bool>* pss = new parents_sign_state<bool>("A",p_A);
	parents_sign_state<bool>* pss2 = new parents_sign_state<bool>("A",p_A2);
	parents_sign_state<bool>* pss3 = new parents_sign_state<bool>("A",p_A3);
	parents_sign_state<bool>* pss4 = new parents_sign_state<bool>("A",p_A4);
	parents_sign_state<bool>* pss5 = new parents_sign_state<bool>("A",p_A5);
	parents_sign_state<bool>* pss6 = new parents_sign_state<bool>("A",p_A6);
	parents_sign_state<bool>* pss7 = new parents_sign_state<bool>("A",p_A7);
	parents_sign_state<bool>* pss8 = new parents_sign_state<bool>("A",p_A8);
	poset_forest<bool> poset = poset_forest<bool>();
	poset.addState(pss);
	poset.addState(pss2);
	poset.addState(pss3);
	poset.addState(pss4);
	poset.addState(pss5);
	poset.addState(pss6);
	poset.addState(pss7);
	poset.addState(pss8);

	vector<vector<parents_sign_state<bool>*>> lowerSets =vector<vector<parents_sign_state<bool>*>>();
	poset.findLowerSets(lowerSets);
		return 0;
}

