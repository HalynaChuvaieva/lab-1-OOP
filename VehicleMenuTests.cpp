#include "Vehicle.h"
#include "BinarySearchTree.h"
#include "BalancedBST.h"
#include "AVLTree.h"
#include "Graph.h"
#include "UndirectedGraph.h"
#include "DirectedGraph.h"
#include "WeightedGraph.h"
#include "NegativeWeightedGraph.h"
using namespace std;

template
string captureOutput(Func f)
{
ostringstream buf;
streambuf *old = cout.rdbuf(buf.rdbuf());
f();
cout.rdbuf(old);
return buf.str();
}

void test_Vehicle_Comparison()
{
Vehicle v1("Audi", "A4", 2018);
Vehicle v2("Audi", "A6", 2018);
Vehicle v3("Audi", "A4", 2018);

assert(v1 < v2);
assert(v1 == v3);
assert(v2 > v1);
}

void test_BST_Insert()
{
BinarySearchTree bst;
bst.insert(Vehicle("Toyota", "Corolla", 2020));
bst.insert(Vehicle("BMW", "X5", 2021));
bst.insert(Vehicle("Audi", "A4", 2018));
string out = captureOutput([&]() { bst.display(); });
assert(out.find("Audi") < out.find("BMW"));
assert(out.find("BMW") < out.find("Toyota"));
}

void test_BalancedBST_Remove()
{
BalancedBST bst;
Vehicle v1("Ford", "Focus", 2019);
Vehicle v2("Ford", "Mondeo", 2020);
Vehicle v3("Ford", "Fiesta", 2018);
bst.insert(v1);
bst.insert(v2);
bst.insert(v3);
bst.remove(v2);
string out = captureOutput([&]() { bst.display(); });
assert(out.find("Mondeo") == string::npos);
assert(out.find("Focus") != string::npos);
assert(out.find("Fiesta") != string::npos);
}

void test_AVL_Height()
{
AVLTree avl;
avl.insert(Vehicle("Honda", "Civic", 2017));
avl.insert(Vehicle("Honda", "Accord", 2020));
avl.insert(Vehicle("Mazda", "3", 2019));
avl.insert(Vehicle("Mazda", "6", 2021));
int h = avl.getHeight();
assert(h >= 2 && h <= 4);
}

void test_UndirectedGraph_Vehicle()
{
UndirectedGraph g;
Vehicle v1("Toyota", "Corolla", 2020);
Vehicle v2("BMW", "X5", 2021);
Vehicle v3("Audi", "A4", 2018);

g.addEdge(v1, v2);
g.addEdge(v2, v3);
assert(!g.isCyclic());
g.addEdge(v3, v1);
assert(g.isCyclic());
}

void test_DirectedGraph_Vehicle()
{
DirectedGraph g;
Vehicle v1("Ford", "Focus", 2019);
Vehicle v2("Ford", "Fiesta", 2018);
Vehicle v3("Ford", "Mondeo", 2020);
g.addEdge(v1, v2);
g.addEdge(v2, v3);
assert(!g.isCyclic());
g.addEdge(v3, v1);
assert(g.isCyclic());
}

void test_WeightedGraph_Vehicle()
{
WeightedGraph g(3);
Vehicle v0("A", "A", 1);
Vehicle v1("B", "B", 2);
Vehicle v2("C", "C", 3);
g.addEdge(0, 1, 4);
g.addEdge(0, 2, 1);
g.addEdge(2, 1, 2);
string out = captureOutput([&]() { g.dijkstra(0); });
assert(out.find("0 : 0") != string::npos);
assert(out.find("1 : 3") != string::npos);
}

void test_NegativeWeightedGraph_Vehicle()
{
NegativeWeightedGraph g;
g.addEdge(0, 1, 2);
g.addEdge(1, 2, -5);
g.addEdge(0, 2, 4);

string out = captureOutput([&]() { g.bellmanFord(0); });
assert(out.find("0 : 0") != string::npos);
assert(out.find("2 : -3") != string::npos);
}

int main()
{
test_Vehicle_Comparison();
test_BST_Insert();
test_BalancedBST_Remove();
test_AVL_Height();
test_UndirectedGraph_Vehicle();
test_DirectedGraph_Vehicle();
test_WeightedGraph_Vehicle();
test_NegativeWeightedGraph_Vehicle();
cout << "ALL TESTS PASSED SUCCESSFULLY\n";
return 0;
}
