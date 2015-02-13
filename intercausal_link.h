#pragma once
#include "qpn_edge.h"
#include "qpn_vertex.h"
#include <map>
class intercausal_link :
	public qpn_edge
	{
	public:
		intercausal_link(void);
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

