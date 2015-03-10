#include "meta_qpn_controller.h"



meta_qpn_controller::meta_qpn_controller(void):meta_qpn<bool>(),influences(qpn_influence<bool>()),product_synergies(qpn_product_synergy<bool>()),context_specifics(qpn_context_specific<bool>())
	{
	addQpn(&influences);
	addQpn(&product_synergies);
	addQpn(&context_specifics);
	}


meta_qpn_controller::~meta_qpn_controller(void)
	{
	}


void meta_qpn_controller::addInfluence(std::string from, std::string to, Sign sign)
	{
	if(!exists(from))
		addNode(from);
	if(!exists(to))
		addNode(to);
	qpn_edge_influence* edge = new qpn_edge_influence(sign);
	std::vector<std::string> v= std::vector<std::string>();
	v.push_back(from);
	v.push_back(to);
	influences.addEdge(edge,v);
	}



void meta_qpn_controller::addProductSynergy(std::string nName1, std::string nName2, std::string linked, Sign sign)
	{
	if(!exists(nName1))
		addNode(nName1);
	if(!exists(nName2))
		addNode(nName2);
	if(!exists(linked))
		addNode(linked);
	qpn_edge_product_synergy<bool>* edge= new qpn_edge_product_synergy<bool>(getNode(linked),sign);
	std::vector<std::string> v= std::vector<std::string>();
	v.push_back(nName1);
	v.push_back(nName2);
	product_synergies.addEdge(edge,v);
	}

void meta_qpn_controller::addProductSynergy(std::string nName1, std::string nName2, std::string linked, Sign trueS, Sign falseS)
	{
	if(!exists(nName1))
		addNode(nName1);
	if(!exists(nName2))
		addNode(nName2);
	if(!exists(linked))
		addNode(linked);

	qpn_edge_product_synergy<bool>* edge;
	if(trueS == falseS)
		edge= new qpn_edge_product_synergy<bool>(getNode(linked),trueS);
	else{
		std::map<bool, Sign> signMap = std::map<bool, Sign> ();
		signMap[true]= trueS;
		signMap[false]=falseS;
		edge= new qpn_edge_product_synergy<bool>(getNode(linked),signMap);
		}
	std::vector<std::string> v= std::vector<std::string>();
	v.push_back(nName1);
	v.push_back(nName2);
	product_synergies.addEdge(edge,v);
	}

void meta_qpn_controller::addContextSpecific(std::string from, std::string to, std::string file_path)
	{

	std::ifstream file = std::ifstream(file_path,std::ios::in);


	if(!exists(from))
		addNode(from);
	if(!exists(to))
		addNode(to);
	std::vector<std::string> v= std::vector<std::string>();
	v.push_back(from);
	v.push_back(to);

	std::list<qpn_node<bool>**> nodes_list =std::list<qpn_node<bool>**>();
	contexts_t contexts = contexts_t();
	constructCSStructure(file,nodes_list,contexts);
	qpn_edge_context_specific<bool>* edge = new qpn_edge_context_specific<bool>(nodes_list,contexts);
	context_specifics.addEdge(edge,v);
	}

void meta_qpn_controller::writeGraphViz(std::string file_path)
	{
	std::ostream& outf =std::ofstream(file_path);
	meta_qpn<bool>::writeGraphViz(outf);
	}

void meta_qpn_controller::constructCSStructure(std::ifstream& file, std::list<qpn_node<bool>**>& nodes_list, contexts_t& contexts)
	{
	std::string line;
	typedef std::vector<std::string> vec_string;
	boost::char_separator<char> semico_sep(";");
	boost::char_separator<char> ddot_sep(":");
	boost::char_separator<char> eq_sep("=");

	if(file)
		{     
		if(std::getline(file,line))
			{
			vec_string nNames;
			boost::split(nNames,line,boost::is_any_of(";"));
			for(auto i_nName=nNames.begin(); i_nName!= nNames.cend(); i_nName++){
				if(!exists(*i_nName))
					addNode(*i_nName);
				nodes_list.push_back(getNode(*i_nName));
				}
			while (std::getline(file,line))
				{
				if (line.size()!=0)
					{
					vec_string rule, c_nodes;
					boost::split(rule,line,boost::is_any_of("="));
					boost::split(c_nodes,rule[0],boost::is_any_of(";"));
					std::list<std::pair<std::string, bool>> context_list = std::list<std::pair<std::string, bool>>();
					for (auto i_node=c_nodes.begin(); i_node!=c_nodes.end();i_node++)
						{
						vec_string nValue;
						boost::split(nValue,*i_node,boost::is_any_of(":"));
						//make pair of node name with value
						try
							{
							bool valNode =boost::lexical_cast<bool>(nValue[1]);
							std::pair<std::string, bool> vContext = std::make_pair(nValue[0],valNode);
							context_list.push_back(vContext);
							}
						catch (...)
							{
							std::cerr<<"error file format ["<<nValue[0]<<"]"<<std::endl;
							}
						}
					Sign c_sign = Sign(rule[1][0]);
					contexts.push_back(std::make_pair(context_list, c_sign));
					}
				}
			}
		file.close(); 
		}
	else 
		std::cerr << " File has not be opened" << std::endl;

	}
