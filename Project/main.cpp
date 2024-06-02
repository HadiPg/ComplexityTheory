#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

class Directed_Graph {
    int V;
    vector<int> *a;
    vector<vector<int>> biconnectedComponents;
public:
    Directed_Graph(int V) { //غزل معين احمد || وجد احمد حبيب
        this->V = V;
        a = new vector<int>[V];
    }

    void add_Edge(int x, int y) { //غدير بسام مسعود || فادي حنا بيطار || عمر محمد العلايا
        a[x].push_back(y);
        a[y].push_back(x);
    }

    void dfs_Algorithem(int u, int parent, stack<pair<int, int>> &edges, vector<int> &disc, vector<int> &low, vector<bool> &articulationPoint) { //عيسى رزوق || زينب حسون || هادي فوزي
        static int time = 0;
        disc[u] = low[u] = ++time;
        int children = 0;
        bool isArticulation = false;

        for (int v : a[u]) {
            if (v == parent) {
                continue;
            }

            if (disc[v] == -1) {
                children++;
                edges.push({u, v});
                dfs_Algorithem (v, u, edges, disc, low, articulationPoint);
                low[u] = min(low[u], low[v]);

                if ((parent == -1 && children > 1) || (parent != -1 && low[v] >= disc[u])) {
                    isArticulation = true;
                    vector<int> component;
                    while (edges.top() != make_pair(u, v)) {
                        component.push_back(edges.top().first);
                        component.push_back(edges.top().second);
                        edges.pop();
                    }
                    component.push_back(u);
                    component.push_back(v);
                    biconnectedComponents.push_back(component);
                    edges.pop();
                }
            } else {
                low[u] = min(low[u], disc[v]);
                if (disc[v] < disc[u]) {
                    edges.push({u, v});
                }
            }
        }

        if (parent == -1 && isArticulation) {
            vector<int> component;
            while (!edges.empty()) {
                component.push_back(edges.top().first);
                component.push_back(edges.top().second);
                edges.pop();
            }
            biconnectedComponents.push_back(component);
        }

        if (parent != -1 && isArticulation) {
            articulationPoint[u] = true;
        }
    }

    bool is_2_vertexStronglyBiconnected() {
        vector<int> disc(V, -1), low(V, -1);
        vector<bool> articulationPoint(V, false);
        stack<pair<int, int>> edges;

        int i = 0;
        while( i < V) {
            if (disc[i] == -1)
                dfs_Algorithem (i, -1, edges, disc, low, articulationPoint);
            i++;
        }

        return biconnectedComponents.size() > 0;
    }
};

int main() { // نغم حيدر || ودود سقر || مقداد اسد
    Directed_Graph g(4);
    g.add_Edge(0, 1);
    g.add_Edge(1, 2);
    g.add_Edge(2, 3);
    g.add_Edge(3, 0);

    if (g.is_2_vertexStronglyBiconnected()) {
        cout << "Graph is 2-vertex strongly biconnected." << endl;
    } else {
        cout << "Graph is not 2-vertex strongly biconnected." << endl;
    }

    return 0;
}
