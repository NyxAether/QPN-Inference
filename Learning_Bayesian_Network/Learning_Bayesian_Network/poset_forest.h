#pragma once

#include <vector>
#include "boost\graph\adjacency_list.hpp"
#include <boost\rational.hpp>
#include "parents_sign_state.h"
#include "pilgrim\general\FrequencyCounter.h"

template <typename NodeValue>
class poset_forest
	{
	public:

		typedef typename std::vector<parents_sign_state<NodeValue>*> lower_set_type;

		struct VertexProperties 
			{
			VertexProperties():states(std::vector<parents_sign_state<NodeValue>*>())
				{}
			std::vector<parents_sign_state<NodeValue>*> states;
			};



		//Defining the graph type used for QPN instantiation
		typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, VertexProperties, boost::no_property> poset_type;
		typedef typename boost::graph_traits<poset_type>::vertex_descriptor Vertex;

		//Defining vertex and edge iterators
		typedef typename boost::graph_traits<poset_type>::vertex_iterator VIterator;
		typedef typename boost::graph_traits<poset_type>::edge_iterator EIterator;
		typedef typename boost::graph_traits<poset_type>::in_edge_iterator InEIterator;
		typedef typename boost::graph_traits<poset_type>::out_edge_iterator OutEIterator;

		poset_forest(std::string nodeName);
		poset_forest(void);
		~poset_forest(void);

		void addState(parents_sign_state<NodeValue>* state);
		void findLowerSets(std::vector<lower_set_type>& lowerSets );
		plProbValue* MLS(PILGRIM::pmFrequencyCounter<plCSVFileDataDescriptor<int>::CSVDescRowDataType>& fc);		 

	protected:


		void insert_as_child(Vertex new_v, Vertex current, std::set<Vertex>& seen);
		void insert_as_parent(Vertex new_v, Vertex current, std::set<Vertex>& seen);
		void desc_seen (Vertex current, std::set<Vertex>& seen);
		void ancestor_seen (Vertex current, std::set<Vertex>& seen);

		bool isAntichain(Vertex v, const std::set<Vertex> antichain);

		void computeLowerSet(std::set<Vertex> antichain,std::set<Vertex>& lowerSet);
		void getPartialLS(Vertex v, std::set<Vertex>& lowerSet);

		void findAntiChains(std::set<std::set<Vertex>>& antichains);

	private:
		boost::rational<int> getRationalFromState(parents_sign_state<NodeValue>* state, std::vector<plFloat>& freq, std::map<std::string, unsigned int>& pos);
		boost::rational<int> computeLowerSetProb(lower_set_type& ls, std::map<parents_sign_state<NodeValue>*,boost::rational<int>>& probTable);
		void constructProbTable(std::map<parents_sign_state<NodeValue>*, boost::rational<int>>& rationalProb, std::map<std::string, unsigned int>& posstd::vector<plProbValue> probTable );

	protected:
		std::string nName;
		std::vector<std::string> parentNames;
		std::vector<parents_sign_state<NodeValue>*> all_states;
		poset_type poset;
	};

template <typename NodeValue>
poset_forest<NodeValue>::poset_forest(void):poset(poset_type()),all_states(std::vector<parents_sign_state<NodeValue>*>()), nName(""), parentNames(std::vector<std::string>())
	{

	}

template <typename NodeValue>
poset_forest<NodeValue>::poset_forest(std::string nodeName): poset(poset_type()),all_states(std::vector<parents_sign_state<NodeValue>*>()), nName(nodeName)
	{

	}


template <typename NodeValue>
poset_forest<NodeValue>::~poset_forest(void)
	{
	VIterator v_it, v_end;
	for (boost::tie(v_it,v_end)=boost::vertices(poset);v_it!=v_end;v_it++)
		{
		lower_set_type states = poset[*v_it].states;
		for (auto i_state = states.begin(); i_state!=states.end(); i_state++)
			{
			delete(*i_state);
			}

		}
	}


