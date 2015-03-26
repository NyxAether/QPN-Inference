#pragma once
#include <fstream>
#include <stdarg.h>
#include <string>
#include <map>
#include <vector>
#include "boost\spirit\home\classic\dynamic\impl\conditions.ipp"
#include "boost\algorithm\string.hpp"


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

	private:
		unsigned int size;
	};

