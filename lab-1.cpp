#include <iostream>
#include <vector>
using namespace std;
class BinarySearchTree {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        Node(int val) : key(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);

        return node;
    }

    Node* minValue(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* node, int key) {
        if (!node) return node;

        if (key < node->key)
            node->left = deleteNode(node->left, key);
        else if (key > node->key)
            node->right = deleteNode(node->right, key);
        else {
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = minValue(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);
        }
        return node;
    }

    void inorder(Node* node) {
        if (node) {
            inorder(node->left);
            cout << node->key << " ";
            inorder(node->right);
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }
    void remove(int key) {
        root = deleteNode(root, key);
    }
    void display() {
        cout << "Дерево: ";
        inorder(root);
        cout << endl;
    }
};

class Graph {
private:
    int n;  
    vector<vector<int>> adj; 
    vector<bool> visited;
    vector<pair<int, int>> spanningTree; 

    void dfs(int v) {
        visited[v] = true;
        for (int u : adj[v]) {
            if (!visited[u]) {
                spanningTree.push_back({ v, u });
                dfs(u);
            }
        }
    }

public:
    Graph(int vertices) {
        n = vertices;
        adj.assign(n, {});
        visited.assign(n, false);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void buildSpanningTree(int start = 0) {
        spanningTree.clear();
        fill(visited.begin(), visited.end(), false);

        dfs(start);

        cout << "Кістякове дерево складається з ребер:\n";
        for (pair<int, int> e : spanningTree) {
            cout << e.first << " - " << e.second << endl;
        }
    }
};

int main() {
    setlocale(LC_CTYPE, "ukr");
    BinarySearchTree bst;
    int choice;

    while (choice!=0){
        cout << "1. Додати елемент у бінарне дерево\n";
        cout << "2. Видалити елемент з дерева\n";
        cout << "3. Вивести дерево\n";
        cout << "4. Побудувати кістякове дерево графа\n";
        cout << "0. Вихід\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        if (choice == 1) {
            int val;
            cout << "Введіть значення: ";
            cin >> val;
            bst.insert(val);
        }
        else if (choice == 2) {
            int val;
            cout << "Введіть значення для видалення: ";
            cin >> val;
            bst.remove(val);
        }
        else if (choice == 3) {
            bst.display();
        }
        else if (choice == 4) {
            int n, m;
            cout << "Введіть кількість вершин графа: ";
            cin >> n;
            cout << "Введіть кількість ребер: ";
            cin >> m;

            Graph g(n);
            cout << "Введіть ребра (u v):\n";
            for (int i = 0; i < m; i++) {
                int u, v;
                cin >> u >> v;
                g.addEdge(u, v);
            }
            g.buildSpanningTree(0);
        }
    } 
    return 0;
}

