#ifndef BTREE_H
#define BTREE_H
#include <vector>

namespace sdf {

template<class T,unsigned order>
class BTree {
    public:
        BTree();
        ~BTree();

        class Node {
            public:
                Node(){
                    children_.emplace_back(nullptr);
                }

                ~Node() {
                    for (auto child : children_) {
                        delete child;
                    }
                    children_.clear();
                    values_.clear();
                }

                //返回值标志着是否有层高的变化
                bool insert(T &&val) {
                    if (children_.size() == order) {
                        for (auto child : children_) {
                            if (child != nullptr) {
                                child->insert(std::forward<T>(val));
                            }
                        }
                    }
                    else {
                        auto it = std::lower_bound(values_.begin(), values_.end().end(), val);
                        if (*it == val) {
                            return false;
                        }
                        children_.emplace(transformIterator(it), std::forward<T>(val));
                        values_.emplace(it, std::forward<T>(val));
                    }
                }
            private:
                std::vector<Node*> children_;
                std::vector<T> values_;

                //返回的是指向children中我们传入的it指向数据的后一个指针
                auto transformIterator(decltype(values_.begin())  it) {
                    return it - values_.begin() + children_.begin() + 1;
                }
        };

        bool insert(T &&value);
        bool remove(T &&value);
        [[nodiscard]] bool find(T &&value) const;

    private:
        Node *root_;
        //const int order_ = _order; //阶数
        int size_ = 0; //元素个数
        int level_ = 0; //层数
        //void destroyTree(Node *node);
        bool insertTree(Node *node, const T &value);
};

template<class T, unsigned order>
BTree<T, order>::BTree() {
    root_ = nullptr;
}

template<class T, unsigned order>
BTree<T, order>::~BTree() {
    delete root_;
}

template<class T, unsigned order>
bool BTree<T, order>::insert(T &&value) {
    if (root_ == nullptr) {
        root_ = new Node();
    }
}
} // sdf

#endif //BTREE_H
