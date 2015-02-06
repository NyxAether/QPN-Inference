#pragma once

#include <iostream>
#include <string>

#include "c:\program files\boost\boost_1_57_0\boost\graph\adjacency_list.hpp"
#include "boost\graph\labeled_graph.hpp"
#include "boost\property_map\property_map.hpp"


////////////////////////
/// SIGNS DEFINTIONS ///
////////////////////////


//Sign definitions
typedef struct Sign Sign;
struct Sign
{
public:
	char c;
	Sign operator+( const  Sign & s);
	Sign operator*( const  Sign & s);
	bool operator==( const  Sign & s);
	bool operator!=( const  Sign & s);
	friend std::ostream& operator<< (std::ostream& os, const Sign& s);
};
/////////////////////
/// END DEFINTION ///
/////////////////////

/////////////////////////////
/// INFLUENCES DEFINITIONS///
/////////////////////////////

//Vertex properties definition
enum vertex_value_t {
	vertex_value
};
enum vertex_sign_t {
	vertex_sign
};
namespace boost
{
	BOOST_INSTALL_PROPERTY(vertex, value);
	BOOST_INSTALL_PROPERTY(vertex, sign);
}
typedef boost::property<boost::vertex_name_t, std::string> VName;
typedef boost::property<vertex_value_t, int, VName> VValue;
typedef boost::property<vertex_sign_t, Sign, VValue> VertexProperty;

//Edge properties definition
enum edge_sign_t {
	edge_sign
};
namespace boost
{
	BOOST_INSTALL_PROPERTY(edge, sign);
}


typedef boost::property<boost::edge_name_t, std::string> EName;
typedef boost::property<edge_sign_t, Sign, EName> EdgeProperty;


//Defining the graph type used for QPN instantiation
typedef boost::labeled_graph<
	boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, VertexProperty, EdgeProperty>,
	std::string> QPN_INFLUENCE;

//Defining vertices and edges for the graph
typedef boost::graph_traits<QPN_INFLUENCE>::vertex_descriptor Vertex;
typedef boost::graph_traits<QPN_INFLUENCE>::edge_descriptor Edge;

//Defining iterators
typedef boost::graph_traits<QPN_INFLUENCE>::vertex_iterator vertex_iterator;
typedef boost::graph_traits<QPN_INFLUENCE>::edge_iterator edge_iterator;
typedef boost::graph_traits<QPN_INFLUENCE>::out_edge_iterator out_edge_iterator;
typedef boost::graph_traits<QPN_INFLUENCE>::in_edge_iterator in_edge_iterator;

//Property map types
typedef boost::property_map<QPN_INFLUENCE, boost::vertex_name_t>::type VNameMap;
typedef boost::property_map<QPN_INFLUENCE, vertex_value_t>::type VValueMap;
typedef boost::property_map<QPN_INFLUENCE, vertex_sign_t>::type VSignMap;

typedef boost::property_map<QPN_INFLUENCE, boost::edge_name_t>::type ENameMap;
typedef boost::property_map<QPN_INFLUENCE, edge_sign_t>::type ESignMap;

/////////////////////
/// END DEFINTION ///
/////////////////////

/////////////////////////////
/// DEFINITIONS SYNEGRIES ///
/////////////////////////////

//Same vertex definition

//Defining edge synergy
enum edge_sum_synergy_t {
	edge_sum_synergy
};
namespace boost
{
	BOOST_INSTALL_PROPERTY(edge, sum_synergy);
}


//typedef boost::property<edge_sum_synergy, std::map<>> EName;
//typedef boost::property<edge_sign_t, Sign, EName> EdgeProperty;

/////////////////////
/// END DEFINTION ///
/////////////////////
