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
 //   // create a typedef for the Graph type
 //   typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;

 //   // Make convenient labels for the vertices
 //   enum { A, B, C, D, E, N };
 //   const int num_vertices = N;
 //   const char* name = "ABCDE";

 //   // writing out the edges in the graph
 //   typedef std::pair<int, int> Edge;
 //   Edge edge_array[] = 
 //   { Edge(A,B), Edge(A,D), Edge(C,A), Edge(D,C),
 //     Edge(C,E), Edge(B,D), Edge(D,E) };
 //   const int num_edges = sizeof(edge_array)/sizeof(edge_array[0]);

 //   // declare a graph object
 //   Graph g(num_vertices);

 //   // add the edges to the graph object
 //   for (int i = 0; i < num_edges; ++i)
 //     add_edge(edge_array[i].first, edge_array[i].second, g);

	//// get the property map for vertex indices
 //   typedef property_map<Graph, vertex_index_t>::type IndexMap;
 //   IndexMap index = get(vertex_index, g);

 //   std::cout << "vertices(g) = ";
 //   typedef graph_traits<Graph>::vertex_iterator vertex_iter;
 //   std::pair<vertex_iter, vertex_iter> vp;
 //   for (vp = vertices(g); vp.first != vp.second; ++vp.first)
 //     std::cout << index[*vp.first] <<  " ";
 //   std::cout << std::endl;

    
}

