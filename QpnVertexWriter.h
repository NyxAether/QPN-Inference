#pragma once
template <class Name>
class QpnVertexWriter
	{
	public:

		QpnVertexWriter(Name _name) : name(_name)
			{
			}


		template <class Vertex>
		void operator()(std::ostream& out, const Vertex& v) const {
			out << "[label=\"" << get(vertex_bundle,name,v).sign<< "\"]";
			}
	private:
		Name name;
	};

