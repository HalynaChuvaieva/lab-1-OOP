#pragma once
#include <iostream>
#include "BalancedBST.h"
using namespace std;

template <class T>
class AVLTree : public BalancedBST<T>
{
    using HeightNode = typename BalancedBST<T>::HeightNode;

public:
    AVLTree() : BalancedBST<T>() {}

protected:
    void insert(T value) override
    {
        this->root = insertNode(static_cast<HeightNode *>(this->root), value);
    }

private:
    HeightNode *insertNode(HeightNode *node, T value)
    {
        if (!node)
            return new HeightNode(value);

        if (value < node->value)
            node->left = insertNode(static_cast<HeightNode *>(node->left), value);
        else if (value > node->value)
            node->right = insertNode(static_cast<HeightNode *>(node->right), value);
        else
            return node;

        node->height = 1 + max(this->height(static_cast<HeightNode *>(node->left)),
                               this->height(static_cast<HeightNode *>(node->right)));

        int balance = getBalance(node);

        if (balance > 1 && value < node->left->value)
            return rotateRight(node);

        if (balance < -1 && value > node->right->value)
            return rotateLeft(node);

        if (balance > 1 && value > node->left->value)
        {
            node->left = rotateLeft(static_cast<HeightNode *>(node->left));
            return rotateRight(node);
        }

        if (balance < -1 && value < node->right->value)
        {
            node->right = rotateRight(static_cast<HeightNode *>(node->right));
            return rotateLeft(node);
        }

        return node;
    }

    int getBalance(HeightNode *node)
    {
        if (!node)
            return 0;
        return this->height(static_cast<HeightNode *>(node->left)) -
               this->height(static_cast<HeightNode *>(node->right));
    }

    HeightNode *rotateRight(HeightNode *y)
    {
        HeightNode *x = static_cast<HeightNode *>(y->left);
        HeightNode *T2 = static_cast<HeightNode *>(x->right);

        x->right = y;
        y->left = T2;

        y->height = 1 + max(this->height(static_cast<HeightNode *>(y->left)),
                            this->height(static_cast<HeightNode *>(y->right)));
        x->height = 1 + max(this->height(static_cast<HeightNode *>(x->left)),
                            this->height(static_cast<HeightNode *>(x->right)));

        return x;
    }

    HeightNode *rotateLeft(HeightNode *x)
    {
        HeightNode *y = static_cast<HeightNode *>(x->right);
        HeightNode *T2 = static_cast<HeightNode *>(y->left);

        y->left = x;
        x->right = T2;

        x->height = 1 + max(this->height(static_cast<HeightNode *>(x->left)),
                            this->height(static_cast<HeightNode *>(x->right)));
        y->height = 1 + max(this->height(static_cast<HeightNode *>(y->left)),
                            this->height(static_cast<HeightNode *>(y->right)));

        return y;
    }
};