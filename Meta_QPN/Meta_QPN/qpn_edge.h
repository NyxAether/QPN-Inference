#pragma once
#include "qpn_sign.h"
struct qpn_edge
	{
	public:
		qpn_edge(void);
		virtual ~qpn_edge(void);

		virtual Sign getSign();
		virtual std::ostream& writeGraphVizFormat(std::ostream& os) const;
		
		//virtual qpn_edge& operator=(qpn_edge& edge);

		friend std::ostream& operator<< (std::ostream& os, const qpn_edge& edge);

				//virtual void assign( qpn_edge& edge);
		std::string name;



	};

