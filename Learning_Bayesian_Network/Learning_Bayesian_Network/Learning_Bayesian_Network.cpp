// Learning_Bayesian_Network.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "n_matrix.h"
#include <iostream>
#include <string>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{

	n_matrix m = n_matrix("n_matrix_test.txt");
	pair<unsigned int, unsigned int> a =m.get(1,1,0);
	cout<< a.first <<":"<<a.second<<endl;
		return 0;
}

