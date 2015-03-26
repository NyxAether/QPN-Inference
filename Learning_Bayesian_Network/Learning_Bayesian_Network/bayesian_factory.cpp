#include "bayesian_factory.h"

using namespace std;

bayesian_factory::bayesian_factory(meta_qpn_controller* controller):qpn(controller)
	{

	}


bayesian_factory::~bayesian_factory(void)
	{
	}

void bayesian_factory::addData(string nName, string filePath)
	{
	data[nName] = make_shared<n_matrix>(filePath);
	}

void bayesian_factory::build()
	{
	//map<string, plSymbol> symbols =map<string, plSymbol>();//TODO Something goes wrong linking with pl
	list<string>nNames = list<string>();
	qpn->getNodeNames(nNames);
	for (auto i_nName=nNames.begin();i_nName!=nNames.cend();i_nName++)
		{
		auto data_node =data[*i_nName] ;
		if(data_node!=NULL)
			{
			//symbols[*i_nName] =  plSymbol (*i_nName,PL_BINARY_TYPE);//TODO Something goes wrong linking with pl
			
			}
		}
	}

void bayesian_factory::computeLowerSets(string nName, list<string> parentNames)
	{

	}
