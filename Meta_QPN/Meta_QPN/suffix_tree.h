#pragma once
#include <limits>
#include <iostream>
template <typename T>
class suffix_tree
	{
	typedef std::map<std::string, std::pair<suffix_tree<T>* ,suffix_tree<T>* >> descendants_t;
	public:
		suffix_tree(void):valDef(false),descendants(descendants_t()),motif_size(std::numeric_limits<int>::max()){};
		virtual ~suffix_tree(void);

		bool isLeaf();
		bool hasValue();
		bool hasEmpty();
		bool hasDesc(std::string key, bool context_b);

		T& getValue();
		int getMotifSize();
		suffix_tree<T>& getEmpty();
		suffix_tree<T>& getDesc(std::string key, bool context_b);

		suffix_tree<T>& createDesc(std::string key, bool context_b);
		void setValue(T value, int motif_size);

	private:
		T value;
		bool valDef;
		int motif_size;
		suffix_tree<T>* empty;
		descendants_t descendants;

	};


template <typename T>
suffix_tree<T>::~suffix_tree(void)
	{
	delete empty;
	for (auto i_desc =descendants.begin(); i_desc!=descendants.cend(); i_desc++)
		{
		delete i_desc->second.first;
		delete i_desc->second.second;
		}
	}

template <typename T>
bool suffix_tree<T>::isLeaf()
	{
	return (!hasEmpty() && descendants.empty());
	}



template <typename T>
bool suffix_tree<T>::hasValue()
	{
	return (value != NULL);
	}



template <typename T>
bool suffix_tree<T>::hasEmpty()
	{
	return (empty != nullptr);
	}

template <typename T>
bool suffix_tree<T>::hasDesc(std::string key, bool context_b)
	{
	if (context_b)
	return (descendants[key].first != NULL);
	else
		return (descendants[key].second != NULL);
	}

template <typename T>
T& suffix_tree<T>::getValue()
	{
	return valDef;
	}


template <typename T>
int suffix_tree<T>::getMotifSize()
	{
	return motif_size;
	}


template <typename T>
suffix_tree<T>& suffix_tree<T>::getEmpty()
	{
	return &empty;
	}

template <typename T>
suffix_tree<T>& suffix_tree<T>::getDesc(std::string key, bool context_b)
	{
	if (context_b)
	return *(descendants[key].first);
	else
		return *(descendants[key].second);
	}


template <typename T>
suffix_tree<T>& suffix_tree<T>::createDesc(std::string key, bool context_b)
	{
	if (hasDesc(key,context_b))
	{
	return getDesc(key, context_b);
	}
	//if(descendants[key] == NULL)
	//	{
	//	descendants[key] = std::pair<suffix_tree<T>* ,suffix_tree<T>* >();
	//	}
	suffix_tree<T>* new_tree = new suffix_tree<T>();
	if (context_b)
		descendants[key].first = new_tree;
	else
		descendants[key].second = new_tree;
	return *new_tree;
	}


template <typename T>
void suffix_tree<T>::setValue(T value, int motif_size)
	{
	this->value=value;
	this->motif_size=motif_size;
	}
