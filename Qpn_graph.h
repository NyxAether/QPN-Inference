#pragma once
#include "qpn_properties.h"

class Qpn_graph 
{
public:




	Qpn_graph(void);
	~Qpn_graph(void);
	void addVertex(std::string name); 
	/*void addFixedVertex(std::string name, bool value); */
	void addInfluence(std::string from, std::string to, Sign sign);
	/*void addProductSynergy(std::string from, std::string to, std::string linkedNode, std::map<bool,Sign>& mapValue);*/
	void writeGraphViz(std::ostream& out);
	void observeVertexValue(std::string vName, int value);
	char signProduct(Sign s1, Sign s2);
	char signSum(Sign s1, Sign s2);
	bool existV(std::string vName);
protected:
	void propagateSign(Vertex& v, std::map<std::string, bool> colorMap, bool fromChild);
	void findNeighbours(Vertex &v,  std::map<std::string, bool> colorMap, bool fromChild, std::list<Edge>& neighbours);
	bool hasObservedDescendant(Vertex& v);
private:
	QPN_INFLUENCE qpn_influence;
	VNameMap vNames;
	VSignMap vSigns;
	VValueMap vValues ;
	ESignMap eSigns;
};

