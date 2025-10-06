#include <iostream>
using namespace std;
#include "BinarySearchTree.h"
template <class T>
class BalancedBST : public BinarySearchTree<T>
{
protected:
    struct HeightNode : public BinarySearchTree<T>::Node
    {
        int height;
        HeightNode(T val) : BinarySearchTree<T>::Node(val), height(1) {}
    };

    int height(HeightNode *node)
    {
        return node ? node->height : 0;
    }

    virtual void insert(T value) = 0;

public:
    BalancedBST() : BinarySearchTree<T>() {}
    virtual ~BalancedBST() {}

    int getHeight()
    {
        return getHeight(static_cast<HeightNode *>(this->root));
    }

private:
    int getHeight(HeightNode *node)
    {
        if (!node)
            return 0;
        return max(getHeight(static_cast<HeightNode *>(node->left)),
                   getHeight(static_cast<HeightNode *>(node->right))) +
               1;
    }
};