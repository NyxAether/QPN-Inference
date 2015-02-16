#pragma once
#include "../../header/simple_qpn/qpn_sign.h"


class qpn_vertex{

public:
	qpn_vertex(std::string name);
	~qpn_vertex();
	int get_value()const;
	void set_value(int val);
	const Sign get_sign()const;
	void set_sign(const Sign& s);
	qpn_vertex(void);
	friend std::ostream& operator<<(std::ostream& os,const qpn_vertex& v);
	std::string name;
	int value;
	Sign sign;

	};