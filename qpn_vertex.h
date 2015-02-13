#pragma once
#include "qpn_sign.h"


class qpn_vertex{

public:
	qpn_vertex(std::string name);
	~qpn_vertex();
	int get_value();
	void set_value(int val);
	const Sign get_sign();
	void set_sign(const Sign& s);
	qpn_vertex(void);

	std::string name;
	int value;
	Sign sign;

	};