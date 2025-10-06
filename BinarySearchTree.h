#pragma once
#include <iostream>
#include "BalancedBST.h"
#include "AVLTree.h"
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
