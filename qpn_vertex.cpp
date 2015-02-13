#pragma once
#include "qpn_vertex.h"
#include <string>

using namespace std;

 qpn_vertex::qpn_vertex(string name){
	 this->name = name;
	 value = -1;
	 sign = Sign::ZERO_SIGN;
	}

 qpn_vertex::qpn_vertex(void)
	 {
	 name= "";
	 value =-1;
	 sign = Sign::ZERO_SIGN;
	 }

int qpn_vertex::get_value(){
	 return value;
	 }
const Sign qpn_vertex::get_sign(){
	return sign;
	}
void qpn_vertex::set_value(int val){
	cout<<name<<endl;
		std::cout <<"setvalue "<<value<<" => "<<val<< endl;
	value = val;
	cout<<"nouvelle valeur "<<value<<endl;
	}
void qpn_vertex::set_sign(const Sign& s){
	cout<<name<<endl;
		std::cout <<"setsign "<<sign<<" => "<<s<< endl;

	sign = Sign(s);
	cout<<"nouvelle valeur "<<sign<<endl;
	}

qpn_vertex::~qpn_vertex()
	{

	}
