#pragma once

#include <vector>
#include "boost\graph\adjacency_list.hpp"
#include "parents_sign_state.h"
#include "pilgrim\general\FrequencyCounter.h"
#include "strange_rational.h"

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

		/**
		* \brief add new state to the poset
		* \details In a poset, all states need to be on the same node. All parents of the node need to set on the state.
		* \param[in] state : A pointer on the state. Be cautious, if a poset is delete same is done for his states.
		*/
		void addState(parents_sign_state<NodeValue>* state);
		
		/**
		* \brief Find all the lower sets in the current poset
		* \details The number of lower sets can be huge. For instance, if the node associate to this poset has 5 parents this method can compute 7580 lower set. For 6 parents, it can compute over 7 000 000 lower sets.
		* \param[out] lowerSets : Will contain at the end of the method all the lower sets 
		*/
		void findLowerSets(std::vector<lower_set_type>& lowerSets );

		/**
		* \brief Minimum lower sets algorithm
		* \param[in] fc : a pointer on a FrequencyCounter associated to the data
		* \param[out] probs : At the end, contains the probability table for the node associate to the poset
		*/
		void MLS(PILGRIM::pmFrequencyCounter<plCSVFileDataDescriptor<int>::CSVDescRowDataType>* fc, std::vector<plProbValue>& probs);		 

	protected:


		void insert_as_child(Vertex new_v, Vertex current, std::set<Vertex>& seen);
		void insert_as_parent(Vertex new_v, Vertex current, std::set<Vertex>& seen);
		void desc_seen (Vertex current, std::set<Vertex>& seen);
		void ancestor_seen (Vertex current, std::set<Vertex>& seen);

		bool isAntichain(Vertex v, const std::set<Vertex> antichain);

		void computeLowerSet(std::set<Vertex> antichain,std::set<Vertex>& lowerSet);
		strange_rational getMinLowerSet(std::vector<lower_set_type>& lowerSets, std::map<parents_sign_state<NodeValue>*, strange_rational>& probTable, lower_set_type &min_ls );
		void getPartialLS(Vertex v, std::set<Vertex>& lowerSet);

		void findAntiChains(std::set<std::set<Vertex>>& antichains);

	private:
		strange_rational getRationalFromState(parents_sign_state<NodeValue>* state, std::vector<plFloat>& freq, std::map<std::string, unsigned int>& pos);
		strange_rational computeLowerSetProb(lower_set_type& ls, std::map<parents_sign_state<NodeValue>*,strange_rational>& probTable);
		void constructProbTable(std::map<parents_sign_state<NodeValue>*, strange_rational>& rationalProb, std::map<std::string, unsigned int>& pos,std::vector<plProbValue>& probTable );
		void computeRelativesPos(plVariablesConjunction& variables, std::vector<unsigned int>& absolute_pos,std::map<std::string, unsigned int>& all, std::map<std::string, unsigned int> & parents);

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
void poset_forest<NodeValue>::MLS(PILGRIM::pmFrequencyCounter<plCSVFileDataDescriptor<int>::CSVDescRowDataType>* fc, std::vector<plProbValue>& probs)
	{
	probs = std::vector<plProbValue>();
	if (fc == nullptr)
		{
		probs.push_back(0.5);
		probs.push_back(0.5);
		return;
		}
	/************************************************************************/
	/* Initialisation                                                       */
	/************************************************************************/
	std::vector<lower_set_type> lowerSets = std::vector<lower_set_type>();
	findLowerSets(lowerSets);
	std::map<parents_sign_state<NodeValue>*, strange_rational> probTable =std::map<parents_sign_state<NodeValue>*, strange_rational>();
	//Gets Variables
	plVariablesConjunction variables =  fc->getVariables();
	//Initializes variable's positions
	std::vector<unsigned int> pos =std::vector<unsigned int>();
	std::map<std::string, unsigned int> relative_pos =std::map<std::string, unsigned int>();
	std::map<std::string, unsigned int> parents_relative_pos =std::map<std::string, unsigned int>();
	computeRelativesPos(variables, pos, relative_pos, parents_relative_pos);


	std::vector<plFloat> freq =std::vector<plFloat>();

	/************************************************************************/
	/*First step : Constructs the table value from the data                 */
	/************************************************************************/
	//Compute frequencies
	fc->frequencyCount(pos, freq);
	for (auto i_state = all_states.begin(); i_state!=all_states.end();i_state++)
		{
		probTable[*i_state] = getRationalFromState(*i_state, freq, relative_pos);
		}


	/************************************************************************/
	/* Second step : MLS Algorithm                                          */
	/************************************************************************/
	while(!lowerSets.empty())
		{
		lower_set_type min_ls = lower_set_type();
		strange_rational min_r = getMinLowerSet(lowerSets, probTable, min_ls);
		std::cout<<"min_ls"<<min_r.numerator()<<" "<<min_r.denominator()<<std::endl;
		//Change probTable
		for (auto i_state = min_ls.begin(); i_state!=min_ls.end();i_state++)
			{
			probTable[*i_state]=min_r;
			}
		//Remove minimal from each lowerSets
		std::vector<lower_set_type> lower_sets_cp = std::vector<lower_set_type>();
		for (auto i_ls = lowerSets.begin(); i_ls!=lowerSets.end();i_ls++)
			{

			for (auto i_min_state= min_ls.begin();i_min_state!=min_ls.end();i_min_state++)
				{
				lower_set_type states_cp = lower_set_type();
				for (auto i_state= i_ls->begin();i_state!=i_ls->end();i_state++)
					{
					if ((*i_min_state) != (*i_state) )
						{
						states_cp.push_back(*i_state);
						}		
					}
				*i_ls = states_cp;
				}
			if(! i_ls->empty())
				{
				lower_sets_cp.push_back(*i_ls);
				}
			}
		lowerSets = lower_sets_cp;
		}
	/************************************************************************/
	/* Third step : Constructs a plProbValue[]                              */
	/************************************************************************/

	constructProbTable(probTable,parents_relative_pos,probs);
	}



