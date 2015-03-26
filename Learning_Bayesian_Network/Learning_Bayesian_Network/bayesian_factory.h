#pragma once
#include "..\..\Meta_QPN\Meta_QPN\meta_qpn_controller.h"
#include "n_matrix.h"
#include <memory>
#include <pl.h>

class bayesian_factory
	{
	public:
		bayesian_factory(meta_qpn_controller* controller);
		~bayesian_factory(void);

		void addData(std::string nName, std::string filePath);
		void build();

		void computeLowerSets(std::string nName, std::list<std::string> parentNames);

	protected:
		meta_qpn_controller* qpn;
		std::map<std::string,std::shared_ptr<n_matrix>> data;
	};

