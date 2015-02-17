#pragma once
#include <map>

#include "boost\graph\adjacency_list.hpp"
#include "boost\graph\labeled_graph.hpp"
#include "boost\property_map\property_map.hpp"
#include "../../header/simple_qpn/qpn_vertex.h"
#include "../../header/simple_qpn/qpn_edge.h"
#include "../../header/simple_qpn/intercausal_link.h"

/**********************************************************************************************//**
\class	Qpn_graph qpn_graph.h qpn_graph.h

\brief	A simple QPN graph with influence and product synergy.

\author	Romain RINCE
\date	16/02/2015
 **************************************************************************************************/

class Qpn_graph 
	{
	public:
		/////////////
		// TYPEDEF //
		/////////////

		//typedef boost::property<boost::vertex_bundle_t, std::string,boost::property<boost::vertex_name_t, std::string>> VertexProperty;
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



		/**********************************************************************************************//**
		\fn	void Qpn_graph::addVertex(std::string name);
		
		\brief	Add a new vertex into the graph.
		
		\author	Romain RINCE
		\date	16/02/2015
		
		\param	name	The name of the new vertex
		 **************************************************************************************************/

		void addVertex(std::string name); 

		/**********************************************************************************************//**
		\fn	void Qpn_graph::addInfluence(std::string from, std::string to, const Sign& sign);
		
		\brief	Adds an influence into the graph. (oriented)
		
		\author	Romain RINCE
		\date	16/02/2015
		
		\param	from	Name of the source vertex of the edge
		\param	to  	Name of the target vertex of the edge
		\param	sign	The sign on the edge. Can be '+', '-', '0' or '?' for the different kind of influence
		 **************************************************************************************************/

		void addInfluence(std::string from, std::string to, const Sign& sign);

		/**********************************************************************************************//**
		\fn	void Qpn_graph::addIntercausalLink(std::string v1, std::string v2, std::string linked_v, std::map<int, Sign>& signMap);
		
		\brief	Adds an intercausal link. (non-oriented)
		
		\author	Romain RINCE
		\date	16/02/2015
		
		\param	v1			   	Name of one of the two node in relation.
		\param	v2			   	Name of one of the two node in relation.
		\param	linked_v	   	The name of a third node whose the sign value of the link depends on
		\param [in,out]	signMap	The sign map that define a sign for each value of the linked node.
		 **************************************************************************************************/

		void addIntercausalLink(std::string v1, std::string v2, std::string linked_v, std::map<int, Sign>& signMap);

		/**********************************************************************************************//**
		\fn	void Qpn_graph::observeVertexValue(std::string vName, int value);
		
		\brief	Fixed the value for an existing node. In this case, the sign is no longer important and will be ignore by all the algorithm.
		
		\author	Romain RINCE
		\date	16/02/2015
		
		\param	vName	The name of the observed vertex
		\param	value	The value of the observed vertex
		 **************************************************************************************************/

		void observeVertexValue(std::string vName, int value);

		/**********************************************************************************************//**
		\fn	void Qpn_graph::observeVertexVariation(std::string vName, Sign sign);
		
		\brief	For a consitent QPN, this method will set a variation on a vertex ('+' or '-') and will propagate this sign through the graph.
		
		\author	Romain RINCE
		\date	16/02/2015
		
		\param	vName	The name the vertex.
		\param	sign 	The sign variation observed on this node.
		 **************************************************************************************************/

		void observeVertexVariation(std::string vName, Sign sign);//Lauch inference 

		/**********************************************************************************************//**
		\fn	void Qpn_graph::writeGraphViz(std::ostream& out);
		
		\brief	Write on the output the graph in dot language.
		
		\author	Romain RINCE
		\date	16/02/2015
		
		\param [in,out]	out	The out.
		 **************************************************************************************************/

		void writeGraphViz(std::ostream& out);

	protected:

		/**********************************************************************************************//**
		\fn	void Qpn_graph::propagateSign(std::string vName, std::map<std::string, bool> colorMap, bool fromChild);
		
		\brief	Recursively propagate a sign from a node through the QPN
		
		\author	Romain RINCE
		\date	16/02/2015
		
		\param	vName	 	The name of the vertrex whose the sign has changed
		\param	colorMap 	Define the trail of the previously visited nodes. Assign a boolean for each node on the QPN set to true if it has been seen, false otherwise.
		\param	fromChild	Needed parameter defining if the state changing of the current node came from a parent(false) or a child(true) of this one. If it's the first node changed (after an observation of variation for instance) or if the information came from non oriented relation, this parameter has to be set to true.
		 **************************************************************************************************/

		void propagateSign(std::string vName, std::map<std::string, bool> colorMap, bool fromChild);

		/////
		//Information retrieving methods
		/////
		template <typename Graph>

		/**********************************************************************************************//**
		\fn	bool Qpn_graph::existV(std::string vName, Graph& g);
		
		\brief	return True if the node exist in the graph
		
		\author	Romain RINCE
		\date	16/02/2015
		
		\param	vName	 	The name of the vertex whose we want to know if it exists
		\param [in]	g	The graph in that we want to search
		
		\return	true if the node exists, false if not.
		 **************************************************************************************************/

		bool existV(std::string vName, Graph& g);

		/**********************************************************************************************//**
		\fn	void Qpn_graph::findNeighbours(std::string& vName, std::map<std::string, bool>& colorMap, bool fromChild, std::list<Influence>& activesInfluences, std::list<Synergy>& activesSynergies);
		
		\brief	For a vertex , find all the edges for which a message of a sign variation has to be sent. Those edges are saved in the two list provided in the parameters
		
		\author	Romain RINCE
		\date	16/02/2015
		
		\param [in]	vName			 	The name of the vertex whose the sign has changed
		\param [in]	colorMap		 	The trail that contains all the node previously explored.
		\param	fromChild				 	Define if the current sign of the node is resulting of a parent of this node, or a child. If it's the first node changed (after an observation of variation for instance) or if the information came from non oriented relation, this parameter has to be set to true.
		\param [out]	activesInfluences	Stores all of the active influences.
		\param [out]	activesSynergies 	Stores all of the active synergies
		 **************************************************************************************************/

		void findNeighbours(std::string& vName,   std::map<std::string, bool>& colorMap, bool fromChild, std::list<Influence>& activesInfluences, std::list<Synergy>& activesSynergies);

		template<typename G,typename E, typename IteratorType>
		void findTargetsByEdgeType(std::string& vName, G& qpn,  std::map<std::string, bool>& colorMap, std::pair<IteratorType,IteratorType> iters,  std::list<E>& activesEdges);
		template<typename G,typename E, typename IteratorType>
		void findSourcesByEdgeType(std::string& vName, G& qpn,  std::map<std::string, bool>& colorMap, std::pair<IteratorType,IteratorType> iters,  std::list<E>& activesEdges);

		/**********************************************************************************************//**
		\fn	bool Qpn_graph::hasObservedDescendant(Vertex& v);
		
		\brief	Search through the QPN if a vertex has an observed descendant
		
		\author	Romain RINCE
		\date	16/02/2015
		
		\param [in]	v	The Vertex whose we want to explore his descendants
		
		\return	true if observed descendant, false if not.
		 **************************************************************************************************/

		bool hasObservedDescendant(Vertex& v);

		/**********************************************************************************************//**
		\fn	bool Qpn_graph::hasObservedDescendant(Vertex& v, std::map<Vertex, bool>& colorMap);
		
		\brief	Search through the QPN if a vertex has an observed descendant
		
		\author	Romain RINCE
		\date	16/02/2015
		
		\param [in]	v			The Vertex whose we want to explore his descendants
		\param [in]	colorMap	The trails of the previously observed node.
		
		\return	true if observed descendant, false if not.
		 **************************************************************************************************/

		bool hasObservedDescendant(Vertex& v, std::map<Vertex, bool>& colorMap);

		template <typename G, typename V>

		/**********************************************************************************************//**
		\fn	std::string Qpn_graph::getVName(V& v, G& g);
		
		\brief	Gets name of a vertex from BGL vertex description
		
		\author	Romain RINCE
		\date	16/02/2015
		
		\param [in]	v	The vertex description
		\param [in]	g	The Graph containing the vertex.
		
		\return	The vertex name.
		 **************************************************************************************************/

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