template <typename NodeValue>
strange_rational poset_forest<NodeValue>::getRationalFromState(parents_sign_state<NodeValue>* state, std::vector<plFloat>& freq, std::map<std::string, unsigned int>& pos)
	{
	unsigned int neg_val = 0;
	unsigned int  pos_val;
	for (auto i_parent = parentNames.begin();i_parent!=parentNames.end();i_parent++)
		{
		neg_val += state->getState(*i_parent).first *((unsigned int) std::pow(2.0,(int)pos[*i_parent]));
		}
	pos_val = neg_val + ((unsigned int) std::pow(2.0,(int)pos[nName]));
	return strange_rational((int) freq[pos_val], (int)(freq[neg_val]+ freq[pos_val]));
	}


template <typename NodeValue>
strange_rational poset_forest<NodeValue>::computeLowerSetProb(lower_set_type& ls, std::map<parents_sign_state<NodeValue>*,strange_rational>& probTable)
	{
	strange_rational frac= strange_rational();
	for (auto i_state= ls.begin(); i_state!=ls.end();i_state++)
		{
		frac += probTable[*i_state];
		
		}
	return frac;
	}



template <typename NodeValue>
void poset_forest<NodeValue>::constructProbTable(std::map<parents_sign_state<NodeValue>*, strange_rational>& rationalProb, std::map<std::string, unsigned int>& pos, std::vector<plProbValue>& probTable)
	{
	probTable = std::vector<plProbValue>(rationalProb.size()*2);
	for (auto i_rprob= rationalProb.begin();i_rprob!=rationalProb.end();i_rprob++)
		{
		int index =0;
		parents_sign_state<NodeValue>* state = i_rprob->first;
		for (auto i_parent = parentNames.begin();i_parent!=parentNames.end();i_parent++)
			{

			index += state->getState(*i_parent).first *((unsigned int) std::pow(2.0,(int)pos[*i_parent]+1));
			}
		strange_rational value =i_rprob->second;
		if(value.numerator() == 0)
			probTable[index] = 0.5;
		else
			probTable[index] = 1- value.value();
		//int index_compl =index +std::pow(2.0,(int)parentNames.size());
		probTable[index +1] =1 - probTable[index];
		}
	for (auto i_display = probTable.begin(); i_display!=probTable.end();i_display++)
		{
		std::cout<<*i_display<<" ";
		}
	std::cout<<std::endl;
	}


