#pragma once
#include <string>

#include "qpn_edge.h"
#include "qpn_node.h"
#include "qpn_sign.h"
#include "suffix_tree.h"


template <typename NodeValue>
struct qpn_edge_context_specific :
	public qpn_edge
	{
	typedef std::list<std::pair<std::list<std::pair<std::string,bool>>,Sign>> contexts_t;
	public:
		//************************************
		// Method:    qpn_edge_context_specific
		// FullName:  qpn_edge_context_specific<NodeValue>::qpn_edge_context_specific
		// Access:    public 
		// Returns:   
		// Qualifier:
		// Parameter: std::list<qpn_node<NodeValue> * > nodes
		// Parameter: contexts_t contexts
		// The two lists of parameter need to be ordered cautiously with a special logic :
		// The order of qpn_node will influence the context order in the contexts parameter.
		// For instance, if nodes are specified in the following order A,B,C,D
		// If context not D, A and B need to be specified only in this order : A, B , not D
		//************************************
		qpn_edge_context_specific(std::list<qpn_node<NodeValue>**> nodes_list, contexts_t contexts);
		~qpn_edge_context_specific(void){};

		Sign getSign();

		std::ostream& writeGraphVizFormat(std::ostream& os) const;

	protected:
		void constructSuffixTree(suffix_tree<Sign>& root,
			std::list<std::pair<std::string,bool>>::iterator i_nName,
			std::list<std::pair<std::string,bool>>::const_iterator cend,
			Sign sign, int motif_size);

	private:
		std::list<std::string> ordered_nNames;
		std::map<std::string, qpn_node<NodeValue>**> nodes;
		suffix_tree<Sign>* root;

	};

template <typename NodeValue>
qpn_edge_context_specific<NodeValue>::qpn_edge_context_specific(std::list<qpn_node<NodeValue>**> nodes_list, contexts_t contexts)
	{
	//construct a new root
	root = new suffix_tree<Sign>();
	//Create 2 structures for the node.
	//a list containing the names of node ordered in the defined way by parameters nodes
	ordered_nNames = std::list<std::string>();
	//A  map which grant access to a node by is name
	nodes = std::map<std::string, qpn_node<NodeValue>**>();

	for (std::list<qpn_node<NodeValue>**>::iterator i_node=nodes_list.begin(); i_node!=nodes_list.cend(); i_node++)
		{
		std::string nName = (*(*i_node))->name;
		ordered_nNames.push_back(nName);
		nodes[nName] = (*i_node);
		}
	//For each contexts specified
	for (contexts_t::iterator i_context= contexts.begin(); i_context !=contexts.cend(); i_context++)
		{
		//extend the suffix tree with the appropriate sign
		//For each element on the context we create associate suffix
		for (auto i_nName=(*i_context).first.begin();i_nName!=(*i_context).first.end(); i_nName++)
			{
			constructSuffixTree(*root,i_nName,(*i_context).first.end(),i_context->second,i_context->first.size());
			}
		}
	}

	template <typename NodeValue>
	Sign qpn_edge_context_specific<NodeValue>::getSign()
		{
		//Each node has to be considerate as a first element of the suffix 
			//Then for each node following this node including himself (following the order specified on construction time)
		
				//If a value is specified (node in the context)
		
				//if this context has been defined on the suffix tree
				
				//child associated to the context become the new root
				
				
			
			
			
		
		//We look on the suffix tree 
		return Sign::ZERO_SIGN;
		}


	template <typename NodeValue>
	std::ostream& qpn_edge_context_specific<NodeValue>::writeGraphVizFormat(std::ostream& os) const
		{
		return os;
		}



	template <typename NodeValue>
	void qpn_edge_context_specific<NodeValue>::constructSuffixTree(suffix_tree<Sign>& tree, std::list<std::pair<std::string,bool>>::iterator i_nName, std::list<std::pair<std::string,bool>>::const_iterator cend, Sign sign, int motif_size)
		{

		std::string nName = i_nName->first;
		bool context_b = i_nName->second;
				std::cout<<nName<<context_b<<":"<<motif_size<<std::endl;
		//If the current node in the suffix tree doesn't have the specified desc
		if (! tree.hasDesc(nName, context_b))
			{
			//he's created
			tree.createDesc(nName, context_b);
			}
		//Descendant specified is catch
		suffix_tree<Sign>& desc = tree.getDesc(nName, context_b);
		//and is sign is changed if he's specified by a least longer motif
		if(motif_size < desc.getMotifSize())
			{
			desc.setValue(sign, motif_size);
			}
		i_nName++;
		//And recurse on the next elements in the context as descendant of the current suffix tree node
		for (;i_nName!=cend;i_nName++)
			{
					
			constructSuffixTree(desc, i_nName, cend, sign, motif_size);
					
			}

		}

