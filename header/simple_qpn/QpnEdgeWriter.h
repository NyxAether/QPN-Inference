#pragma once
template <class Name>
class QpnEdgeWriter
	{
	public:

		QpnEdgeWriter(Name _name) : name(_name)
			{
			}


		template <class VertexOrEdge>
		void operator()(std::ostream& out, const VertexOrEdge& v) const {
			out << "[label=\"" << name[v] << "\"]";
			}
	private:
		Name name;
	};

