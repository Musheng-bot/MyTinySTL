//
// Created by meish on 25-5-27.
//

#ifndef AVL_H
#define AVL_H

#include "BST.h"

namespace sdf
{
    class AVL final : public BST
    {
        public:
            //任一节点的左右子树高度差不大于1
            AVL() = default;
            ~AVL() override = default;

            void insert(int val) override;
            void remove(int val) override;

        private:
            Node* insert(Node* root,int val);

            static Node* leftRotate(Node* root);
            static Node* rightBalance(Node* root);
            static Node* rightRotate(Node* root);
            static Node* leftBalance(Node* root);

            static Node* remove(Node* root, int val);
    };


}


#endif //AVL_H
