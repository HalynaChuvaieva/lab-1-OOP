#include "Vehicle.h"
#include "BinarySearchTree.h"
#include "BalancedBST.h"
#include "AVLTree.h"
#include <cassert>
#include <iostream>
using namespace std;

void test_BST_Insert_Display()
{
    cout << "Running test_BST_Insert_Display..." << endl;
    BinarySearchTree<Vehicle> bst;
    Vehicle v1("Toyota", "Corolla", 2020);
    Vehicle v2("BMW", "X5", 2021);
    Vehicle v3("Audi", "A4", 2018);

    bst.insert(v1);
    bst.insert(v2);
    bst.insert(v3);

    cout << "Expected order: Audi -> BMW -> Toyota\n";
    bst.display();
    cout << "Test passed (manual visual check)\n\n";
}

void test_BalancedBST_Remove()
{
    cout << "Running test_BalancedBST_Remove..." << endl;
    BalancedBST<Vehicle> bst;
    Vehicle v1("Ford", "Focus", 2019);
    Vehicle v2("Ford", "Mondeo", 2020);
    Vehicle v3("Ford", "Fiesta", 2018);

    bst.insert(v1);
    bst.insert(v2);
    bst.insert(v3);

    bst.remove(v2);
    cout << "Removed Ford Mondeo (2020)\n";
    bst.display();
    cout << "Test passed (manual visual check)\n\n";
}

void test_AVL_Height()
{
    cout << "Running test_AVL_Height..." << endl;
    AVLTree<Vehicle> avl;
    avl.insert(Vehicle("Honda", "Civic", 2017));
    avl.insert(Vehicle("Honda", "Accord", 2020));
    avl.insert(Vehicle("Mazda", "3", 2019));
    avl.insert(Vehicle("Mazda", "6", 2021));

    int height = avl.getHeight();
    cout << "AVL height = " << height << endl;
    assert(height > 0);
    cout << "Test passed \n";
}
void test_Vehicle_Comparison()
{
    cout << "Running test_Vehicle_Comparison..." << endl;
    Vehicle v1("Audi", "A4", 2018);
    Vehicle v2("Audi", "A6", 2018);
    Vehicle v3("Audi", "A4", 2018);

    assert(v1 < v2);
    assert(v1 == v3);
    assert(v2 > v1);
    cout << "Test passed \n";
}

int main()
{
    test_Vehicle_Comparison();
    test_BST_Insert_Display();
    test_BalancedBST_Remove();
    test_AVL_Height();

    cout << "All Vehicle-related menu function tests completed.\n";
    return 0;
}