template <typename NodeValue>
void poset_forest<NodeValue>::computeRelativesPos(plVariablesConjunction& variables, std::vector<unsigned int>& absolute_pos,std::map<std::string, unsigned int>& all_pos, std::map<std::string, unsigned int> & parents_pos)
	{
	int cpt =parentNames.size();
	//child first
	absolute_pos.push_back(variables.get_symbol_position(variables.get_symbol_with_name(nName)));
	all_pos[nName] =cpt ;
	//then parent
	for(auto i_parent=parentNames.begin();i_parent!=parentNames.end();i_parent++)
		{
		unsigned int pos_parent =variables.get_symbol_position(variables.get_symbol_with_name(*i_parent));
		absolute_pos.push_back(pos_parent);

		cpt--;
		all_pos[*i_parent]=cpt;
		parents_pos[*i_parent]=cpt;

		//unsigned int relative= 0;
		//unsigned int relative_p= 0;
		//for (auto i_pos_r= all_pos.begin();i_pos_r!=all_pos.end();i_pos_r++)
		//	{
		//	string current_name = i_pos_r->first;
		//	unsigned int current_pos = variables.get_symbol_position(variables.get_symbol_with_name(current_name) );
		//	if(pos_parent < current_pos )
		//		all_pos[current_name]++;
		//	else
		//		relative++;
		//	if (current_name != nName)
		//	{
		//	if(pos_parent < current_pos )
		//		parents_pos[current_name]++;
		//	else
		//		relative_p++;
		//	}
		//	}
		//all_pos[*i_parent]= relative;
		//parents_pos[*i_parent]= relative_p;


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
strange_rational poset_forest<NodeValue>::getMinLowerSet(std::vector<lower_set_type>& lowerSets, std::map<parents_sign_state<NodeValue>*, strange_rational>& probTable, lower_set_type &min_ls)
	{
	strange_rational min_r;
	strange_rational min(1,1);
	std::list<lower_set_type> min_ls_list =std::list<lower_set_type>() ;
	//Searching minimal
	// If there are multiple minimal, they will be merge
	for(unsigned int i = 0 ; i< lowerSets.size();i++)
		{
		min_r = computeLowerSetProb(lowerSets[i], probTable);
		if (min == min_r)
			{
			min_ls_list.push_back(lowerSets[i]);
			}
		if(min_r < min)
			{
			min = min_r;
			min_ls_list = std::list<lower_set_type>();
			min_ls_list.push_back(lowerSets[i]);
			}

		}
	//Suppress all min lower sets
	for (auto i_min_ls=min_ls_list.begin(); i_min_ls!=min_ls_list.end();i_min_ls++)
		{

		for (auto i_ls=lowerSets.begin();i_ls!=lowerSets.end();i_ls++)
			{
			if(*i_min_ls == *i_ls)
				{
				lowerSets.erase(i_ls);
				break;
				}
			}
		for (auto i_min_state=i_min_ls->begin();i_min_state!= i_min_ls->end(); i_min_state++)
			{
			min_ls.push_back(*i_min_state);
			}
		}
	return min;
	}


template <typename NodeValue>
void poset_forest<NodeValue>::getPartialLS(Vertex v, std::set<Vertex>& lowerSet)
	{
	if (lowerSet.count(v) == 0)
		{
		lowerSet.insert(v);
		InEIterator in_it, end_in_it;
		for (boost::tie(in_it,end_in_it) = boost::in_edges(v, poset); in_it!=end_in_it;in_it++)
			{
			Vertex next_v= boost::source(*in_it,poset);
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
