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

#define mp make_pair
#define pb push_back

typedef long long ll;

using namespace std;

const int N = 200000;
const int NEUTRO = INT_MAX;

ll arr[N];
ll segTree[4 * N];
ll lazy[4 * N];

int n;

ll merge(ll v1, ll v2) {
    return min (v1,v2);
}

void build(int id, int l, int r) {
    if (l == r) {
        if (l >= n) {
            segTree[id] = NEUTRO;
        } else {
            segTree[id] = arr[l];
        }
    } else {
        int mid = (l + r) / 2;

        build(2 * id + 1, l, mid);
        build(2 * id + 2, mid + 1, r);
        segTree[id] = merge(segTree[2 * id + 1], segTree[2 * id + 2]);
    }
}

ll query(int id, int l, int r, int x, int y) {
    if (lazy[id] != 0) {
        segTree[id] += lazy[id];

        if (l != r) {
            lazy[2 * id + 1] += lazy[id];
            lazy[2 * id + 2] += lazy[id];
        }
        lazy[id] = 0;
    }
    if (r < x || l > y) {
        return NEUTRO;
    } if (l >= x && r <= y) {
        return segTree[id];
    } else {
        int mid = (l + r) / 2;

        return merge ( query(2 * id + 1, l, mid, x, y),
                       query(2 * id + 2, mid + 1, r, x, y));
    }
}

void update(int id, int l, int r, ll v, int x, int y) {
    if (lazy[id] != 0) {
        segTree[id] += lazy[id];

        if (l != r) {
            lazy[2 * id + 1] += lazy[id];
            lazy[2 * id + 2] += lazy[id];
        }
        lazy[id] = 0;
    }
    if (r <x || l > y) {
        return;
    }
    if (l == r) {
        segTree[id] += v;
    } else {
         if (l >= x && r <= y) {

            segTree[id] += v;

            lazy[2 * id + 1] += v;
            lazy[2 * id + 2] += v;
        } else {
            int mid = (l + r) / 2;

            update(2 * id + 1, l, mid, v, x, y);
            update(2 * id + 2, mid + 1, r, v, x, y);
            segTree[id] = merge(segTree[2 * id + 1], segTree[2 * id + 2]);
        }
    }
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    build(0, 0, n - 1);
    
    int m;
    cin >> m;
    
    int l, r, ch;
    ll v;
    
    for (int i = 0 ; i < m; i++) {
        scanf ("%d %d%c", &l, &r, &ch);

        if (ch != '\n') {
            cin >> v;
            if (r >= l) {
                update(0, 0, n - 1, v, l, r);
            } else {
                update(0, 0, n - 1, v, l,  n - 1);
                update(0, 0, n - 1, v, 0,  r);
            }
        } else {
            if (r >= l) {
                cout << query(0, 0, n - 1, l, r) << endl;
            } else {
                cout << merge( query(0, 0, n - 1, l, n - 1),
                               query(0, 0, n - 1, 0, r)) << endl;

            }
        }

    }

    return 0;
}