//
// Created by meish on 25-5-27.
//
#include "AVL.h"

#include <cmath>
#include <ios>

void sdf::AVL::insert(int val)
{
	root_ = insert(root_, val);
}

void sdf::AVL::remove(int val)
{
	root_ = remove(root_, val);
}

sdf::BST::Node* sdf::AVL::insert(Node* root,int val)
{
	//返回生成的树的根节点
	if (root == nullptr)
	{
		return new Node(val);
	}
	if (root->data == val)
	{
		return root;
	}
	if (root->data < val)
	{
		root->right = insert(root->right, val);
		//右边插入节点，则有可能右子树失衡
		if (abs(static_cast<int>(height(root->left)) - static_cast<int>(height(root->right))) <= 1)
		{
			//依旧平衡
			return root;
		}
		//右子树失衡
		Node* right = root->right;
		if (height(right->right) > height(right->left))
		{
			//右孩子的右子树失衡了
			return leftRotate(root);
		}
		//右孩子的左孩子失衡了
		return rightBalance(root);


	}
	root->left = insert(root->left, val);
	Node* left = root->left;
	if (abs(static_cast<int>(height(root->left)) - static_cast<int>(height(root->right))) <= 1)
	{
		//依旧平衡
		return root;
	}
	if (height(left->right) > height(left->left))
	{
		return leftBalance(root);
	}
	return rightRotate(root);
}

sdf::BST::Node* sdf::AVL::leftRotate(Node* root)
{
	//左旋转操作
	Node* child = root->right;
	Node* grandchild = child->left;
	child->left = root;
	root->right = grandchild;

	return child;
}

sdf::BST::Node *sdf::AVL::rightBalance(Node* root)
{
	root->right = rightRotate(root->right);
	return leftRotate(root);
}

sdf::BST::Node* sdf::AVL::rightRotate(Node* root)
{
	Node* child = root->left;
	Node* grandchild = child->right;
	root->left = grandchild;
	child->right = root;

	return child;
}

sdf::BST::Node* sdf::AVL::leftBalance(Node* root)
{
	root->left = leftRotate(root->left);
	return rightRotate(root);
}

sdf::AVL::Node* sdf::AVL::remove(Node* root, int val)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	if (root->data == val)
	{
		if (root->left != nullptr && root->right != nullptr)
		{
			//转化为情况1，2
			Node* pre = root->left;
			while (pre->right != nullptr)
			{
				pre = pre->right;
			}
			root->data = pre->data;
			root->left = remove(root->left, root->data);
		}
		else if (root ->left == nullptr &&root->right == nullptr)
		{
			delete root;
			root = nullptr;
			return nullptr;
		}
		else
		{
			return root->left ? root->left : root->right;
		}
	}
	else if (root->data < val)
	{
		root->right = remove(root->right, val);

		if (abs(static_cast<int>(height(root->right)) - static_cast<int>(height(root->left))) <= 1)
		{
			//依旧平衡
			return root;
		}

		Node* left = root->left;
		if (height(left->right) > height(left->left))
		{
			//左孩子的右子树失衡了
			return leftBalance(root);
		}
		//左孩子的左孩子失衡了
		return rightRotate(root);

	}
	root->left = remove(root->left, val);
	if (abs(static_cast<int>(height(root->left)) - static_cast<int>(height(root->right))) <= 1)
	{
		//依旧平衡
		return root;
	}
	Node* right = root->right;
	if (height(right->right) > height(right->left))
	{
		//右孩子的右子树失衡
		return leftRotate(root);
	}
	//右孩子的左子树失衡
	return rightBalance(root);

}

