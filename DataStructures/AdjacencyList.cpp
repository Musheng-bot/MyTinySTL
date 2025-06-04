#include "AdjacencyList.h"
#include <iostream>
using std::cout;

namespace sdf
{
	AdjacencyList::AdjacencyList() = default;

	AdjacencyList::~AdjacencyList()
	{
		for (auto& pair : node_map_)
		{
			delete pair.second;
			pair.second = nullptr;
		}
	}

	void AdjacencyList::addNode(std::string data)
	{
		node_map_[node_count_] = new Node(std::move(data));
		++node_count_;
	}

	void AdjacencyList::link(int in, int out)
	{
		node_map_[in]->out.emplace_back(out);
		node_map_[out]->in.emplace_back(in);
	}

	void AdjacencyList::erase(int node)
	{
		Node* n = node_map_[node];
		for (auto p :n->in)
		{
			node_map_[p]->out.remove(node);
		}
		for (auto p : n->out)
		{
			node_map_[p]->in.remove(node);
		}
	}

	void AdjacencyList::showLink() const
	{
		for (auto& pair : node_map_)
		{
			if (pair.second->out.empty())
			{
				return;
			}
			cout << pair.first << "is linked with nodes ";
			for (auto node : pair.second->out)
			{
				cout << node << ' ';
			}
			cout << '\n';
		}
		cout << std::flush;
	}

	std::size_t AdjacencyList::inDegree(const int node)
	{
		return node_map_[node]->in.size();
	}

	std::size_t AdjacencyList::outDegree(const int node)
	{
		return node_map_[node]->out.size();
	}
}
