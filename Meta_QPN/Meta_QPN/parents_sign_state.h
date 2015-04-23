/**
* \file parents_sign_state.h
* \brief Store a state of signs propagate by parents's node
* \author Romain Rincé
* \date 26 march 2014
*/

#pragma once
#include "qpn_sign.h"
#include <map>
#include <utility>
#include <memory>



/*! \class parents_sign_state
* \brief Store a state of signs propagate by parents's node
*
* Store a state configuration for all the parents of a node. So it stores both of the value and the sign propagated by a parent.
* The principal purpose of this object is to define a partial order between the states.
* This order was initially necessary for an MLS algorithm using for learning Bayesian network from QPN.
* 
* This order is defined regarding to the signs of the state and the variation of those signs between two  parents_state.
*  For instance a variation positive for each sign induces a global positive variation from a state to an other.
*  More information can be find about sign variation into the Sign class.
*
* If the two state have different parents's node defined they are necessarily considered as uncomparable
*/
template <typename NodeValue>
class parents_sign_state
	{
	public:
		parents_sign_state(std::string nodeName, std::map<std::string, std::pair<NodeValue, Sign>>* observed_state);
		virtual ~parents_sign_state(void);


		std::string getNode() const;
		void getParents(std::vector<std::string>& v) const;
		/*!
		*\brief return state associate to a parent
		*
		*\param nName Name of the parent of which we want to know the state
		*
		*/
		std::pair<NodeValue, Sign> getState(std::string nName)const;

		/*!
		*  \brief Compare the current object with an other
		*
		*  This method allow a partial order comparison between parents_sign_state.
		*	To parents state can be compared regarding to their signs :
		*   - If the global variation of the signs is positive, the function return 1
		*   - If the global variation of the signs is negative, the function return -1
		*   - If the global variation of the signs is unchanged/equal, the function return 0
		*   - If the global variation of the signs is unknown or the parents define are different, the function return any other integer
		*
		*  \param pss : the other parents_sign_state with which we want to compare the current object
		* \return 
		*/
		int compare(const parents_sign_state& pss) const;

		virtual bool operator==(const parents_sign_state<NodeValue>& pss);

	protected:
		std::map<std::string, std::pair<NodeValue, Sign>>* state;
		std::string nName;

	};

template <typename NodeValue>
parents_sign_state<NodeValue>::parents_sign_state(std::string nodeName,std::map<std::string, std::pair<NodeValue, Sign>>* observed_state):state(observed_state), nName(nodeName)
	{

	}


template <typename NodeValue>
parents_sign_state<NodeValue>::~parents_sign_state(void)
	{
	delete state;
	}


template <typename NodeValue>
std::string parents_sign_state<NodeValue>::getNode() const
	{
	return nName;
	}


template <typename NodeValue>
void parents_sign_state<NodeValue>::getParents(std::vector<std::string>& v) const
	{
	for (auto i_parent=state->cbegin();i_parent!=state->cend();i_parent++)
		{
		v.push_back(i_parent->first);
		}
	}

template <typename NodeValue>
std::pair<NodeValue, Sign> parents_sign_state<NodeValue>::getState(std::string nName)const
	{
	return state->at(nName);
	}


template <typename NodeValue>
int parents_sign_state<NodeValue>::compare(const parents_sign_state& pss) const
	{
	if(nName != pss.getNode())
		return 3; //incomparable
	Sign variation = Sign::ZERO_SIGN;
	for (auto i_state= (*state).cbegin(); i_state != (*state).cend(); i_state++ )
		{
		std::string pName =i_state->first;
		Sign signTo = getState(pName).second;
		Sign signFrom = pss.getState(pName).second;
		if (signTo == Sign::QMARK_SIGN && signFrom==Sign::QMARK_SIGN)
			{
			NodeValue valTo =getState(pName).first;
			NodeValue valFrom = pss.getState(pName).first;
			if(valTo != valFrom)
				return 4;//incomparable. We can break the algorithm here we have to propagate a QMARK_SIGN which is dominant by + operation
			//no else case because it's equivalent to no variation and therefore there is no need to propagate it into the variation
			}
		else
			variation = variation + (signTo - signFrom);
		}
	if(variation == Sign::PLUS_SIGN)
		return 1;
	if(variation == Sign::MINUS_SIGN)
		return -1;
	if(variation == Sign::ZERO_SIGN)
		return 0;
	//if(variation == Sign::QMARK_SIGN)
		return 2; //Standard incomparability 
	
	}

template <typename NodeValue>
bool parents_sign_state<NodeValue>::operator==(const parents_sign_state<NodeValue>& pss)
	{
	if(nName != pss.getNode())
		return false;
	for (auto i_value = state->begin(); i_value!= state->end(); i_value++)
		{
		std::string nName = i_value->first;
		NodeValue val1, val2;
		val1 = i_value->second.first;
		val2 = pss.getState(nName).first;
		if(val1 != val2)
			return false;
		}
	return true;
	}
