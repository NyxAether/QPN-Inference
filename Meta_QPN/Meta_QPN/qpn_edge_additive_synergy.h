#pragma once
#include "qpn_edge.h"
#include "qpn_additive_synergy.h"

struct qpn_edge_additive_synergy :
	public qpn_edge
	{
	public:
		qpn_edge_additive_synergy(void):sign(Sign::ZERO_SIGN){};
		qpn_edge_additive_synergy( Sign sign, std::string nName):sign(sign),affected_node(nName){};
		~qpn_edge_additive_synergy(void){};

		Sign getSign();
		std::ostream& writeGraphVizFormat(std::ostream& os) const;
		Sign getRealSign();
		const std::string   getAffectedNode() const;

	private:
		std::string affected_node;
		Sign sign;


	};


