#pragma once
#include "boost\spirit\home\classic\dynamic\impl\conditions.ipp"
#include "qpn_influence.h"
#include "qpn_product_synergy.h"
#include "qpn_additive_synergy.h"
#include "qpn_nm_influence.h"
#include "qpn_context_specific.h"
#include "meta_qpn.h"
#include <fstream> 

class meta_qpn_controller:
	public meta_qpn<bool>
	{
	public:
		meta_qpn_controller(void);
		virtual ~meta_qpn_controller(void);

		void addInfluence(std::string from, std::string to, Sign sign);
		void addProductSynergy(std::string nName1, std::string nName2, std::string linked, Sign sign);
		void addProductSynergy(std::string nName1, std::string nName2, std::string linked, Sign trueS, Sign falseS);

		void writeGraphViz(std::string file_path);

	private:
		qpn_influence<bool> influences;
		qpn_product_synergy<bool> product_synergies;
		qpn_context_specific<bool> context_specifics;
	};

