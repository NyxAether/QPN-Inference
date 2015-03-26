#pragma once
#include "..\..\Meta_QPN\Meta_QPN\parents_sign_state.h"
#include <vector>
class poset_forest
	{
	public:
		poset_forest(void);
		~poset_forest(void);

	protected:
		std::vector<parents_sign_state> states;
	};

