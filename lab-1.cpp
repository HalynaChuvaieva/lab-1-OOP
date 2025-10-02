#include <iostream>
#include "Graph.h"
#include "BinarySearchTree.h"
using namespace std;

void menu() {
    int mainChoice;
    do {
        cout << "\nMAIN MENU\n";
        cout << "1. Binary Search Tree\n";
        cout << "2. Balanced BST\n";
        cout << "3. AVL Tree\n";
        cout << "4. Graph\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
        case 1: {
            BinarySearchTree<int> bst;
            int choice;
            do {
                cout << "\nBINARY SEARCH TREE MENU\n";
                cout << "1. Insert\n";
                cout << "2. Remove\n";
                cout << "3. Display\n";
                cout << "0. Back\n";
                cout << "Choice: ";
                cin >> choice;
                if (choice == 1) { int val; cout << "Value: "; cin >> val; bst.insert(val); }
                else if (choice == 2) { int val; cout << "Value: "; cin >> val; bst.remove(val); }
                else if (choice == 3) bst.display();
            } while (choice != 0);
            break;
        }
        case 2: {
            BalancedBST<int> bst;
            int choice;
            do {
                cout << "\nBALANCED BST MENU\n";
                cout << "1. Insert\n";
                cout << "2. Remove\n";
                cout << "3. Display\n";
                cout << "4. Get height\n";
                cout << "0. Back\n";
                cout << "Choice: ";
                cin >> choice;
                if (choice == 1) { int val; cout << "Value: "; cin >> val; bst.insert(val); }
                else if (choice == 2) { int val; cout << "Value: "; cin >> val; bst.remove(val); }
                else if (choice == 3) bst.display();
                else if (choice == 4) cout << "Height: " << bst.getHeight() << endl;
            } while (choice != 0);
            break;
        }
        case 3: {
            AVLTree<int> avl;
            int choice;
            do {
                cout << "\nAVL TREE MENU\n";
                cout << "1. Insert\n";
                cout << "2. Display\n";
                cout << "0. Back\n";
                cout << "Choice: ";
                cin >> choice;
                if (choice == 1) { int val; cout << "Value: "; cin >> val; avl.insert(val); }
                else if (choice == 2) avl.display();
            } while (choice != 0);
            break;
        }
        case 4: {
            int graphType;
            cout << "\nGRAPH MENU\n";
            cout << "1. Undirected Graph\n";
            cout << "2. Directed Graph\n";
            cout << "3. Weighted Graph\n";
            cout << "4. Negative Weighted Graph\n";
            cout << "Choice: ";
            cin >> graphType;

            int n, m;
            cout << "Enter number of vertices: "; cin >> n;
            cout << "Enter number of edges: "; cin >> m;

            if (graphType == 1) {
                UndirectedGraph g(n);
                cout << "Enter edges (u v):\n";
                for (int i = 0; i < m; i++) { int u,v; cin >> u >> v; g.addEdge(u,v); }
                g.buildSpanningTree();
                cout << "Cyclic? " << (g.isCyclic() ? "Yes\n" : "No\n");
            }
            else if (graphType == 2) {
                DirectedGraph g(n);
                cout << "Enter edges (u v):\n";
                for (int i = 0; i < m; i++) { int u,v; cin >> u >> v; g.addEdge(u,v); }
                g.buildSpanningTree();
                cout << "Cyclic? " << (g.isCyclic() ? "Yes\n" : "No\n");
            }
            else if (graphType == 3) {
                WeightedGraph g(n);
                cout << "Enter edges (u v w):\n";
                for (int i = 0; i < m; i++) { int u,v,w; cin >> u >> v >> w; g.addEdge(u,v,w); }
                g.dijkstra(0);
            }
            else if (graphType == 4) {
                NegativeWeightedGraph g(n);
                cout << "Enter edges (u v w):\n";
                for (int i = 0; i < m; i++) { int u,v,w; cin >> u >> v >> w; g.addEdge(u,v,w); }
                g.bellmanFord(0);
            }

            break;
        }
        }
    } while (mainChoice != 0);
}

int main() {
    menu();
    return 0;
}

