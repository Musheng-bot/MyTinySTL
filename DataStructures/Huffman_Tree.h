#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H
#include <functional>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

namespace sdf
{
	class Huffman_Tree
	{
	public:
		struct Huffman_Tree_Node
		{
			char data;
			int weight;
			Huffman_Tree_Node* left = nullptr;
			Huffman_Tree_Node* right = nullptr;
			Huffman_Tree_Node(char ch,int w): data(ch),weight(w){}
		};
		using Node = Huffman_Tree_Node;

		Huffman_Tree();
		~Huffman_Tree();

		void createTree(std::string str);
		void showHuffmanCode();

		std::string encode(const std::string &str);
		std::string decode(const std::string& str);

		

	private:
		Node* root_ = nullptr;
		std::unordered_map<char, std::string> code_map_;

		using MinHeap = std::priority_queue<Node*, std::vector<Node*>, std::function<bool(Node*,Node*)>>;
		MinHeap min_heap_;

		void destroyTheTree(Node* node);
		void showHuffmanCode(Node* node, std::string code);
	};
}

#endif // HUFFMAN_TREE_H
