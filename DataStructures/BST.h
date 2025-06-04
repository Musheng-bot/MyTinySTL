//
// Created by meish on 25-5-27.
//

#ifndef BITSET_H
#define BITSET_H

namespace sdf
{
    class BST
    {
        public:
            struct BST_Node
            {
                BST_Node* left = nullptr;
                BST_Node* right = nullptr;
                int data{};
                explicit BST_Node(int val) : data(val){}
            };
            using Node = BST_Node;

            BST();
            virtual ~BST();

            virtual void insert(int val);
            virtual void remove(int val);
            [[nodiscard]] bool find(int val) const;
            [[nodiscard]] unsigned long long height() const;
            [[nodiscard]] unsigned long long size() const;

            void preOrder() const;
            void inOrder() const;
            void postOrder() const;
            void levelOrder() const;

        protected:
            Node* root_ = nullptr;

            static void destroyTheBST(Node* node);
            static void preOrder(Node* node);
            static void inOrder(Node* node);
            static void postOrder(Node* node);
            static void levelOrder(Node* node,int i);
            static unsigned long long height(const Node* node);
    };

}

#endif //BITSET_H
