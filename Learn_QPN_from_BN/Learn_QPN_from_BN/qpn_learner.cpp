#include "StdAfx.h"
#include "qpn_learner.h"

using namespace std;
using namespace PILGRIM;

qpn_learner::qpn_learner(void)
	{
	}

qpn_learner::qpn_learner(pmBayesianNetwork* bayesNet): bn(bayesNet)
	{

	}


qpn_learner::~qpn_learner(void)
	{
	}

meta_qpn_controller qpn_learner::learn()
	{
	pmGraph bn_graph = bn->get_graph();
	pmNodeIterator i_node, i_node_end;
	boost::tie(i_node,i_node_end) = vertices(bn_graph);
	for (;i_node!=i_node_end;i_node++)
	{
	bn->summary();
	vector<plProbValue> probs = vector<plProbValue>();
	plComputableObject* table = bn->getComputableObject(*i_node);
	table->tabulate(probs);
	plVariablesConjunction children = bn->getParents(*i_node);
	}

	return meta_qpn_controller();
	}
