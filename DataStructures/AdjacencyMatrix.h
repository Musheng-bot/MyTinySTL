#ifndef ADJACENCY_MATRIX_H
#define ADJACENCY_MATRIX_H
#include <string>
#include <unordered_map>
#include <vector>

namespace sdf
{
	class AdjacencyMatrix final
	{
	public:
		AdjacencyMatrix() = default;
		~AdjacencyMatrix() = default;

		void addNode(std::string data)
		{
			data_map_[count_] = std::move(data);
			for (auto &vec : matrix_)
			{
				vec.emplace_back(false);
			}
			matrix_.emplace_back(count_, false);
			++count_;
		}
		void link(int begin, int end)
		{
			matrix_[begin-1][end-1] = true;
		}

	private:
		std::unordered_map<int, std::string> data_map_;
		std::vector<std::vector<bool>> matrix_;

		int count_ = 1;
	};
}

#endif // ADJACENCY_MATRIX_H
