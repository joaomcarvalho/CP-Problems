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

typedef long long ll;

using namespace std;

#define mp make_pair
#define pb push_back

const int N = 1000;
const int LOGN = 10;

vector<int> children[N];
int parent[N][LOGN];
int depth[N];

int n, t, q, caso = 1;

void build() {
    for (int j = 1; j < LOGN; ++j) {
        for (int i = 0; i < N; i++) {
            if (parent[i][j-1] != -1) {
                parent[i][j] = parent[parent[i][j-1]][j-1];
            }
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        swap(u, v);
    }

    for (int i = LOGN - 1; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = parent[u][i];
        }
    }

    if (u == v) {
        return u;
    }

    for (int i  = LOGN - 1; i >= 0; --i) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}


int main() {
    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        memset(parent, -1, sizeof(parent[0][0]) * N * LOGN);
        memset(depth, 0, sizeof(depth));
        for (int j = 0; j < N; j++) {
            vector<int> vec;
            children[i] = vec;
        }
        scanf("%d", &n);
        depth[0] = 1;
        int filhos, cur;
        for (int j = 0; j < n; j++) {
            scanf("%d", &filhos);

            for (int z = 0;  z < filhos; z++) {
                scanf("%d" , &cur);
                children[j].pb(cur - 1);
                parent[cur - 1][0] = j;
                depth[cur - 1] = depth[j] + 1;
            }
        }
        build();
        scanf("%d", &q);
        int l, r;
        printf("Case %d:\n", caso);
        caso++;
        for (int j = 0; j < q; j++) {
            scanf ("%d %d", &l, &r);
            l--;r--;
            printf("%d\n", lca(l,r) + 1);
        }
    }

    return 0;
}