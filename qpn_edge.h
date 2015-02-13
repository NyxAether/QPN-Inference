#pragma once
#include "qpn_sign.h"

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

