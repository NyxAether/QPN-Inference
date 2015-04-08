#pragma once
#include "qpn_descriptor_directed.h"
#include "qpn_descriptor_undirected.h"
#include <set>
#include <vector>

template < typename NodeValue>
class meta_qpn
	{
	public:
		typedef typename qpn_descriptor_directed< NodeValue> qpn_directed_type;
		typedef typename qpn_descriptor_undirected< NodeValue> qpn_undirected_type;

		//TODO using some smart pointers for the qpns can be the good way to do things
		meta_qpn(void):qpn_directed(std::list<qpn_directed_type*>()), qpn_undirected(std::list<qpn_undirected_type*>()){};
		virtual ~meta_qpn(void){};

		void addQpn(qpn_directed_type* new_qpn);
		void addQpn(qpn_undirected_type* new_qpn);

		void addNode(std::string nName);

		void observeNodeValue(std::string nName, NodeValue value);
		void observeNodeSign(std::string nName, Sign sign);

		void resetQPN();
		void resetSigns();

		void propagate(const std::string nName, std::map<std::string, bool>& colorMap, bool fromChild);

		bool exists(std::string nName);
		bool hasDescendent(const std::string nName, std::map<std::string, bool>& colorMap);
		int nodesCount();

		void  writeGraphViz(std::ostream& out);

		qpn_node<NodeValue>** getNode(std::string nName);
		qpn_node<NodeValue>* getNode(int index);
		qpn_edge* getEdge(std::string fromN, std::string toN);
		void getNodeNames(std::list<std::string>& nodeNames) const;
		void getParentNames(std::string nName, std::list<std::string>& parentNames) const;
		void getParentsStatus(std::string nName, std::map<std::string,std::pair<NodeValue, Sign>>& status);

	protected:
		template<typename NodeValue, typename T1>
		void copyNode(i_qpn_descriptor<NodeValue, T1>* qpn)
			{
			std::list<std::string>* nNames = qpn->nodeNames();
			for(std::list<std::string>::iterator nName = nNames->begin(); nName != nNames->cend(); nName++)
				{
				if(nodes[*nName] == nullptr)
					{
					nodes[*nName]= qpn->getNode(*nName);
					}

				}
			qpn->setNodeMap(&nodes);
			};

	private:
		std::list<qpn_directed_type*> qpn_directed;
		std::list<qpn_undirected_type*> qpn_undirected;
		std::map<std::string, qpn_node<NodeValue>*> nodes;

	};

template < typename NodeValue>
void meta_qpn<NodeValue>::addQpn(qpn_directed_type* new_qpn)
	{
	copyNode(new_qpn);
	qpn_directed.push_back(new_qpn);

	} 


template < typename NodeValue>
void meta_qpn<NodeValue>::addQpn(qpn_undirected_type* new_qpn)
	{
	copyNode(new_qpn);
	qpn_undirected.push_back(new_qpn);
	}


template < typename NodeValue>
void meta_qpn<NodeValue>::addNode(std::string nName)
	{
	if(!exists(nName))
		nodes[nName] = new qpn_node<NodeValue>(nName);
	}



template < typename NodeValue>
void meta_qpn<NodeValue>::observeNodeValue(std::string nName, NodeValue value)
	{
	nodes[nName]->setValue(value);
	}

template < typename NodeValue>
void meta_qpn<NodeValue>::observeNodeSign(std::string nName, Sign sign)
	{
	nodes[nName]->setSign( sign);
	nodes[nName]->setSignObserved(true);
	std::map<std::string, bool> colorMap = std::map<std::string, bool>();
	colorMap[nName]=true;
	propagate(nName,colorMap,true);
	}



template < typename NodeValue>
void meta_qpn<NodeValue>::resetQPN()
	{
	//For each node 
	for (auto i_nName = nodes->begin(); i_nName!=nodes->cend(); i_nName++)
		{
		i_nName->second->reset();
		}
	}


template < typename NodeValue>
void meta_qpn<NodeValue>::resetSigns()
	{
	//For each node 
	for (auto i_nName = nodes->begin(); i_nName!=nodes->cend(); i_nName++)
		{
		i_nName->second->resetSign();
		}
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
bool meta_qpn<NodeValue>::exists(std::string nName)
	{
	return nodes[nName] != nullptr;
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
				if(child->isObserved())
					return true;
				if(!colorMap[child->getName()])
					if(hasDescendent(child->getName(), std::map<std::string, bool>(colorMap)))
						return true;
				}
			}
		}
	return false;
	}

template<typename NodeValue>
int meta_qpn<NodeValue>::nodesCount()
	{
	return nodes.size();
	}

