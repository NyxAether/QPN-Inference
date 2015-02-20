#pragma once
#include "qpn_sign.h"
struct qpn_edge
	{
	public:
		qpn_edge(void);
		virtual ~qpn_edge(void);
		virtual Sign getSign();
		virtual std::ostream& writeGraphVizFormat(std::ostream& os) const;
		friend std::ostream& operator<< (std::ostream& os, const qpn_edge& edge);
	};

