#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H


namespace sdf
{
	template <typename T>
	class RedBlackTree
	{
		private:
			enum class Color
			{
				RED,
				BLACK
			};
			struct Node
			{
				Color color = Color::BLACK;
				T data;
				Node* left = nullptr;
				Node* right = nullptr;
				Node* parent = nullptr;
				explicit Node(const T &dat, const Color c = Color::BLACK) : color(c),data(dat){}
			};

		public:
			//节点是红色或黑色。
			//根是黑色。
			//所有叶子都是黑色（叶子是NULL节点）。
			//每个红色节点必须有两个黑色的子节点。（从每个叶子到根的所有路径上不能有两个连续的红色节点。）
			//从任一节点到其每个叶子的所有简单路径都包含相同数目的黑色节点（简称黑高）

			class Iterator;
			RedBlackTree() = default;
			~RedBlackTree();

			void insert(const T &val);
			void remove(const T &val);
			[[nodiscard]] Iterator find(const T &val) const;
			unsigned size() const;
			bool empty() const;

			class Iterator {
				public:
					explicit Iterator(Node* node = nullptr) : node_(node){}
					~Iterator() = default;

					T &operator*() const;
					T *operator->() const;
					Iterator &operator++();
					Iterator &operator--();
					bool operator==(const Iterator &other) const;
					bool operator!=(const Iterator &other) const;

				private:
					Node* node_;
			};

			Iterator begin() const;
			Iterator end() const;

		private:
			Node* root_ = nullptr;
			unsigned int size_ = 0;

			void destroyTheTree(Node* node);
			//传入参数时都是祖父，父，孩子的父节点
			void rightRotate(Node *node);
			void leftRotate(Node *node);
			void leftBalance(Node* node);
			void rightBalance(Node* node);
			static Color color(Node* node);
			void insertFixUp(Node* node);
			void removeFixUp(Node *parent, Node* node);
	};

	template<typename T>
	RedBlackTree<T>::~RedBlackTree() {
		destroyTheTree(root_);
	}

	template<typename T>
	void RedBlackTree<T>::insert(const T &val) {
		//根是黑色
		if (root_ == nullptr) {
			root_ = new Node(val, Color::BLACK);
			++size_;
			return;
		}
		Node *parent = nullptr;
		Node* node = root_;
		while (node != nullptr) {
			if (node->data > val) {
				parent = node;
				node = node->left;
			}
			else if (node->data < val) {
				parent = node;
				node = node->right;
			}
			else {
				//不插相同的值
				return;
			}
		}
		//退出，找到了叶子节点

		if (val < parent->data) {
			parent->left = new Node(val, Color::RED);
			++size_;
			node = parent->left;
			node->parent = parent;
		}
		else {
			parent->right = new Node(val, Color::RED);
			++size_;
			node = parent->right;
			node->parent = parent;
		}
		if (color(parent) == Color::RED) {
			insertFixUp(node);
		}
	}

	template<typename T>
	void RedBlackTree<T>::remove(const T &val) {
		if (root_ == nullptr) {
			return;
		}
		Node *node = root_;
		while (node != nullptr) {
			if (node->data == val) {
				if (node->left != nullptr && node->right != nullptr) {
					Node *prev = node->left;
					while (prev->right != nullptr) {
						prev = prev->right;
					}
					node->data = prev->data;
					node = prev;
				}

				if (node->left == nullptr && node->right == nullptr) {
					//没有孩子节点
					if (color(node) == Color::RED) {
						//红色节点，直接删，不用调整
						Node *parent = node->parent;
						if (parent != nullptr) {
							if (parent->left == node) {
								parent->left = nullptr;
							}
							else {
								parent->right = nullptr;
							}
						}
						if (node == root_) {
							root_ = nullptr;
						}
						delete node;
						node = nullptr;
						--size_;
					}
					else {
						//删除黑色没有孩子的节点，违背“黑路同”，准备做大量调整
						Node *parent = node->parent;
						if (parent != nullptr) {
							if (parent->left == node) {
								parent->left = nullptr;
							}
							else {
								parent->right = nullptr;
							}
						}
						if (node == root_) {
							root_ = nullptr;
						}
						delete node;
						node = nullptr;
						--size_;
						removeFixUp(parent, node);
					}
				}
				//只有左/右子树, 则node一定是黑色，且左右子树的节点一定是红色
				else{
					Node *child = node->left;
					if (child == nullptr) {
						child = node->right;
					}
					Node *parent = node->parent;
					child->parent = parent;
					if (parent) {
						if (parent->left == node) {
							parent->left = child;
						}
						else {
							parent->right = child;
						}
					}
					else {
						root_ = child;
					}
					delete node;
					node = nullptr;
					--size_;
					child->color = Color::BLACK;
					//只要替代后，然后孩子节点变黑即可
				}
			}
			else if (node->data < val) {
				node = node->right;
			}
			else {
				node = node->left;
			}
		}
		//退出，说明要删除的值不在里面
	}