template <typename NodeValue>
void poset_forest<NodeValue>::addState(parents_sign_state<NodeValue>* state)
	{
	//First we add the new state to list of all states
	all_states.push_back(state);
	//Adds informations about the poset
	if(nName.empty())
		nName= state->getNode();
	if(parentNames.size() == 0)
		state->getParents(parentNames);
	//seen's purpose is to stop the algorithm anytime an node as been seen previously
	//If, during the algorithm insert_as_child, a node is seen but 
	//is incomparable this node stay incomparable in the insert_as_parent algorithm and reciprocally 
	VIterator v_it, v_end;
	//We first need to assert that a state is not equal to an existing
	for (boost::tie(v_it,v_end)=boost::vertices(poset);(v_it!=v_end);v_it++)
		{
		parents_sign_state<NodeValue>* current_state = poset[*v_it].states.front();
		if (state->compare(*current_state)==0)
			{				
			poset[*v_it].states.push_back(state);
			return;//An equal state has been found so the new_state is added and the algorithm stop
			}
		}
	//If no equal state was found, we add the new state as a new element of the graph then we search an existing order between
	//this state and the others
	std::set<Vertex> seen= std::set<Vertex> ();
	Vertex v = boost::add_vertex( poset);
	poset[v].states.push_back(state);
	seen.insert(v);
	for (boost::tie(v_it,v_end)=boost::vertices(poset);(v_it!=v_end);v_it++)
		{
		if(seen.count(*v_it)==0)
			{
			seen.insert(*v_it);
			parents_sign_state<NodeValue>* current_state = poset[*v_it].states.front();
			switch(state->compare(*current_state))//TODO no zero case ?
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
void poset_forest<NodeValue>::findLowerSets(std::vector<lower_set_type>& lowerSets)
	{
	std::set<std::set<Vertex>> antichains = std::set<std::set<Vertex>>();
	//Lower sets are obtained from its associate antichains
	findAntiChains(antichains);
	for (auto i_achain = antichains.begin();i_achain!=antichains.end();i_achain++)
		{
		//For each antichains we compute the associate lower set
		std::set<Vertex> vertexLowerSet = std::set<Vertex>();
		computeLowerSet(*i_achain, vertexLowerSet);
		std::vector<parents_sign_state<NodeValue>*> lowerSet =std::vector<parents_sign_state<NodeValue>*>();
		for (auto i_v = vertexLowerSet.begin(); i_v!=vertexLowerSet.end();i_v++)
			{
			lower_set_type states = poset[*i_v].states;
			for (auto i_state = states.begin(); i_state!= states.end(); i_state++)
				{
				lowerSet.push_back(*i_state);
				}

			}
		lowerSets.push_back(lowerSet);
		}
	}



template <typename NodeValue>
plProbValue* poset_forest<NodeValue>::MLS(PILGRIM::pmFrequencyCounter<plCSVFileDataDescriptor<int>::CSVDescRowDataType>& fc)
	{
	/************************************************************************/
	/* Initialisation                                                       */
	/************************************************************************/
	std::vector<lower_set_type> lowerSets = std::vector<lower_set_type>();
	findLowerSets(lowerSets);
	std::map<parents_sign_state<NodeValue>*, boost::rational<int>> probTable =std::map<parents_sign_state<NodeValue>*, boost::rational<int>>();
	//Gets Variables
	plVariablesConjunction variables =  fc.getVariables();
	//Initializes variable's positions
	std::vector<unsigned int> pos =std::vector<unsigned int>();
	std::map<std::string, unsigned int> relative_pos =std::map<std::string, unsigned int>();
	for(auto i_parent=parentNames.begin();i_parent!=parentNames.end();i_parent++)
		{
		unsigned int pos_parent =variables.get_symbol_position(variables.get_symbol_with_name(*i_parent));
		pos.push_back(pos_parent);
		unsigned int relative= 0;
		for (auto i_pos_r= relative_pos.begin();i_pos_r!=relative_pos.end();i_pos_r++)
			{
			unsigned int current_pos = variables.get_symbol_position(variables.get_symbol_with_name((*i_pos_r).first)) ;
			if(pos_parent < current_pos )
				relative_pos[(*i_pos_r).first]++;
			else
				relative++;
			}
		relative_pos[*i_parent]= relative;
		}


	std::vector<plFloat> freq =std::vector<plFloat>();

	/************************************************************************/
	/*First step : Constructs the table value from the data                 */
	/************************************************************************/
	//Compute frequencies
	fc.frequencyCount(pos, freq);
	for (auto i_state = all_states.begin(); i_state!=all_states.end();i_state++)
		{
		probTable[*i_state] = getRationalFromState(*i_state, freq, relative_pos);
		}


	/************************************************************************/
	/* Second step : MLS Algorithm                                          */
	/************************************************************************/
	while(!lowerSets.empty())
		{
		boost::rational<int> min_r;
		boost::rational<int> min(1,1);
		int index_min =0;
		//Searching minimal
		for(unsigned int i = 0 ; i< lowerSets.size();i++)
			{
			min_r = computeLowerSetProb(lowerSets[i], probTable);
			if(min_r < min)
				{
				min = min_r;
				index_min = i;
				}
			}
		lower_set_type min_ls = lowerSets[index_min];
		//Change probTable
		for (auto i_state = min_ls.begin(); i_state!=min_ls.end();i_state++)
			{
			probTable[*i_state]=min_r;
			}
		//Remove minimal from lowerSets and other
		lowerSets.erase(lowerSets.begin()+index_min);
		for (auto i_ls = lowerSets.begin(); i_ls!=lowerSets.end();i_ls++)
			{

			for (auto i_min_state= min_ls.begin();i_min_state!=min_ls.end();i_min_state++)
				{
				for (auto i_state= i_ls->begin();i_state!=i_ls->end();i_state++)
					{
					if ((*i_min_state) == (*i_state) )
						{
						i_ls->erase(i_state);
						i_state--;
						}		
					}
				}
			if(i_ls->empty())
				{
				lowerSets.erase(i_ls);
				i_ls--;
				}
			}
		}
	/************************************************************************/
	/* Third step : Constructs a plProbValue[]                              */
	/************************************************************************/

	}



template <typename NodeValue>
boost::rational<int> poset_forest<NodeValue>::getRationalFromState(parents_sign_state<NodeValue>* state, std::vector<plFloat>& freq, std::map<std::string, unsigned int>& pos)
	{
	unsigned int neg_val = 0;
	unsigned int  pos_val;
	for (auto i_parent = parentNames.begin();i_parent!=parentNames.end();i_parent++)
		{
		neg_val += state->getState(*i_parent).first *((unsigned int) std::pow(2.0,(int)pos[*i_parent]));
		}
	pos_val = neg_val + ((unsigned int) std::pow(2.0,(int)pos[nName]));
	return boost::rational<int>((int) freq[pos_val], (int)freq[pos_val+neg_val]);
	}


template <typename NodeValue>
boost::rational<int> poset_forest<NodeValue>::computeLowerSetProb(lower_set_type& ls, std::map<parents_sign_state<NodeValue>*,boost::rational<int>>& probTable)
	{
	int num, denum;
	num =0;
	denum = 0;
	for (auto i_state= ls.begin(); i_state!=ls.end();i_state++)
		{
		boost::rational<int> frac = probTable[*i_state];
		num += frac.numerator();
		denum += frac.denominator();
		}
	return boost::rational<int>(num, denum);
	}



template <typename NodeValue>
void poset_forest<NodeValue>::constructProbTable(std::map<parents_sign_state<NodeValue>*, boost::rational<int>>& rationalProb, std::map<std::string, unsigned int>& pos, std::vector<plProbValue>& probTable)
	{
		probTable = std::vector<plProbValue>(rationalProb.size());
		for (auto i_rprob= rationalProb.begin();i_rprob!=rationalProb.end();i++)
		{
		int index =0;
		for (auto i_parent = parentNames.begin();i_parent!=parentNames.end();i_parent++)
			{
			index += state->getState(*i_parent).first *((unsigned int) std::pow(2.0,(int)pos[*i_parent]));//DKLHFKLMSDFJKLSDJFK
			error;
			}
		}
	}


template <typename NodeValue>
void poset_forest<NodeValue>::insert_as_child(Vertex new_v, Vertex current, std::set<Vertex>& seen)
	{
	OutEIterator out_it, end_out_it;
	parents_sign_state<NodeValue>* new_state = poset[new_v].states.front();
	bool inserted = false;
	for (boost::tie(out_it,end_out_it) = boost::out_edges(current, poset); out_it!=end_out_it;out_it++)
		{
		Vertex next_v= boost::target(*out_it,poset);
		if (seen.count(next_v)==0)
			{
			parents_sign_state<NodeValue>* next_state = poset[next_v].states.front();

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
	parents_sign_state<NodeValue>* new_state = poset[new_v].states.front();
	bool inserted = false;
	for (boost::tie(in_it,end_in_it) = boost::in_edges(current, poset); in_it!=end_in_it; in_it++)
		{
		Vertex next_v= boost::source(*in_it,poset);
		if (seen.count(next_v)==0)
			{
			seen.insert(next_v);
			parents_sign_state<NodeValue>* next_state = poset[next_v].states.front();

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
		int comp_val =poset[v].states.front()->compare(*(poset[*i_v].states.front()));
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
