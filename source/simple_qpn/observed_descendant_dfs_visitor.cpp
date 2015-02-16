#include "../../header/simple_qpn/observed_descendant_dfs_visitor.h"



template<class Vertex, class Graph>
void observed_descendant_dfs_visitor::discover_vertex(Vertex v, const Graph& g) const
	{
	if(get(vertex_bundle,g, v).value !=-1)
		hasDescendant =true;
	}

observed_descendant_dfs_visitor::observed_descendant_dfs_visitor():hasDescendant(false){}

