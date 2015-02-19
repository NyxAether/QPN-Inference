//#pragma once
//#include "meta_qpn.h"
//
//using namespace std;
//
//template <class NodeValue, typename GraphType>
//meta_qpn<NodeValue, GraphType>::meta_qpn(void):qpn_directed(list<qpn_descriptor<NodeValue>&>()),qpn_undirected(list<qpn_descriptor<NodeValue>&>())
//	{
//	}
//
//template <class NodeValue, typename GraphType>
//meta_qpn<NodeValue, GraphType>::~meta_qpn(void)
//	{
//	}
//
//
//template <class NodeValue, typename GraphType>
//void meta_qpn<NodeValue, GraphType>::addQpn(qpn_descriptor<NodeValue, GraphType>& qpn, bool isDirected)
//	{
//	bool empty = qpn_directed.size==0;
//	if (isDirected)
//		{
//		qpn_directed.push_back(qpn);
//		copyNode(from, to);
//		} 
//	else
//		{
//		qpn_undirected.push_back(qpn);
//		}
//
//	}
//	template <class NodeValue, typename GraphType>
//	void meta_qpn<NodeValue, GraphType>::copyNode(qpn_descriptor<class NodeValue, GraphType>& from, qpn_descriptor<class NodeValue, GraphType>& to)
//		{
//	
//		}
//
//	}
//