	template<typename T>
	typename RedBlackTree<T>::Iterator RedBlackTree<T>::find(const T &val) const {
		Node *node = root_;
		while (node != nullptr) {
			if (node->data == val) {
				return Iterator(node);
			}

			if (node->data < val) {
				node = node->right;
			}
			else {
				node = node->left;
			}
		}
		return Iterator();
	}

	template<typename T>
	unsigned RedBlackTree<T>::size() const {
		return size_;
	}

	template<typename T>
	bool RedBlackTree<T>::empty() const {
		return root_ == nullptr;
	}

	template<typename T>
	T & RedBlackTree<T>::Iterator::operator*() const {
		return node_->data;
	}

	template<typename T>
	T * RedBlackTree<T>::Iterator::operator->() const {
		return &node_->data;
	}

	template<typename T>
	typename RedBlackTree<T>::Iterator & RedBlackTree<T>::Iterator::operator++() {
		if (node_->right != nullptr) {
			node_ = node_->right;
			while (node_->left != nullptr) {
				node_ = node_->left;
			}
		}
		else {
			while (node_->parent->right == node_) {
				node_ = node_->parent;
				if (node_->parent == nullptr) {
					node_ = nullptr;
					return *this;
				}
			}
			node_ = node_->parent;
		}
		return *this;
	}

	template<typename T>
	typename RedBlackTree<T>::Iterator & RedBlackTree<T>::Iterator::operator--() {
		if (node_->left != nullptr) {
			node_ = node_->left;
		}
		else {
			while (node_->parent->right == node_) {
				node_ = node_->parent;
			}
			node_ = node_->parent;
		}
		return *this;
	}

	template<typename T>
	bool RedBlackTree<T>::Iterator::operator==(const Iterator &other) const {
		return node_ == other.node_;
	}

	template<typename T>
	bool RedBlackTree<T>::Iterator::operator!=(const Iterator &other) const {
		return node_ != other.node_;
	}

	template<typename T>
	typename RedBlackTree<T>::Iterator RedBlackTree<T>::begin() const {
		Node *node = root_;
		while (node->left != nullptr) {
			node = node->left;
		}
		return Iterator(node);
	}

	template<typename T>
	typename RedBlackTree<T>::Iterator RedBlackTree<T>::end() const {
		return Iterator(nullptr);
	}

	template<typename T>
	void RedBlackTree<T>::destroyTheTree(Node *node) {
		if (node == nullptr) {
			return;
		}
		destroyTheTree(node->left);
		destroyTheTree(node->right);
		delete node;
		--size_;
	}

	template<typename T>
	void RedBlackTree<T>::rightRotate(Node *node) {
		Node* parent = node->parent;
		Node *grandparent = parent->parent;
		Node *child = node->right;
		if (grandparent) {
			if (grandparent->left == parent) {
				grandparent->left = node;
			}
			else {
				grandparent->right = node;
			}
		}
		else {
			root_ = node;
		}
		node->parent = grandparent;
		parent->parent = node;
		if (child) {
			child->parent = parent;
		}
		parent->left = child;
		node->right = parent;
	}

	template<typename T>
	void RedBlackTree<T>::leftRotate(Node *node) {
		Node* parent = node->parent;
		Node *grandparent = parent->parent;
		Node *child = node->left;
		if (grandparent) {
			if (grandparent->left == parent) {
				grandparent->left = node;
			}
			else {
				grandparent->right = node;
			}
		}
		else {
			root_ = node;
		}
		node->parent = grandparent;
		parent->parent = node;
		if (child) {
			child->parent = parent;
		}
		parent->right = child;
		node->left = parent;
	}

