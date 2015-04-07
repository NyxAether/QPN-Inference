#include "bayesian_factory.h"

using namespace std;

bayesian_factory::bayesian_factory(meta_qpn_controller* controller):qpn(controller)
	{
	list<string> nNames= list<string>();
	controller->getNodeNames(nNames);
	for (auto i_nName = nNames.begin(); i_nName!=nNames.end();i_nName++)
		{
		constructPoset(*i_nName);
		}
	}

bayesian_factory::~bayesian_factory(void)
	{
	}

void bayesian_factory::constructPoset(string nName)
	{
	map<string, pair<bool, Sign>>*  state = new map<string, pair<bool, Sign>>();
	posets[nName] = poset_type();
	list<string> parentNames = list<string>();
	qpn->getParentNames(nName,parentNames);
	stateDefine(nName, parentNames.begin(), parentNames.end(), state);
	}

void bayesian_factory::stateDefine(string nName, list<string>::iterator begin, list<string>::iterator end, map<string, pair<bool, Sign>>* state)
	{
	if (begin != end)
		{
		(*state)[*begin] = make_pair(true, Sign::ZERO_SIGN);
		begin++;
		map<string, pair<bool, Sign>>* true_state = new map<string, pair<bool, Sign>>(*state);
		stateDefine(nName, begin,end, true_state);
		begin--;

		(*state)[*begin] = make_pair(false, Sign::ZERO_SIGN);
		begin++;
		map<string, pair<bool, Sign>>* false_state = new map<string, pair<bool, Sign>>(*state);
		stateDefine(nName, begin,end, false_state);
		begin--;

		}
	else
		{
		qpn->getParentsStatus(nName, *state);
		parents_sign_state<bool>* sign_state = new parents_sign_state<bool>(nName,state);
		posets[nName].addState(sign_state);
		}
	}


