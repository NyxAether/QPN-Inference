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
		void findLowerSets(std::vector<std::vector<parents_sign_state<NodeValue>*>>& lowerSets );


	protected:
		void insert_as_child(Vertex new_v, Vertex current, std::set<Vertex>& seen);
		void insert_as_parent(Vertex new_v, Vertex current, std::set<Vertex>& seen);
		void desc_seen (Vertex current, std::set<Vertex>& seen);
		void ancestor_seen (Vertex current, std::set<Vertex>& seen);

		bool isAntichain(Vertex v, const std::set<Vertex> antichain);

		void computeLowerSet(std::set<Vertex> antichain,std::set<Vertex>& lowerSet);
		void getPartialLS(Vertex v, std::set<Vertex>& lowerSet);

		void findAntiChains(std::set<std::set<Vertex>>& antichains);

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
				//A new edge is inserted
				insert_as_child(v,*v_it,seen);
				ancestor_seen(*v_it,seen);
				break;
				}
			case -1:
				{
				insert_as_parent(v,*v_it,seen);
				desc_seen(*v_it,seen);
				break;
				}
				}

			}
		}
	}


template <typename NodeValue>
void poset_forest<NodeValue>::findLowerSets(std::vector<std::vector<parents_sign_state<NodeValue>*>>& lowerSets)
	{
	std::set<std::set<Vertex>> antichains = std::set<std::set<Vertex>>();
	findAntiChains(antichains);
	for (auto i_achain = antichains.begin();i_achain!=antichains.end();i_achain++)
		{
		std::set<Vertex> vertexLowerSet = std::set<Vertex>();
		computeLowerSet(*i_achain, vertexLowerSet);
		std::vector<parents_sign_state<NodeValue>*> lowerSet =std::vector<parents_sign_state<NodeValue>*>();
		for (auto i_v = vertexLowerSet.begin(); i_v!=vertexLowerSet.end();i_v++)
			{
			lowerSet.push_back(poset[*i_v]);
			}
		lowerSets.push_back(lowerSet);
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
				//All the nodes that weren't explored need to be set to seen
				//in this case the children of the current node
				ancestor_seen(next_v,seen);
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
				//All the nodes that weren't explored need to be set to seen
				//in this case the parents of the current node
				desc_seen(next_v,seen);
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


template <typename NodeValue>
void poset_forest<NodeValue>::desc_seen(Vertex current, std::set<Vertex>& seen)
	{
	OutEIterator out_it, end_out_it;
	for (boost::tie(out_it,end_out_it) = boost::out_edges(current, poset); out_it!=end_out_it;out_it++)
		{
		Vertex next_v= boost::target(*out_it,poset);
		if (seen.count(next_v)==0){
			seen.insert(next_v);
			desc_seen(next_v,seen);
			}
		}
	}


template <typename NodeValue>
void poset_forest<NodeValue>::ancestor_seen(Vertex current, std::set<Vertex>& seen)
	{
	InEIterator in_it, end_in_it;
	for (boost::tie(in_it,end_in_it) = boost::in_edges(current, poset); in_it!=end_in_it;in_it++)
		{
		Vertex next_v= boost::source(*in_it,poset);
		if (seen.count(next_v)==0){
			seen.insert(next_v);
			ancestor_seen(next_v,seen);
			}
		}
	}


template <typename NodeValue>
bool poset_forest<NodeValue>::isAntichain(Vertex v, std::set<Vertex> antichain)
	{
	for (auto i_v = antichain.begin();i_v!=antichain.end();i_v++)
		{
		int comp_val =poset[v]->compare(*(poset[*i_v]));
		if(comp_val == 0 || comp_val==-1 ||comp_val ==1)
			return false;
		}
	return true;
	}



template <typename NodeValue>
void poset_forest<NodeValue>::computeLowerSet(std::set<Vertex> antichain,std::set<Vertex>& lowerSet)
	{
	for (auto i_v = antichain.begin(); i_v!=antichain.end(); i_v++)
		{
		getPartialLS(*i_v,lowerSet);
		}
	}


template <typename NodeValue>
void poset_forest<NodeValue>::getPartialLS(Vertex v, std::set<Vertex>& lowerSet)
	{
	if (lowerSet.count(v) == 0)
		{
		lowerSet.insert(v);
		OutEIterator out_it, end_out_it;
		for (boost::tie(out_it,end_out_it) = boost::out_edges(v, poset); out_it!=end_out_it;out_it++)
			{
			Vertex next_v= boost::target(*out_it,poset);
			getPartialLS(next_v, lowerSet);
			}
		}
	}


template <typename NodeValue>
void poset_forest<NodeValue>::findAntiChains(std::set<std::set<Vertex>>& antichains)
	{
	VIterator v_it, v_end;
	//We build antichains by iteration. For each node
	for (boost::tie(v_it,v_end)=boost::vertices(poset);(v_it!=v_end);v_it++)
		{
				std::cout<<"coucou"<<std::endl;
		//we look into all antichain to figure if we can find a new antichain composed with this node and this antichain 
		for (auto i_antichain = antichains.begin(); i_antichain!=antichains.end();i_antichain++)
			{
			//If a new antichain can be obtain
			if (isAntichain(*(v_it),*i_antichain))
				{
				//the current antichain is copied, vertex is added to it. The antichain created is added to the list of antichains 
				std::set<Vertex> new_achain =std::set<Vertex>(*i_antichain);
				new_achain.insert(*v_it);
				antichains.insert(new_achain);
				//antichains.push_back(new_achain);
				}
			}
		//Finally all nodes is an antichain by itself and need to be added
		std::set<Vertex> new_achain =std::set<Vertex>();
		new_achain.insert(*v_it);
		antichains.insert(new_achain);
		}
	}
