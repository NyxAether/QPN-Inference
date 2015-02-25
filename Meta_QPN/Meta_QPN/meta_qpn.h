#pragma once
#include "qpn_descriptor.h"

template < typename NodeValue>
class meta_qpn
	{
	public:
		typedef typename qpn_descriptor< NodeValue, boost::bidirectionalS> qpn_directed_type;
		typedef typename qpn_descriptor< NodeValue, boost::undirectedS> qpn_undirected_type;

		//TODO using some smart pointers for the qpns can be the good way to do things
		meta_qpn(void):qpn_directed(std::list<qpn_directed_type*>()), qpn_undirected(std::list<qpn_undirected_type*>()){};
		~meta_qpn(void){};

		void addQpn(qpn_directed_type* new_qpn);
		void addQpn(qpn_undirected_type* new_qpn);

		void observeNodeValue(std::string nName, NodeValue value);
		
		void observeNodeSign(std::string nName, Sign sign);

		void propagate(const std::string nName, std::map<std::string, bool>& colorMap, bool fromChild);

		bool hasDescendent(const std::string nName, std::map<std::string, bool>& colorMap);

		void  writeGraphViz(std::ostream& out);

	protected:
		template<typename NodeValue, typename T1, typename T2>
		void copyNode(qpn_descriptor<NodeValue, T1>* from, qpn_descriptor<NodeValue, T2>* to)
			{
			std::list<std::string>* nNames = from->nodeNames();
			for(std::list<std::string>::iterator nName = nNames->begin(); nName != nNames->cend(); nName++)
				{
				if(! to->exists(*nName))
					{
					to->addVertex(from->getNode(*nName));
					}
				else
					{
					from->setNode(*nName, to->getNode(*nName));
					}
				}
			};

	private:
		std::list<qpn_directed_type*> qpn_directed;
		std::list<qpn_undirected_type*> qpn_undirected;
	};



template < typename NodeValue>
void meta_qpn<NodeValue>::addQpn(qpn_directed_type* new_qpn)
	{
		if (qpn_directed.empty())
			{
			if(!qpn_undirected.empty())
				{
				for(std::list<qpn_undirected_type*>::iterator it = qpn_undirected.begin();  it!=qpn_undirected.cend();it++){
					copyNode(*it, new_qpn);
					}
				}
			}
		else
			{
			copyNode(new_qpn, qpn_directed.front());
			}
		qpn_directed.push_back(new_qpn);

		} 
	

template < typename NodeValue>
void meta_qpn<NodeValue>::addQpn(qpn_undirected_type* new_qpn)
	{
	if(!qpn_directed.empty())
		{
		copyNode(new_qpn, qpn_directed.front());		
		}
		qpn_undirected.push_back(new_qpn);
	}

template < typename NodeValue>
void meta_qpn<NodeValue>::observeNodeValue(std::string nName, NodeValue value)
	{
	qpn_directed.front()->observeNodeValue(nName, value);
	}

template < typename NodeValue>
void meta_qpn<NodeValue>::observeNodeSign(std::string nName, Sign sign)
	{
	qpn_directed.front()->observeNodeVariation(nName, sign);
	std::map<std::string, bool> colorMap = std::map<std::string, bool>();
	colorMap[nName]=true;
	propagate(nName,colorMap,true);
	}

template < typename NodeValue>
void meta_qpn<NodeValue>::propagate(const std::string nName, std::map<std::string, bool>& colorMap, bool fromChild)
	{
	colorMap[nName]=true;
	//Directed
	for (std::list<qpn_directed_type*>::iterator it_qpn_dir = qpn_directed.begin();it_qpn_dir != qpn_directed.cend();it_qpn_dir++) //For each QPN
		{
		std::map<std::string, bool> nextNodes = std::map<std::string, bool> ();
		if((*it_qpn_dir)->exists(nName)) //if the current node exist in it
			{
			(*it_qpn_dir)->propagate(nName,colorMap, (fromChild ||hasDescendent(nName,std::map<std::string, bool> ())), nextNodes);// The sign is propagate for each edges
				for(std::map<std::string, bool>::iterator it_nName = nextNodes.begin();it_nName!=nextNodes.cend();it_nName++) // and propagate is launch again on each node modified
					{
					propagate((*it_nName).first,std::map<std::string, bool>(colorMap),it_nName->second);
					}
			}
		}

	//Undirected
	for (std::list<qpn_undirected_type*>::iterator it_qpn_undir = qpn_undirected.begin();it_qpn_undir != qpn_undirected.cend();it_qpn_undir++)
		{
		std::map<std::string, bool> nextNodes = std::map<std::string, bool> ();
		if((*it_qpn_undir)->exists(nName))
			{
			(*it_qpn_undir)->propagate(nName,colorMap, false, nextNodes);
				for(std::map<std::string, bool>::iterator it_nName = nextNodes.begin();it_nName!=nextNodes.cend();it_nName++)
					{
					//In qpns undirected, from child need to be false everytime due to the indirection of the function target, source, out_egde, in_edge in those case.
					propagate((*it_nName).first,std::map<std::string, bool>(colorMap),it_nName->second);
					}
			}
		}
	}


template < typename NodeValue>
bool meta_qpn<NodeValue>::hasDescendent(const std::string nName, std::map<std::string, bool>& colorMap)
	{
	colorMap[nName]=true;
	//Directed
	for (std::list<qpn_directed_type*>::iterator it_qpn_dir = qpn_directed.begin();it_qpn_dir != qpn_directed.cend();it_qpn_dir++) //For each QPN
		{
		if((*it_qpn_dir)->exists(nName))
			{
			list<qpn_node<NodeValue>> children =list<qpn_node<NodeValue>>();
			(*it_qpn_dir)->getChildren(nName, children);
				for(list< qpn_node<NodeValue>>::iterator child = children.begin();child!=children.cend(); child++)
					{
					if(child->valIsSet)
						return true;
					if(!colorMap[child->name])
						if(hasDescendent(child->name, std::map<std::string, bool>(colorMap)))
							return true;
					}
			}
		}
	return false;
	}

template < typename NodeValue>
void meta_qpn<NodeValue>::writeGraphViz(std::ostream& out)
	{
	out<<"digraph G {"<<std::endl;
	qpn_directed.front()->writeGraphVizNodes(out);
	for(std::list<qpn_directed_type*>::iterator it = qpn_directed.begin(); it!=qpn_directed.cend(); it++)
		{
		(*it)->writeGraphVizEdges(out);
		}
	for(std::list<qpn_undirected_type*>::iterator it = qpn_undirected.begin(); it!=qpn_undirected.cend(); it++)
		{
		(*it)->writeGraphVizEdges(out);
		}
	out<<"}"<<std::endl;
	}