	template<typename T>
	void RedBlackTree<T>::leftBalance(Node *node) {
		leftRotate(node->right);
		rightRotate(node->parent);
	}

	template<typename T>
	void RedBlackTree<T>::rightBalance(Node *node) {
		rightRotate(node->left);
		leftRotate(node->parent);
	}

	template<typename T>
	typename RedBlackTree<T>::Color RedBlackTree<T>::color(Node *node) {
		if (node == nullptr) {
			return Color::BLACK;
		}
		return node->color;
	}

	template<typename T>
	void RedBlackTree<T>::insertFixUp(Node *node) {
		if (node == root_) {
			node->color = Color::BLACK;
			return;
		}

		Node *parent = node->parent;
		if (color(parent) == Color::BLACK) {
			return;
		}
		Node *grandparent = parent->parent;
		Node *uncle = grandparent->left == parent ? grandparent->right : grandparent->left;
		if (color(uncle) == Color::RED) {
			//则叔叔，父亲，爷爷变色，对爷爷做调整
			parent->color = Color::BLACK;
			uncle->color = Color::BLACK;
			grandparent->color = Color::RED;
			insertFixUp(grandparent);
		}
		else {
			//分情况讨论
			if (node == parent->left) {
				if (grandparent->left == parent) {
					//LL
					rightRotate(parent);
					parent->color = Color::BLACK;
					grandparent->color = Color::RED;
				}
				else {
					//RL
					rightBalance(parent);
					node->color = Color::BLACK;
					grandparent->color = Color::RED;
				}
			}
			else {
				if (grandparent->right == parent) {
					//RR
					leftRotate(parent);
					parent->color = Color::BLACK;
					grandparent->color = Color::RED;
				}
				else {
					//LR
					leftBalance(parent);
					node->color = Color::BLACK;
					grandparent->color = Color::RED;
				}
			}
		}
	}

	template<typename T>
	void RedBlackTree<T>::removeFixUp(Node *parent, Node *node) {
		if (parent == nullptr && node == nullptr) {
			return;
		}
		if (color(node) == Color::RED || node == root_) {
			node->color = Color::BLACK;
			return;
		}


		Node *brother = parent->right == node ? parent->left : parent->right;
		//兄弟是黑色
		if (color(brother) == Color::BLACK) {
			//至少有一个红色孩子
			if (color(brother->left) == Color::RED || color(brother->right) == Color::RED) {
				Node *red = nullptr;
				//根据parent,brother,red作LL,LR,RL,RR调整
				if (parent->left == brother) {
					//L
					//只要满足LL,那就优先考虑成为LL
					red = color(brother->left) == Color::RED ? brother->left : brother->right;
					if (red == brother->left) {
						//LL
						red->color = brother->color;
						brother->color = parent->color;
						parent->color = Color::BLACK;
						rightRotate(brother);
					}
					else {
						//LR
						red->color = parent->color;
						parent->color = Color::BLACK;
						leftBalance(brother);
					}
				}
				else {
					//R
					//只要满足RR,那就优先考虑成为RR
					red = color(brother->right) == Color::RED ? brother->right : brother->left;
					if (red == brother->left) {
						//RL
						red->color = parent->color;
						parent->color = Color::BLACK;
						rightBalance(brother);
					}
					else {
						//RR
						red->color = brother->color;
						brother->color = parent->color;
						parent->color = Color::BLACK;
						leftRotate(brother);
					}
				}
			}
			//兄弟的孩子都是黑色
			else {
				brother->color = Color::RED;
				removeFixUp(parent->parent, parent);
			}
		}
		//兄弟是红色
		else {
			if (node) {
				node->color = Color::BLACK;
			}
			parent->color = Color::RED == color(parent) ? Color::BLACK : Color::RED;
			brother->color = Color::RED == color(brother) ? Color::BLACK : Color::RED;
			if (node == parent->right) {
				rightRotate(brother);
			}
			else {
				leftRotate(brother);
			}
			removeFixUp(parent, node);
		}
	}
}

#endif // RED_BLACK_TREE_H
