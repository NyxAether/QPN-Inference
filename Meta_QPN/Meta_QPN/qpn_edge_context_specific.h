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
		Sign getSign() const;
		std::ostream& writeGraphVizFormat(std::ostream& os) const;

	protected:
		void constructSuffixTree(suffix_tree<Sign>& tree,
			std::list<std::pair<std::string,bool>>::iterator i_nName,
			std::list<std::pair<std::string,bool>>::const_iterator cend,
			Sign sign, int motif_size);
		void findBestMotif(suffix_tree<Sign>& tree,
			std::list<std::string>::const_iterator i_nName,
			std::list<std::string>::const_iterator cend,
			Sign & sign, int& motif_size) const;

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
		std::string nName = (*(*i_node))->getName();
		ordered_nNames.push_back(nName);
		nodes[nName] = (*i_node);
		}
	//For each contexts specified
	for (contexts_t::iterator i_context= contexts.begin(); i_context !=contexts.cend(); i_context++)
		{
		suffix_tree<Sign>& tree = *root;
		Sign sign = i_context->second;
		int motif_size = i_context->first.size();
		//extend the suffix tree with the appropriate sign
		//For each element on the context we create associate suffix
		constructSuffixTree(tree,(*i_context).first.begin(),(*i_context).first.end(),sign,motif_size);
		}
	std::cout<<std::endl<<"const"<<std::endl;
	root->display();
	}

template <typename NodeValue>
Sign qpn_edge_context_specific<NodeValue>::getSign()
	{
	std::cout<<std::endl<<"sign deb"<<std::endl;
	root->display();
	Sign sign = Sign::QMARK_SIGN;
	int motif_size = 0;
	//Calculate nodes in context
	std::list<std::string> context_nodes =std::list<std::string>();
	for(auto i_node = ordered_nNames.cbegin() ; i_node != ordered_nNames.cend() ; i_node++)
		{
		if((*(nodes[*i_node]))->isValObserved())
			context_nodes.push_back(*i_node);
		}

	findBestMotif(*root,context_nodes.cbegin(),context_nodes.cend(), sign, motif_size);

	std::cout<<std::endl<<"sign fin"<<std::endl;
	root->display();
	return sign;
	}

template <typename NodeValue>
Sign qpn_edge_context_specific<NodeValue>::getSign() const
	{
	std::cout<<std::endl<<"sign deb"<<std::endl;
	root->display();
	Sign sign = Sign::QMARK_SIGN;
	int motif_size = 0;
	//Calculate nodes in context
	std::list<std::string> context_nodes =std::list<std::string>();
	for(auto i_node = ordered_nNames.cbegin() ; i_node != ordered_nNames.cend() ; i_node++)
		{
		if((*(nodes.at(*i_node)))->isValObserved())
			context_nodes.push_back(*i_node);
		}

	findBestMotif(*root,context_nodes.cbegin(),context_nodes.cend(), sign, motif_size);

	std::cout<<std::endl<<"sign fin"<<std::endl;
	root->display();
	return sign;
	}


template <typename NodeValue>
std::ostream& qpn_edge_context_specific<NodeValue>::writeGraphVizFormat(std::ostream& os) const
	{
	os<<"label=\"";
	for (auto i_nName = ordered_nNames.cbegin(); i_nName!=ordered_nNames.cend();)
		{
		const std::string nName =(*(nodes.at(*i_nName)))->getName();
		os<<nName;

		if(++i_nName != ordered_nNames.cend())
			os<<std::endl;
		}
	os<<getSign()<<"\"";
	return os;
	}



template <typename NodeValue>
void qpn_edge_context_specific<NodeValue>::constructSuffixTree(suffix_tree<Sign>& tree, std::list<std::pair<std::string,bool>>::iterator i_nName, std::list<std::pair<std::string,bool>>::const_iterator cend, Sign sign, int motif_size)
	{

	std::string nName = i_nName->first;
	bool context_b = i_nName->second;

	//If the current node in the suffix tree doesn't have the specified desc
	if (! tree.hasDesc(nName, context_b))
		{
		//he's created
		tree.createDesc(nName, context_b);
		}
	//Descendant specified is catch
	suffix_tree<Sign>& desc = tree.getDesc(nName, context_b);
	//and is sign is changed if he's specified by a least longer motif
	if(++i_nName == cend)
		{
		desc.setValue(sign, motif_size);
		}
	else{
		//else recurse on the next elements in the context as descendant of the current suffix tree node
		constructSuffixTree(desc, i_nName, cend, sign, motif_size);
		}
	}

template <typename NodeValue>
void qpn_edge_context_specific<NodeValue>::findBestMotif(suffix_tree<Sign>& tree, std::list<std::string>::const_iterator i_nName, std::list<std::string>::const_iterator cend, Sign & sign, int& motif_size) const
	{

	//If current context explored has a value in suffix tree 
	if (tree.hasValue())
		{

		//Sign need to be compared to the best motif found. (longer is better)
		if (tree.getMotifSize() > motif_size)
			{
			sign = tree.getValue();
			motif_size = tree.getMotifSize();
			}
		}

	if(i_nName!=cend){
		qpn_node<NodeValue> node = *(*(nodes.at(*i_nName)));
		//If this context has been defined on the suffix tree
		if (tree.hasDesc(*i_nName, node.getValue()))
			{
			suffix_tree<Sign>& desc =tree.getDesc(*i_nName, node.getValue());
			i_nName++;
			findBestMotif(desc,i_nName,cend, sign, motif_size);
			//child associated to the context become the new root
			}
		else
			{
			//else suffix tree doesn't change
			findBestMotif(tree,++i_nName,cend,sign,motif_size);
			}
		}
	}



