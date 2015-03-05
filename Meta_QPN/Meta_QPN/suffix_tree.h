#pragma once
#include <limits>
#include <iostream>
template <typename T>
class suffix_tree
	{
	typedef std::map<std::string, std::pair<suffix_tree<T>* ,suffix_tree<T>* >> descendants_t;
	public:
		suffix_tree(void):valDef(false),leaf(true),descendants(descendants_t()),motif_size(std::numeric_limits<int>::max()){};
		virtual ~suffix_tree(void);

		bool isLeaf() const;
		bool hasValue() const;
		bool hasDesc(std::string key, bool context_b) ;

		T& getValue();
		int getMotifSize();
		suffix_tree<T>& getDesc(std::string key, bool context_b);
		const suffix_tree<T>& getDesc(std::string key, bool context_b) const;

		suffix_tree<T>& createDesc(std::string key, bool context_b);
		void setValue(T value, int motif_size);

		void display();

	private:
		T value;
		bool valDef, leaf;
		int motif_size;
		descendants_t descendants;

	};

template <typename T>
void suffix_tree<T>::display()
	{
	if (hasValue())
		std::cout<<value;
	else
		std::cout<<"empty";
	std::cout<<"{"<<std::endl;

	for ( descendants_t::iterator i_desc=descendants.begin(); i_desc!=descendants.cend(); i_desc++)
		{
		std::string nName = i_desc->first;
		if(hasDesc(nName, true)){
			std::cout<<nName<<"1|";
			getDesc(nName,true).display();
			}
		if(hasDesc(nName, false)){
			std::cout<<nName<<"0|";
			getDesc(nName,false).display();
			}
		}
	std::cout<<"}"<<std::endl;
	}

template <typename T>
suffix_tree<T>::~suffix_tree(void)
	{
	for (auto i_desc =descendants.begin(); i_desc!=descendants.cend(); i_desc++)
		{

		delete i_desc->second.first;
		delete i_desc->second.second;
		}
	}

template <typename T>
bool suffix_tree<T>::isLeaf() const
	{
	return leaf;
	}



template <typename T>
bool suffix_tree<T>::hasValue() const
	{
	return (valDef);
	}



template <typename T>
bool suffix_tree<T>::hasDesc(std::string key, bool context_b) 
	{
	//std::cout<<"hasDesc"<<key<<":"<<context_b<<(descendants[key].first != nullptr)<<(descendants[key].second != nullptr)<<std::endl;
	if (context_b)
		return (descendants[key].first != nullptr);
	else
		return (descendants[key].second != nullptr);
	}

template <typename T>
T& suffix_tree<T>::getValue()
	{
	return value;
	}


template <typename T>
int suffix_tree<T>::getMotifSize()
	{
	return motif_size;
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
const suffix_tree<T>& suffix_tree<T>::getDesc(std::string key, bool context_b) const
	{
	if (context_b)
		return *(descendants.at(key).first);
	else
		return *(descendants.at(key).second);
	}

template <typename T>
suffix_tree<T>& suffix_tree<T>::createDesc(std::string key, bool context_b)
	{
	leaf=false;
	if (hasDesc(key,context_b))
		{
		return getDesc(key, context_b);
		}
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
	valDef=true;
	}
