/**********************************************************************************************//**
\file	qpn_edge.h

\brief	Describes the qpn edge class.

\author	Romain RINCE
\date	16/02/2015
 **************************************************************************************************/

#pragma once
#include "../../header/simple_qpn/qpn_sign.h"

/**********************************************************************************************//**
\class	qpn_edge qpn_edge.h qpn_edge.h

\brief	Describes the behavior of a edge in a qpn.

\author	Romain RINCE
\date	16/02/2015

An edge is defining by is Sign which can be '+', '-', '0' or '?' respectively for a positive influence, negative influence, zero influence and ambiguous influence.
 **************************************************************************************************/

class qpn_edge
	{
	public:
		qpn_edge( const Sign& s);
		virtual ~qpn_edge(void);

		virtual const Sign get_sign();
		void set_sign (const Sign& s);
		virtual std::ostream& display(std::ostream& os) const;
		friend std::ostream& operator<< (std::ostream& os, const qpn_edge& edge);
		Sign sign;
	
		qpn_edge(void);
	};

