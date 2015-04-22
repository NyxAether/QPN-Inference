#include "bayesian_factory.h"



using namespace std;
using namespace PILGRIM;

bayesian_factory::bayesian_factory(meta_qpn_controller* controller):qpn(controller),posets(posets_type()),data(data_type()),symbols(symbols_type()), values(values_type())
	{
	list<string> nNames= list<string>();
	controller->getNodeNames(nNames);
	//Define the symbols
	for (auto i_nName = nNames.cbegin(); i_nName!=nNames.cend();i_nName++)
		{

		symbols[*i_nName]= plSymbol(*i_nName, PL_BINARY_TYPE);
		}
	//Construct the posets
	for (auto i_nName = nNames.begin(); i_nName!=nNames.end();i_nName++)
		{
		constructPoset(*i_nName);
		}
	}

bayesian_factory::~bayesian_factory(void)
	{
	for (auto i_data = data.begin(); i_data!=data.end();i_data++)
		{
		//Destruct the data descriptor stores into the pmFrequencyCounter
		delete(i_data->second->getDataDescriptor());
		//Destruct the pmFrequencyCounter
		delete(i_data->second);
		}
	}

void bayesian_factory::constructPoset(string nName)
	{
	map<string, pair<bool, Sign>>*  state = new map<string, pair<bool, Sign>>();
	posets[nName] = poset_type();
	vector<string> parentNames = vector<string>();
	qpn->getParentNames(nName,parentNames);
	stateDefine(nName, parentNames.begin(), parentNames.end(), state);
	}

void bayesian_factory::stateDefine(string nName, vector<string>::iterator begin, vector<string>::iterator end, map<string, pair<bool, Sign>>* state)
	{
	if (begin != end)
		{
		//For each parent two state are created. One for each values possible.
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
		//When all parents have been seen, a complete state is define and is had to the poset associate to the child
		qpn->getParentsStatus(nName, *state);
		parents_sign_state<bool>* sign_state = new parents_sign_state<bool>(nName,state);
		posets[nName].addState(sign_state);
		}
	}

void bayesian_factory::addData(string nName, string filePath)
	{
	vector<string> pNames = vector<string>();
	qpn->getParentNames(nName, pNames);
	plVariablesConjunction variables = plVariablesConjunction();

	setHeaders(variables,filePath);

	plCSVFileDataDescriptor<int>* ds =new plCSVFileDataDescriptor<int>(filePath, variables, true, ';');
	pmFrequencyCounter<plCSVFileDataDescriptor<int>::CSVDescRowDataType>* fc= new	pmFrequencyCounter<plCSVFileDataDescriptor<int>::CSVDescRowDataType>(ds, variables);
	data[nName]=fc;

	}

void bayesian_factory::build()
	{
	list<string> nNames = list<string>();
	qpn->getNodeNames(nNames);
	for (auto i_name = nNames.begin(); i_name!=nNames.end();i_name++)
		{
		
		}
	}

void bayesian_factory::setHeaders(plVariablesConjunction& variables, std::string filename)
	{
	ifstream file(filename, ios::in);  

	if(file)  
		{
		string line,name_var;  
		getline(file, line);  
		 istringstream toSplit(line);
		while (getline(toSplit, name_var, ';')) 
			variables = variables ^ symbols[name_var];
		file.close();
		}
	else
		cerr << "Cannot read the specified file" << endl;
	}

void bayesian_factory::computeProbTable(string nName, vector<plProbValue> & values)
	{

	}

//parents_sign_state<bool> bayesian_factory::createPSSFromRow(string nName, plCSVFileDataDescriptor<int>::CSVDescRowDataType& row)
//	{
//	list<string> pNames = list<string>();
//	qpn->getParentNames(nName, pNames);
//	for (auto i_nName = pNames.begin(); i_nName!=pNames.end();i_nName++)
//		{
//
//		}
//	//parents_sign_state<bool> pss = parents_sign_state<bool>(nName);
//	}


