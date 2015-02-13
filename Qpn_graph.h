#pragma once
#include <map>

#include "boost\graph\adjacency_list.hpp"
#include "boost\graph\labeled_graph.hpp"
#include "boost\property_map\property_map.hpp"
#include "qpn_vertex.h"
#include "qpn_edge.h"
#include "intercausal_link.h"

class Qpn_graph 
	{
	public:
		/////////////
		// TYPEDEF //
		/////////////

		//typedef boost::property<boost::vertex_name_t, std::string> VertexProperty;
		//typedef boost::property<boost::edge_name_t, std::string> EdgeProperty;

		//Defining the graph type used for QPN instantiation
		typedef boost::labeled_graph<
			boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, qpn_vertex, qpn_edge>,
			std::string> QPN_INFLUENCE;
		typedef boost::labeled_graph<
			boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, qpn_vertex, intercausal_link>,
			std::string> QPN_SYNERGY;

		//Defining vertices and edges for the graph
		typedef boost::graph_traits<QPN_INFLUENCE>::vertex_descriptor Vertex;
		typedef boost::graph_traits<QPN_SYNERGY>::vertex_descriptor VertexSyn;
		typedef boost::graph_traits<QPN_INFLUENCE>::edge_descriptor Influence;
		typedef boost::graph_traits<QPN_SYNERGY>::edge_descriptor Synergy;

		//Defining iterators
		typedef boost::graph_traits<QPN_INFLUENCE>::vertex_iterator vertex_iterator;
		typedef boost::graph_traits<QPN_INFLUENCE>::edge_iterator influence_iterator;
		typedef boost::graph_traits<QPN_SYNERGY>::edge_iterator synergy_iterator;
		typedef boost::graph_traits<QPN_INFLUENCE>::out_edge_iterator out_influence_iterator;
		typedef boost::graph_traits<QPN_INFLUENCE>::in_edge_iterator in_influence_iterator;

		//Property map types
		//typedef boost::property_map<QPN_INFLUENCE, boost::vertex_name_t>::type VNameMap;
		//typedef boost::property_map<QPN_INFLUENCE, boost::vertex_color_t>::type color_map_t;
		/////////////////
		// END TYPEDEF //
		/////////////////

		Qpn_graph(void);
		~Qpn_graph(void);

		/////
		//Graph construction methods
		/////
		void addVertex(std::string name); 

		void addInfluence(std::string from, std::string to, const Sign& sign);

		void addIntercausalLink(std::string v1, std::string v2, std::string linked_v, std::map<int, Sign>& signMap);

		void observeVertexValue(std::string vName, int value);

		void observeVertexVariation(std::string vName, Sign sign);//Lauch inference 

		/////
		//GraphViz
		/////
		void writeGraphViz(std::ostream& out);

	protected:
		/////
		//Inference algorithm
		/////
		void propagateSign(std::string vName, std::map<std::string, bool> colorMap, bool fromChild);

		/////
		//Information retrieving methods
		/////
		template <typename Graph>
		bool existV(std::string vName, Graph& g);

		void findNeighbours(std::string& vName,   std::map<std::string, bool>& colorMap, bool fromChild, std::list<Influence>& activesInfluences, std::list<Synergy>& activesSynergies);

		template<typename G,typename E, typename IteratorType>
		void findTargetsByEdgeType(std::string& vName, G& qpn,  std::map<std::string, bool>& colorMap, std::pair<IteratorType,IteratorType> iters,  std::list<E>& activesEdges);
		template<typename G,typename E, typename IteratorType>
		void findSourcesByEdgeType(std::string& vName, G& qpn,  std::map<std::string, bool>& colorMap, std::pair<IteratorType,IteratorType> iters,  std::list<E>& activesEdges);

		bool hasObservedDescendant(Vertex& v);

		bool hasObservedDescendant(Vertex& v, std::map<Vertex, bool>& colorMap);

		template <typename G, typename V>
		std::string getVName(V& v, G& g);



	private:
		QPN_INFLUENCE qpn_influence;
		QPN_SYNERGY qpn_synergy;


		//std::map<Vertex, qpn_vertex*> vMap;
		//std::map<Edge, qpn_edge> eMap;
		//VNameMap vNames;
		//VSignMap vSigns;
		//VValueMap vValues ;
		//ESignMap eSigns;
	};



