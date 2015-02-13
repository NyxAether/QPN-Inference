#include "intercausal_link.h"


using namespace std;


intercausal_link::intercausal_link(void):qpn_edge(), linked_v(NULL), valToSign(map<int,Sign>())
	{

	}

intercausal_link::intercausal_link(qpn_vertex* linked_vert, map<int,Sign> valToSignMap):qpn_edge(), linked_v(linked_vert),valToSign(valToSignMap)
	{

	}

intercausal_link::~intercausal_link(void)
	{
	}


const Sign intercausal_link::get_sign()
	{
	if(linked_v->get_value() == -1)
		return Sign::ZERO_SIGN;
	else
		return valToSign[linked_v->get_value()];
	}

void intercausal_link::set_sign(map<int,Sign> valToSign)
	{
	valToSign = map<int,Sign>(valToSign);
	}

void intercausal_link::set_sign(int value, const Sign& s)
	{
	valToSign[value] = s;
	}

ostream& intercausal_link::display(ostream& os) const
	{
	os <<"[label=\"";
		for(auto iter = valToSign.cbegin(); iter != valToSign.cend();){

			os<< iter->second;
			if (++iter != valToSign.cend())
				{
				os<<",";
				}

			}
		os<<"\",style=dotted, dir=none]";
		return os;
	}
