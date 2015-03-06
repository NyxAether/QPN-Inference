#pragma once
#include "boost\spirit\home\classic\dynamic\impl\conditions.ipp"
#include "qpn_influence.h"
#include "qpn_product_synergy.h"
#include "qpn_additive_synergy.h"
#include "qpn_nm_influence.h"
#include "qpn_context_specific.h"
#include "meta_qpn.h"
#include <fstream> 

class meta_qpn_controller
	{
	public:
		meta_qpn_controller(void);
		virtual ~meta_qpn_controller(void);

	private:
		meta_qpn<bool> qpn;
	};

