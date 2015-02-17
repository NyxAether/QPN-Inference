#pragma once
#include "qpn_sign.h"
struct qpn_edge
	{
	public:
		qpn_edge(void);
		virtual ~qpn_edge(void);
		virtual Sign getSign()= 0;
	};

