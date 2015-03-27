#pragma once
#include "..\..\Meta_QPN\Meta_QPN\parents_sign_state.h"
#include <vector>
#include "boost\graph\adjacency_list.hpp"

template <typename NodeValue>
class poset_forest
	{
	public:

		struct VertexProperties
			{
			parents_sign_state state;
			};

		//Defining the graph type used for QPN instantiation
		typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, parents_sign_state<NodeValue>*, boost::no_property> poset_type;
		typedef typename boost::graph_traits<poset_type>::vertex_descriptor Vertex;

		//Defining vertex and edge iterators
		typedef typename boost::graph_traits<poset_type>::vertex_iterator VIterator;
		typedef typename boost::graph_traits<poset_type>::edge_iterator EIterator;
		typedef typename boost::graph_traits<poset_type>::in_edge_iterator InEIterator;
		typedef typename boost::graph_traits<poset_type>::out_edge_iterator OutEIterator;

		poset_forest(void);
		~poset_forest(void);

		void addState(parents_sign_state<NodeValue>* state);

	protected:
		void insert_as_child(Vertex new_v, Vertex current, std::set<Vertex>& seen);
		void insert_as_parent(Vertex new_v, Vertex current, std::set<Vertex>& seen);

	protected:
		std::vector<parents_sign_state<NodeValue>> states;
		poset_type poset;
	};

template <typename NodeValue>
poset_forest<NodeValue>::poset_forest(void):states(std::vector<parents_sign_state<NodeValue>>()), poset(poset_type())
	{

	}


template <typename NodeValue>
poset_forest<NodeValue>::~poset_forest(void)
	{
	VIterator v_it, v_end;
	for (boost::tie(v_it,v_end)=boost::vertices(poset);v_it!=v_end;v_it++)
		{
		delete(poset[*v_it]);
		}
	}


template <typename NodeValue>
void poset_forest<NodeValue>::addState(parents_sign_state<NodeValue>* state)
	{
	//seen's purpose is to stop the algorithm anytime an node as been seen previously
	//If, during the algorithm insert_as_child, a node is seen but 
	//is incomparable this node stay incomparable in the insert_as_parent algorithm and reciprocally 
	std::set<Vertex> seen= std::set<Vertex> ();
	Vertex v = boost::add_vertex(state, poset);
	seen.insert(v);
	VIterator v_it, v_end;
	for (boost::tie(v_it,v_end)=boost::vertices(poset);(v_it!=v_end);v_it++)
		{
		if(seen.count(*v_it)==0)
			{
			seen.insert(*v_it);
			parents_sign_state<NodeValue>* current_state = poset[*v_it];
			switch(state->compare(*current_state))
				{
			case 1:
				{
				insert_as_child(v,*v_it,seen);
				break;
				}
			case -1:
				{
				insert_as_parent(v,*v_it,seen);
				break;
				}
				}

			}
		}
	}

template <typename NodeValue>
void poset_forest<NodeValue>::insert_as_child(Vertex new_v, Vertex current, std::set<Vertex>& seen)
	{
	OutEIterator out_it, end_out_it;
	parents_sign_state<NodeValue>* new_state = poset[new_v];
	bool inserted = false;
	for (boost::tie(out_it,end_out_it) = boost::out_edges(current, poset); out_it!=end_out_it;out_it++)
		{
		Vertex next_v= boost::target(*out_it,poset);
		if (seen.count(next_v)==0)
			{
			parents_sign_state<NodeValue>* next_state = poset[next_v];

			int diff = next_state->compare(*new_state);
			if(diff == 1){
				insert_as_child(new_v, next_v,seen);
				inserted= true;
				}
			else if(diff == -1)
				{
				boost::remove_edge(current, next_v,poset);
				boost::add_edge(current,new_v,poset);
				boost::add_edge(new_v,next_v, poset);
				inserted =true;
				}
			}
		}
	if (!inserted)
		{
		boost::add_edge(current,new_v, poset);
		}
	}

template <typename NodeValue>
void poset_forest<NodeValue>::insert_as_parent(Vertex new_v, Vertex current, std::set<Vertex>& seen)
	{
	InEIterator in_it, end_in_it;
	parents_sign_state<NodeValue>* new_state = poset[new_v];
	bool inserted = false;
	for (boost::tie(in_it,end_in_it) = boost::in_edges(current, poset); in_it!=end_in_it; in_it++)
		{
		Vertex next_v= boost::source(*in_it,poset);
		if (seen.count(next_v)==0)
			{
			seen.insert(next_v);
			parents_sign_state<NodeValue>* next_state = poset[next_v];

			int diff = next_state->compare(*new_state);
			if(diff == -1){
				insert_as_parent(new_v, next_v,seen);
				inserted= true;
				}
			else if(diff == 1)
				{
				boost::remove_edge(next_v , current , poset);
				boost::add_edge(new_v ,current, poset);
				boost::add_edge(next_v, new_v, poset);
				inserted =true;
				}
			}
		}
	if (!inserted)
		{
		boost::add_edge(new_v,current, poset);
		}
	}


