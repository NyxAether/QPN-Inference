// Meta_QPN.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "boost\spirit\home\classic\dynamic\impl\conditions.ipp"
#include "qpn_influence.h"
#include "meta_qpn.h"
#include "qpn_descriptor.h"

using namespace std;
using namespace boost;

int _tmain(int argc, _TCHAR* argv[])
	{
	/*meta_qpn< int> qpn_manager = meta_qpn< int>();
	qpn_descriptor<int>* qpn =new qpn_influence<int>(); 
	qpn->addVertex("chat");
	qpn->addVertex("chien");
		vector<string> v = vector<string>();
		v.push_back("chat");
		v.push_back("chien");
	qpn->addEdge(qpn_edge_influence(Sign::MINUS_SIGN), v);
	qpn_manager.addQpn(qpn,true);
	qpn_manager.writeGraphViz(cout);*/
	return 0;
	}

