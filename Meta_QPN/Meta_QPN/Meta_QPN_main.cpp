// Meta_QPN.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "boost\spirit\home\classic\dynamic\impl\conditions.ipp"
#include "qpn_influence.h"
#include "meta_qpn.h"
#include "qpn_descriptor.h"


int _tmain(int argc, _TCHAR* argv[])
{
//meta_qpn< qpn_descriptor, int, qpn_edge> qpn_manager = meta_qpn();
	qpn_influence<int> qpn =qpn_influence<int>(); 

	return 0;
}

