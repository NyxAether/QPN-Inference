#pragma once
#include "qpn_sign.h"


template <typename NodeValue>
struct qpn_node
	{
	public:
		qpn_node(void):value(NULL), sign(Sign::ZERO_SIGN), valObserved(false), signObserved(false)
			{
			};
		virtual ~qpn_node(void){};
		friend std::ostream& operator<<(std::ostream& os,const qpn_node<NodeValue>& v);
		virtual inline NodeValue getValue() const;
		virtual inline Sign getSign() const;
		virtual inline std::string getName() const;

		virtual inline void setName(const std::string new_name);
		virtual  void setSign(Sign sign);
		virtual  void setValue(NodeValue val);
		virtual  void setSignObserved(bool obs);
		virtual inline bool isObserved();
		virtual inline bool isValObserved();
		virtual inline bool isSignObserved();

	protected:
		std::string name;
		bool valObserved;
		bool signObserved;
		Sign sign;
		NodeValue value;
	};



template <typename NodeValue>
std::string qpn_node<NodeValue>::getName() const
	{
	return name;
	}

template <typename NodeValue>
Sign qpn_node<NodeValue>::getSign() const
	{
	return sign;
	}

template <typename NodeValue>
NodeValue qpn_node<NodeValue>::getValue() const
	{
	return value;
	}

template <typename NodeValue>
bool qpn_node<NodeValue>::isSignObserved()
	{
	return signObserved;
	}

template <typename NodeValue>
bool qpn_node<NodeValue>::isValObserved()
	{
	return valObserved;
	}


template <typename NodeValue>
bool qpn_node<NodeValue>::isObserved()
	{
	return (valObserved || signObserved);
	}


template <typename NodeValue>
void qpn_node<NodeValue>::setSign(Sign sign)
	{
	this->sign =sign;
	}

template <typename NodeValue>
void qpn_node<NodeValue>::setName(const std::string new_name)
	{
	name = new_name;
	}


template <typename NodeValue>
void qpn_node<NodeValue>::setValue(NodeValue val)
	{
	value =  NodeValue(val);
	valObserved=true;
	}

template <typename NodeValue>
void qpn_node<NodeValue>::setSignObserved(bool obs)
	{
	signObserved =obs;
	}
template <typename NodeValue>
std::ostream& operator<<(std::ostream& os, qpn_node<NodeValue>& node)
	{
	os<<"[label=\""<<node.getName()<<":";
	if(node.isValObserved())
		os<<node.getValue()<<"\",style=filled, color=\"0.75 0.75 0.75\"";
	else {
		os<<node.getSign()<<"\"";
		if(node.isSignObserved())
			os<<",style=bold";
		}
	os<<"]";
	return os;
	}

