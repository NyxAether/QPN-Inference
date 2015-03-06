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

void meta_qpn_controller::writeGraphViz(std::string file_path)
	{
	std::ostream& outf =std::ofstream(file_path);
	meta_qpn<bool>::writeGraphViz(outf);
	}
