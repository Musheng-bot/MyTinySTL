//
// Created by meish on 25-5-27.
//

#include "BST.h"
#include <iostream>
#include <queue>
using namespace std;

sdf::BST::BST() = default;

sdf::BST::~BST()
{
	destroyTheBST(root_);
}

void sdf::BST::insert(int val)
{
	if (root_ == nullptr)
	{
		root_ = new Node(val);
		return;
	}
	Node* cur = root_;
	Node* parent = nullptr;
	int dir = 0;
	while (cur != nullptr) {
		if (cur->data == val)
		{
			//BST不插入相同的节点
			return;
		}
		parent = cur;
		if (cur ->data > val)
		{
			cur = cur->left;
			dir = -1;
		}
		else
		{
			cur = cur->right;
			dir = 1;
		}
	}
	if (dir == -1)
	{
		parent->left = new Node(val);
	}
	else if (dir == 1)
	{
		parent->right = new Node(val);
	}

}

void sdf::BST::remove(int val)
{
	if (root_ == nullptr)
	{
		return;
	}
	Node* cur = root_;
	Node* parent = nullptr;
	while (cur != nullptr)
	{
		if (cur->data < val)
		{
			parent = cur;
			cur = cur->right;
		}
		else if (cur -> data > val)
		{
			parent = cur;
			cur = cur->left;
		}
		else
		{
			//找到了对应的节点值
			//先处理左右子树都不为空的情况
			if (cur -> left != nullptr && cur->right != nullptr)
			{
				//找前驱节点
				Node* pre = cur->left;
				while (pre ->right != nullptr)
				{
					pre = pre->right;
				}
				//找到了前驱节点
				cur->data = pre->data;
				val = pre->data;
				parent = cur;
				cur = cur->left;
			}
			else if (cur->left == nullptr && cur->right == nullptr)
			{
				if (cur == root_)
				{
					delete root_;
					root_ = nullptr;
					cur = nullptr;
				}
				//直接删
				if (parent->left == cur)
				{
					delete cur;
					parent->left = nullptr;
				}
				else
				{
					delete cur;
					parent->right = nullptr;
				}
				cur = nullptr;
			}
			else
			{
				Node* next = cur->left ? cur->left : cur->right;
				if (cur == root_)
				{
					delete cur;
					cur = nullptr;
					root_ = next;
				}

				if (parent->left == cur)
				{
					parent->left = next;
				}
				else
				{
					parent->right = next;
				}
				delete cur;
				cur = nullptr;
			}
		}
	}

}

bool sdf::BST::find(int val) const
{
	Node* cur = root_;
	while (cur != nullptr)
	{
		if (cur ->data == val)
		{
			return true;
		}
		else if (cur->data < val)
		{
			cur = cur->right;
		}
		else if (cur->data > val)
		{
			cur = cur->left;
		}
	}
	return false;
}

unsigned long long sdf::BST::height() const
{
	if (root_ == nullptr)
	{
		return 0;
	}
	std::queue<Node*> que;
	que.emplace(root_);
	unsigned long long level = 0;
	int size = 1;
	while (!que.empty())
	{
		int next_size = 0;
		for (int i = 0; i < size; ++i)
		{
			Node* front = que.front();
			que.pop();
			if (front->left)
			{
				que.emplace(front->left);
				++next_size;
			}
			if (front->right)
			{
				que.emplace(front->right);
				++next_size;
			}

		}
		size = next_size;
		++level;
	}
	return level;
}

unsigned long long sdf::BST::size() const
{
	if (root_ == nullptr)
	{
		return 0;
	}
	std::queue<Node*> que;
	unsigned long long res = 1;
	que.emplace(root_);
	while (!que.empty())
	{
		Node* front = que.front();
		que.pop();
		if (front->left)
		{
			que.emplace(front->left);
			++res;
		}
		if (front->right)
		{
			que.emplace(front->right);
			++res;
		}
	}
	return res;
}

void sdf::BST::preOrder() const
{
	preOrder(root_);
}

void sdf::BST::inOrder() const
{
	inOrder(root_);
}

void sdf::BST::postOrder() const
{
	postOrder(root_);
}

void sdf::BST::levelOrder() const
{
	unsigned long long height = this->height();
	for (int i = 0; i < height; ++i)
	{
		levelOrder(root_, i);
	}
}

void sdf::BST::destroyTheBST(Node* node)
{
	if (node == nullptr)
	{
		return;
	}
	destroyTheBST(node->left);
	destroyTheBST(node->right);
	delete node;
	node = nullptr;
}

void sdf::BST::preOrder(Node* node)
{
	if (node == nullptr)
	{
		return;
	}
	if (node->left)
		preOrder(node->left);

	cout << node->data << ' ';

	if (node->right)
		preOrder(node->right);
}

void sdf::BST::inOrder(Node* node)
{
	if (node == nullptr)
	{
		return;
	}
	cout << node->data << ' ';
	inOrder(node->left);
	inOrder(node->right);
}

void sdf::BST::postOrder(Node* node)
{
	if (node == nullptr)
	{
		return;
	}
	postOrder(node->left);
	postOrder(node->right);
	cout << node->data << ' ';
}

void sdf::BST::levelOrder(Node* node, int i)
{
	if (node == nullptr)
	{
		return;
	}
	if (i == 0)
	{
		cout << node->data << ' ';
	}
	levelOrder(node->left, i - 1);
	levelOrder(node->right, i - 1);
}

unsigned long long sdf::BST::height(const Node* node)
{
	if (node == nullptr)
	{
		return 0;
	}
	return std::max(height(node->left), height(node->right)) + 1;
}
