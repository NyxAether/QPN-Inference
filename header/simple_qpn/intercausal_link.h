/**********************************************************************************************//**
  \file	intercausal_link.h
 
  \brief Declares the intercausal link class.
  			
  \author Romain RINCE
  		   
  \version 0.1.1
  			
  \date 16/02/2015
  		 
  Header for the intercausal link. This class inherit from the qpn_edge but differ by the sign value which depends on an third node value .
 **************************************************************************************************/
#pragma once
#include "../../header/simple_qpn/qpn_edge.h"
#include "../../header/simple_qpn/qpn_vertex.h"
#include <map>

/**********************************************************************************************//**
\class	intercausal_link

\brief	Describe the intercausal link behavior

\author	Romain RINCE
\date	16/02/2015
 **************************************************************************************************/

class intercausal_link :
	public qpn_edge
	{
	public:

		/**********************************************************************************************//**
		\fn	intercausal_link::intercausal_link(void);
		
		\brief	Default constructor.
		
		\author	Romain RINCE
		\date	16/02/2015

		The default constructor can't be use by himself and need to have is sign map instancied and his linked vertrex as well
		 **************************************************************************************************/

		intercausal_link(void);

		/**********************************************************************************************//**
		\fn	intercausal_link::intercausal_link(qpn_vertex* linked_vert, std::map<int,Sign> valToSignMap);
		
		\brief	Constructor.
		
		\author	Romain RINCE
		\date	16/02/2015
		
		\param [in,out]	linked_vert	Pointer of the linked vertrex
		\param	valToSignMap	   	Contains the sign for each value of linked_vert
		 **************************************************************************************************/

		intercausal_link(qpn_vertex* linked_vert, std::map<int,Sign> valToSignMap);
		~intercausal_link(void);
	
		virtual const Sign get_sign();
		void set_sign (std::map<int,Sign> valToSign);
		void set_sign (int value, const Sign& s);
		virtual std::ostream& display(std::ostream& os) const;

	protected:
		qpn_vertex* linked_v;
		std::map<int,Sign> valToSign;
	};

