#pragma once
#include <boost/graph/depth_first_search.hpp>


class observed_descendant_dfs_visitor :public boost::default_dfs_visitor
	{
	public:
		observed_descendant_dfs_visitor();
		template<class Vertex, class Graph>
		void discover_vertex(Vertex v, const Graph& g) const;

		bool hasDescendant;
	};

