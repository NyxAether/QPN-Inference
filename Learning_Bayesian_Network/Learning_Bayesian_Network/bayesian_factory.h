/*=============================================================================
* Product        : 
* File           : bayesian_factory.h
* Author         : Romain RINCE
* Creation       : 

*=============================================================================
*/
#pragma once
#include "meta_qpn_controller.h"
#include "n_matrix.h"
#include <memory>
#include <pl.h>
#include "poset_forest.h"
#include "pilgrim\general\LoadDataSet.h"
#include "pilgrim\general\pmCommonTypeDefinations.h"

//=============================================================================
/*!
*  \brief bayesian_factory class
*
*  \details This class purpose is to construct a bayesiannetwork using plBayesianNetwork and a qpn 
*  \author  Romain RINCE
*  \version   0.1
*  \date      Arpil 7, 2015

*/
class bayesian_factory
	{
	public:


		typedef poset_forest<bool> poset_type;
		typedef std::map<std::string,poset_forest<bool>> posets_type;
		typedef std::map<std::string, pmCSVDataSet*> data_type;

		/**
		* \brief Main constructor
		* \details Using a setted qpn, this constructor will process all the structures needed to 
		* compute the bayesian network
		*  \param controller : a point on a meta_qpn_controller. If this meta_qpn is modified after
		* the construction it will result an inconsistent bayesian network on best case, errors on 
		* worst.
		*/
		bayesian_factory(meta_qpn_controller* controller);
		~bayesian_factory(void);

		/**
		* \brief Add observation data to compute probabilities
		* \details This method need to be call for each node on the qpn. The file in parameter
		* specifies observation on the parents's node and the value of the current node. 
		* Probabilities can be extract from this and in finie the corresponding Bayesian network
		* \param nName : name of the node on which data want to be added
		* \parm filePath : file containg data for the current node?
		*/
		void addData(std::string nName, std::string filePath);
		/**
		*\brief Construct the bayesian network
		*\details Buid a bayesian network using the data setted by the previous call of addData.
		* If a node doesn't have data specified, all configurations of state for the node and his 
		* parents will be considered as equiproportional.
		*/
		void build();

	protected:
		/**
		* \brief Construct a poset for a node in the qpn
		* \details With the aim of computing probabilities, algorithm MLS need to compute the lower
		* sets depending into the value of the node, the parents and the signs propagated 
		* considering those values. 
		* \param nName : node name on which we want to compute the lower sets.
		*/
		void constructPoset(std::string nName);
		
		/**
		* \brief Define values for a set of nodes
		* \details With the aim of constructing a poset, it's necessary to define all set possible 
		* for the parent nodes and observe the value of the common child. This is the purpose of 
		* this method. Each state compute is use to define a new lower set. The number of states can be easily estimated : values are
		* considerated boolean so the number of state is equal to 2^nb_parents.
		* \param nName : name of the child
		* \param begin : first iterator on the parent names (you can see that is not a reference because the algorithm simulate a 
		* tree structure to compute all state) 
		* \param end : last iterator on the parent names
		* \param[in] state : empty map needed to begin the algorithm. Store configuration of parents nodes in a specific state
		*/
		void stateDefine(std::string nName, std::list<std::string>::iterator begin, std::list<std::string>::iterator end, std::map<std::string, std::pair<bool, Sign>>* state);

	protected:
		meta_qpn_controller* qpn;
		posets_type posets;
		data_type data;



	};

