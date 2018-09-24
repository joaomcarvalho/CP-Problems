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

#define INF 100010
// Usado para arestas com fluxo infinito (aumentar se necessário)
#define N 10010
// Coloque aqui um número maior que o maximo numero de nós no grafo

int nodes = N, ini, fim;
typedef long long ll;
int dist[N], work[N];

struct Edge {
    int to, rev, used_flow, cap;
};

int in[N];
int out[N];

vector < Edge > graph[N];

void addEdge(int from, int to, int cap) {

    //out[x - 1], in[y - 1], z

    Edge a = {to, (int)graph[to].size(), 0, cap};
    Edge b = {from, (int)graph[from].size(), 0, 0};
    //Edge b = {from, (int)graph[from].size(), 0, cap};
    // Se o fluxo for direcionado, alterar para Edge b = {from, graph[from].size(), 0, 0};
    graph[from].push_back(a);
    graph[to].push_back(b);
}

void addEdge2(int from, int to, int cap) {

    //out[x - 1], in[y - 1], z

    Edge in_to = {in[to], (int)graph[in[to]].size(), 0, cap};
    Edge in_from = {in[from], (int)graph[in[from]].size(), 0, cap};
    // Se o fluxo for direcionado, alterar para Edge b = {from, graph[from].size(), 0, 0};
    graph[out[from]].push_back(in_to);
    graph[out[to]].push_back(in_from);
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

    while (1) {

        for (int i = 0; i < N; i++) {
            graph[i].clear();
        }
        for (int i = 0; i < N; i++) dist[i] = 0;
        for (int i = 0; i < N; i++) work[i] = 0;
        for (int i = 0; i < N; i++) in[i] = 0;
        for (int i = 0; i < N; i++) out[i] = 0;
//        memset(dist, 0, sizeof dist);
//        memset(work, 0, sizeof work);
//        memset(in, 0, sizeof in);
//        memset(out, 0, sizeof out);


        scanf("%d %d", &n, &m);

        if (n == m && n == 0) {
            break;
        }


        int nodes = 0;
        addEdge(0, 1, INF);
        //addEdge(1, 0, INF);
        in[0] = 0;
        out[0] = 1;
        nodes+=2;
        int x, y;
        for (int i = 0; i < n - 2; i++) {
            scanf("%d %d", &x, &y);
            addEdge(nodes, nodes + 1, y);
            //addEdge(nodes + 1, nodes, y);

            nodes+=2;

            in[x - 1] = nodes - 2;
            out[x - 1] = nodes - 1;
        }
        addEdge(nodes, nodes + 1, INF);
        //addEdge(nodes + 1, nodes, INF);
        in[n - 1] = nodes;
        out[n - 1] = nodes + 1;
        nodes+=2;

        int z;
        for(int i = 0; i < m; i++) {
            scanf("%d %d %d", &x, &y, &z);
            addEdge(out[x - 1], in[y - 1], z);
            addEdge(out[y - 1], in[x - 1], z);
        }
        printf("%lld\n", flow(out[0], in[n - 1]));
    }
    return 0;
}
