#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H
#include <list>
#include <string>
#include <unordered_map>
#include <utility>

namespace sdf
{
	class AdjacencyList
	{
		struct Node
		{
			std::string data;
			std::list<int> in;
			std::list<int> out;
			explicit Node(std::string d) : data(std::move(d))
			{
			}
		};
	public:
		AdjacencyList();
		~AdjacencyList();

		void addNode(std::string data);
		void link(int in, int out);
		void erase(int node);

		void showLink() const;
		std::size_t inDegree(int node);
		std::size_t outDegree(int node);



	private:
		std::unordered_map<int, Node*> node_map_;
		int node_count_ = 1;
	};
}
#endif // ADJACENCYLIST_H
