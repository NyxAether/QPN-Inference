#pragma once
#include <fstream>
#include <stdarg.h>
#include <string>
#include <map>
#include <vector>
#include "boost\spirit\home\classic\dynamic\impl\conditions.ipp"
#include "boost\algorithm\string.hpp"

template<unsigned int N>
class n_matrix
	{

	public:
		n_matrix(std::string file_path);
		virtual ~n_matrix(void);

		std::pair<unsigned int, unsigned int> get(unsigned int i_args, ...) const;
		//std::pair<unsigned int, unsigned int> get(std::pair<std::string, int> map_args, ...) const;

	private:
		void init_indexes(std::ifstream& file);
		void init_data(std::ifstream& file);
		int ipow(int base, int exp) const;

	protected:
		std::map<std::string, unsigned int> index_map;
		std::vector<unsigned int> nb_value;		
		std::vector<std::pair<unsigned int, unsigned int>> data;
	};

template<unsigned int N>
n_matrix<N>::n_matrix(std::string file_path):index_map(std::map<std::string, unsigned int>()), nb_value(std::vector<unsigned int>()), data(std::vector<std::pair<unsigned int, unsigned int>>())
	{
	std::ifstream file = std::ifstream(file_path, std::ios::in);
	init_indexes(file);
	init_data(file);
	}

template<unsigned int N>
n_matrix<N>::~n_matrix(void)
	{
	}



template<unsigned int N>
std::pair<unsigned int, unsigned int> n_matrix<N>::get(unsigned int i_args, ...) const
	{
	va_list ap;
	va_start(ap, i_args);
	int i_index;
	unsigned int index =i_args;
	for(int i = 1; i < N; i++) {
		i_index = va_arg(ap,unsigned int);
		index += i_index*ipow(nb_value[i], i);
		}
	va_end(ap);
	return data.at(index);
	}


//template<unsigned int N>
//std::pair<unsigned int, unsigned int> n_matrix<N>::get(std::pair<std::string, int> map_args, ...) const
//	{
//	va_list ap;
//	va_start(ap, map_args);
//	std::pair<std::string, int> arg = map_args;
//	int tmp =index_map.at(arg.first);
//	unsigned int index =arg.second *ipow(nb_value[tmp],tmp);
//	for(int i = 1; i < N; i++) {
//		arg = va_arg(ap, std::pair<std::string, int>);
//		index =arg.second * ipow(nb_value[index_map.at(arg.first)],index_map.at(arg.first));
//		}
//	va_end(ap);
//	return data.at(index);
//	}


template<unsigned int N>
void n_matrix<N>::init_indexes(std::ifstream& file)
	{
	std::vector<std::string> init_param;
	std::vector<std::string> val_pair;
	std::string line;
	do //remove white space TODO assert it works
		{
		std::getline(file,line);
		} while (line.empty() );

		boost::split(init_param,line,boost::is_any_of("\t "),boost::token_compress_on);
		int i= 0;

		for (auto i_param=init_param.begin();i_param!=init_param.cend();i_param++)
			{
			boost::split(val_pair,*i_param,boost::is_any_of(":"));
			index_map[val_pair[0]] = i;//Associate to the name of each value is indice on the coeffs std::map 
			nb_value.push_back(atoi(val_pair[1].c_str())-1);
			i++;
			}
	}


template<unsigned int N>
void n_matrix<N>::init_data(std::ifstream& file)
	{
	std::vector<std::string> init_param;
	std::vector<std::string> val_pair;
	std::string line;
	do //remove white space TODO assert it works
		{
		std::getline(file,line);
		} while (line.empty() );
		do 
		{
		boost::split(init_param,line,boost::is_any_of("\t "),boost::token_compress_on);

		for (auto i_param=init_param.begin();i_param!=init_param.cend();i_param++)
			{
			boost::split(val_pair,*i_param,boost::is_any_of(":"));
			data.push_back(std::make_pair(atoi(val_pair[0].c_str()),atoi(val_pair[1].c_str())));
			}
		} while (std::getline(file,line));
	}

template<unsigned int N>
int n_matrix<N>::ipow(int base, int exp) const
	{
	int result = 1;
	while (exp)
		{
		if (exp & 1)
			result *= base;
		exp >>= 1;
		base *= base;
		}

	return result;
	}