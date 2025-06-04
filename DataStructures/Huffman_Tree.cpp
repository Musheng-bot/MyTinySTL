#include "Huffman_Tree.h"

#include <iostream>
#include <queue>
using namespace std;


sdf::Huffman_Tree::Huffman_Tree() :
	min_heap_([](Node* a, Node* b) { return a->weight > b->weight;})
{}

sdf::Huffman_Tree::~Huffman_Tree()
{
	destroyTheTree(root_);
}

void sdf::Huffman_Tree::createTree(std::string str)
{
	std::unordered_map<char, int> fre_map;
	for (auto i : str)
	{
		fre_map[i]++;
	}
	for (const auto& i : fre_map)
	{
		min_heap_.emplace(new Node(i.first, i.second));
	}

	while (min_heap_.size() > 1)
	{
		Node* n1 = min_heap_.top();
		min_heap_.pop();

		Node* n2 = min_heap_.top();
		min_heap_.pop();

		auto node = new Node('\0', n1->weight + n2->weight);
		node->left = n1;
		node->right = n2;
		min_heap_.emplace(node);
	}
	root_ = min_heap_.top();
	min_heap_.pop();
	showHuffmanCode(root_, string());
}

void sdf::Huffman_Tree::showHuffmanCode()
{
	for (auto &pair : code_map_)
	{
		cout << pair.first << " : " << pair.second << '\n';
	}
	cout << endl;
}

std::string sdf::Huffman_Tree::encode(const std::string &str)
{
	string res;
	for (auto i : str)
	{
		res += code_map_[i];
	}
	return res;
}

std::string sdf::Huffman_Tree::decode(const std::string& str)
{
	string res;
	Node* cur = root_;
	for (auto ch : str)
	{
		if (ch == '0')
		{
			cur = cur->left;
		}
		else
		{
			cur = cur->right;
		}
		if (cur->left == nullptr && cur->right == nullptr)
		{
			res += cur->data;
			cur = root_;
		}
	}
	return res;
}

void sdf::Huffman_Tree::destroyTheTree(Node* node)
{
	if (node == nullptr)
	{
		return;
	}
	auto left = node->left;
	auto right = node->right;
	delete node;
	destroyTheTree(left);
	destroyTheTree(right);
}

void sdf::Huffman_Tree::showHuffmanCode(Node* node, std::string code)
{
	//VLR
	if (node->left == nullptr && node->right == nullptr)
	{
		code_map_[node->data] = code;
		return;
	}
	showHuffmanCode(node->left,code + "0");
	showHuffmanCode(node->right, code + "1");
}
