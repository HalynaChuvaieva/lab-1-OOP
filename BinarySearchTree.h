#pragma once
#include <iostream>
using namespace std;

template <class T>
class BinarySearchTree
{
protected:
    struct Node
    {
        T key;
        Node *left;
        Node *right;
        Node(T val) : key(val), left(nullptr), right(nullptr) {}
    };
    Node *root;

    virtual Node *insert(Node *node, T key)
    {
        if (!node)
            return new Node(key);
        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        return node;
    }

    Node *minValue(Node *node)
    {
        Node *current = node;
        while (current && current->left)
            current = current->left;
        return current;
    }

    Node *deleteNode(Node *node, T key)
    {
        if (!node)
            return node;
        if (key < node->key)
            node->left = deleteNode(node->left, key);
        else if (key > node->key)
            node->right = deleteNode(node->right, key);
        else
        {
            if (!node->left)
            {
                Node *temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right)
            {
                Node *temp = node->left;
                delete node;
                return temp;
            }
            Node *temp = minValue(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);
        }
        return node;
    }

    void inorder(Node *node)
    {
        if (node)
        {
            inorder(node->left);
            cout << node->key << " ";
            inorder(node->right);
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    virtual void insert(T key) { root = insert(root, key); }
    void remove(T key) { root = deleteNode(root, key); }
    void display()
    {
        inorder(root);
        cout << endl;
    }
};

template <class T>
class BalancedBST : public BinarySearchTree<T>
{
protected:
    struct Node : public BinarySearchTree<T>::Node
    {
        int height;
        Node(T val) : BinarySearchTree<T>::Node(val), height(1) {}
    };

    int height(Node *node)
    {
        return node ? node->height : 0;
    }

public:
    BalancedBST() : BinarySearchTree<T>() {}
    int getHeight()
    {
        return getHeight(static_cast<Node *>(this->root));
    };
private:
    int getHeight(Node* node) {
        if (!node) return 0;
        return max(getHeight(static_cast<Node*>(node->left)),
                   getHeight(static_cast<Node*>(node->right))) + 1;
    }
};

template <class T>
class AVLTree : public BalancedBST<T>
{
protected:
    using Node = typename BalancedBST<T>::Node;

    int getBalance(Node *node)
    {
        if (!node)
            return 0;
        return height(node->left) - height(node->right);
    }

    Node *rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Node *insert(Node *node, T key) override
    {
        if (!node)
            return new Node(key);

        if (key < node->key)
            node->left = insert(static_cast<Node *>(node->left), key);
        else if (key > node->key)
            node->right = insert(static_cast<Node *>(node->right), key);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate(static_cast<Node *>(node->left));
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(static_cast<Node *>(node->right));
            return leftRotate(node);
        }

        return node;
    }

public:
    AVLTree() : BalancedBST<T>() {}
    void insert(T key) override { this->root = insert(static_cast<Node *>(this->root), key); }
};
