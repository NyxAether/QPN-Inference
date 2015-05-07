#pragma once

#include "pilgrim\general\pmBayesianNetwork.h"
#include "meta_qpn_controller.h"

class qpn_learner
	{
	
	public:
		qpn_learner(void);
		qpn_learner(PILGRIM::pmBayesianNetwork* bayesNet);
		~qpn_learner(void);

		meta_qpn_controller learn();

	private:
		PILGRIM::pmBayesianNetwork * bn;
	};