template < typename NodeValue>
void meta_qpn<NodeValue>::writeGraphViz(std::ostream& out)
	{
	out<<"digraph G {"<<std::endl;
	for (auto i_node=nodes.cbegin(); i_node!=nodes.cend();i_node++)
		{
		out<<i_node->first<<*(i_node->second)<<";"<<std::endl;
		}
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


template < typename NodeValue>
qpn_node<NodeValue>** meta_qpn<NodeValue>::getNode(std::string nName)
	{
	qpn_node<NodeValue>* node_ptr = nodes[nName];
	if(node_ptr == nullptr)
		{
		addNode(nName);
		}
	return &(nodes[nName]);
	}

template < typename NodeValue>
qpn_node<NodeValue>* meta_qpn<NodeValue>::getNode(int index)
	{
	int i = 0;
	for(auto i_node = nodes.begin(); i_node!=nodes.cend();  i_node++)
		{
		if(i == index)
			return i_node->second;
		}
	return NULL;
	}



template < typename NodeValue>
qpn_edge* meta_qpn<NodeValue>::getEdge(std::string fromN, std::string toN)
	{
	for (auto i_qpn = qpn_directed.begin(); i_qpn!=qpn_directed.cend();i_qpn++)
		{
		if((*i_qpn)->exists(fromN) && (*i_qpn)->exists(toN) )
			return (*i_qpn)->getEdge(fromN, toN);
		}
	return nullptr;
	}



template < typename NodeValue>
void meta_qpn<NodeValue>::getNodeNames(std::list<std::string>& nodeNames) const
	{
	for(auto i_node = nodes.cbegin(); i_node!=nodes.cend();i_node++)
		{
		nodeNames.push_back(i_node->first);
		}
	}


template < typename NodeValue>
void meta_qpn<NodeValue>::getParentNames(std::string nName, std::list<std::string>& parentNames) const
	{
	std::set<std::string> parentNamesSet= std::set<std::string>();
	for (auto i_qpn = qpn_directed.cbegin(); i_qpn!= qpn_directed.cend();i_qpn++)
		{
		std::list<qpn_node<NodeValue>> parents = std::list<qpn_node<NodeValue>>();
		(*i_qpn)->getParents(nName, parents);
		for (auto i_node = parents.cbegin(); i_node!=parents.cend();i_node++)
			{
			parentNamesSet.insert(i_node->getName());
			}
		}
	//for (auto i_qpn = qpn_undirected.cbegin(); i_qpn!= qpn_undirected.cend();i_qpn++)
	//	{
	//	std::list<qpn_node<NodeValue>> parents = std::list<qpn_node<NodeValue>>();
	//	(*i_qpn)->getParents(nName, parents);
	//	for (auto i_node = parents.cbegin(); i_node!=parents.cend();i_node++)
	//		{
	//		parentNamesSet.insert(i_node->getName());
	//		}
	//	}

	std::copy(parentNamesSet.begin(), parentNamesSet.cend(), std::back_inserter(parentNames));
	}


template < typename NodeValue>
void meta_qpn<NodeValue>::getParentsStatus(std::string nName, std::map<std::string,std::pair<NodeValue, Sign>>& status)
	{
	std::map<std::string, std::pair<bool, NodeValue>> save_state;
	std::list<std::string> parentNames = std::list<std::string> ();
	getParentNames(nName, parentNames);
	//Set the values for all the parents
	for (auto i_pName = parentNames.begin(); i_pName!=parentNames.cend(); i_pName++)
		{
		qpn_node<NodeValue>** parent = getNode(*i_pName);
		save_state[*i_pName]=std::make_pair((*parent)->isValObserved(),(*parent)->getValue());
		(*parent)->setValue(status[*i_pName].first);
		}
	//Catch all the signs propagated 
	for (auto i_pName = parentNames.begin(); i_pName!=parentNames.cend(); i_pName++)
		{
		qpn_node<NodeValue>* parent = *(getNode(*i_pName));
		qpn_edge* e=  getEdge(*i_pName, nName);
		if(e != nullptr)
			status[*i_pName].second = e->getSign() * parent->getSign();//TODO Error we need the sign of the node to e+v 
		}
	//Clean modifications
	for (auto i_pName = parentNames.begin(); i_pName!=parentNames.cend(); i_pName++)
		{
		qpn_node<NodeValue>** parent = getNode(*i_pName);
		if(!save_state[*i_pName].first)
			(*parent)->reset();
		else
			(*parent)->setValue(save_state[*i_pName].second);
		}
	}
