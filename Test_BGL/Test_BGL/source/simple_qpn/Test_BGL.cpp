// Test_BGL.cpp : définit le point d'entrée pour l'application console.
//
  #include <iostream>                  // for std::cout
  #include <utility>                   // for std::pair
  #include <algorithm>                 // for std::for_each
  #include <boost/graph/graph_traits.hpp>
  #include <boost/graph/adjacency_list.hpp>
  #include <boost/graph/dijkstra_shortest_paths.hpp>
  #include <fstream> 
	#include "../../header/simple_qpn/Qpn_graph.h"


  using namespace boost;

int main(int,char*[])
{
std::ofstream outf =std::ofstream("net.gv");

	Qpn_graph qpn = Qpn_graph();
	qpn.addVertex("1");
	qpn.addVertex("2");
	qpn.addVertex("3");
	qpn.addVertex("4");
	qpn.addVertex("5");
	qpn.addInfluence("1","2", Sign::PLUS_SIGN);
	qpn.addInfluence("1","3", Sign::MINUS_SIGN);
	qpn.addInfluence("2","4", Sign::PLUS_SIGN);
	qpn.addInfluence("5","2", Sign::MINUS_SIGN);
	qpn.addInfluence("3","4", Sign::MINUS_SIGN);
	std::map<int,Sign> signMap = std::map<int,Sign>();
	signMap[0] = Sign::MINUS_SIGN;
	signMap[1] = Sign::PLUS_SIGN;
	qpn.addIntercausalLink("2","3","4",signMap);
	//qpn.observeVertexValue("4", 0);
		
	qpn.observeVertexVariation("5",Sign::MINUS_SIGN);
	qpn.writeGraphViz(outf);


    
}

