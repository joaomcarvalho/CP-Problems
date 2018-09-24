#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <cstring>
#include <climits>
#include <set>
#include <unordered_map>
#include <list>
#include <set>
#include <string>
#include <math.h>
#include <iomanip>
#include <string>
#include <string.h>
#include <limits.h>
#include <map>
#include <queue>

using namespace std;

#define INF 1000000100
// Usado para arestas com fluxo infinito (aumentar se necessário)
#define N 5010
// Coloque aqui um número maior que o maximo numero de nós no grafo

int nodes = N, ini, fim;
typedef long long ll;
int dist[N], work[N];

struct Edge {
    int to, rev, used_flow, cap;
};

vector < Edge > graph[N];

void addEdge(int from, int to, int cap) {
    Edge a = {to, (int)graph[to].size(), 0, cap};
    Edge b = {from, (int)graph[from].size(), 0, cap};
    // Se o fluxo for direcionado, alterar para Edge b = {from, graph[from].size(), 0, 0};
    graph[from].push_back(a);
    graph[to].push_back(b);
}

bool dinic_bfs() {
    fill(dist, dist + nodes, -1);
    dist[ini] = 0;

    queue < int > fila;
    fila.push(ini);

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        for (int i = 0; i < graph[u].size(); i++) {
            Edge &e = graph[u][i];
            int v = e.to;
            if (dist[v] < 0 && e.used_flow < e.cap) {
                dist[v] = dist[u] + 1;
                fila.push(v);
            }
        }
    }

    return dist[fim] >= 0;
}

int dinic_dfs(int u, int flow) {
    if (u == fim)
        return flow;

    for (int &i = work[u]; i < graph[u].size(); i++) {
        Edge &e = graph[u][i];

        if (e.cap > e.used_flow) {
            int v = e.to;

            if (dist[v] == dist[u] + 1) {
                int minf = dinic_dfs(v, min(flow, e.cap - e.used_flow));
                if (minf > 0) {
                    e.used_flow += minf;
                    graph[v][e.rev].used_flow -= minf;
                    return minf;
                }
            }
        }
    }

    return 0;
}

ll flow(int _ini, int _fim) {
    ini = _ini;
    fim = _fim;
    ll result = 0;

    while (dinic_bfs()) {
        fill(work, work + nodes, 0);
        while (int delta = dinic_dfs(ini, INT_MAX))
            result += delta;
    }

    return result;
}


int main() {
    int n, m;
    scanf("%d %d", &n, &m);


    int x, y, z;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &x, &y, &z);
        x--; y--;
        addEdge(x,y,z);
    }

    cout << flow(0, n - 1) << endl;
    return 0;
}
