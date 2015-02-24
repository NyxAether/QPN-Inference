#pragma once
#include "qpn_edge.h"
struct qpn_edge_influence :
	public qpn_edge
	{
	public:
		qpn_edge_influence(void);
		qpn_edge_influence(const Sign& sign);
		~qpn_edge_influence(void);

		Sign getSign();

		std::ostream& writeGraphVizFormat(std::ostream& os) const;

	//	virtual qpn_edge_influence& operator=(qpn_edge& edge);



		//virtual void assign( qpn_edge& edge);
		Sign sign;
	};

