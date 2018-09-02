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

const int N = 100100;
const int NEUTRO = 0;

int arr[N];
int segTree[21][4 * N];
int lazy[21][4 * N];

int n,m;

int merge(int v1, int v2) {
    return v1 + v2;
}

void build(int id, int l, int r, int bit) {
    if (l == r) {
        if (l >= n) {
            segTree[bit][id] = NEUTRO;
        } else {
            if (arr[l] & (1<<bit))
                segTree[bit][id] = 1;
            else
                segTree[bit][id] = NEUTRO;
        }
    } else {
        int mid = (l + r) / 2;

        build(2 * id + 1, l, mid,bit);
        build(2 * id + 2, mid + 1, r,bit);
        segTree[bit][id] = merge(segTree[bit][2 * id + 1], segTree[bit][2 * id + 2]);
    }
}

int query(int id, int l, int r, int x, int y, int bit) {
    if (lazy[bit][id] != 0) {
        segTree[bit][id] = (r - l + 1) - segTree[bit][id];

        if (l != r) {
            lazy[bit][2 * id + 1] ^= 1;
            lazy[bit][2 * id + 2] ^= 1;
        }
        lazy[bit][id] = 0;
    }
    if (r < x || l > y) {
        return NEUTRO;
    } if (l >= x && r <= y) {
        return segTree[bit][id];
    } else {
        int mid = (l + r) / 2;

        return merge ( query(2 * id + 1, l, mid, x, y, bit),
                       query(2 * id + 2, mid + 1, r, x, y, bit));
    }
}

void update(int id, int l, int r, int x, int y, int bit) {
    if (lazy[bit][id]) {
        segTree[bit][id] = (r - l + 1) - segTree[bit][id];

        if (l != r) {
            lazy[bit][2 * id + 1] ^= 1;
            lazy[bit][2 * id + 2] ^= 1;
        }
        lazy[bit][id] = 0;
    }
    if (r <x || l > y) {
        return;
    }
     else {
        if (l >= x && r <= y) {

            segTree[bit][id] = (r - l + 1) - segTree[bit][id];

            if (l != r) {
                lazy[bit][2 * id + 1] ^= 1;
                lazy[bit][2 * id + 2] ^= 1;
            }

        } else {
            int mid = (l + r) / 2;

            update(2 * id + 1, l, mid, x, y, bit);
            update(2 * id + 2, mid + 1, r, x, y, bit);
            segTree[bit][id] = merge(segTree[bit][2 * id + 1], segTree[bit][2 * id + 2]);
        }
    }
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    for (int i = 0; i < 20; i++) {
        build(0, 0, n - 1, i);
    }

    cin >> m;
    int t, l,r, x;


    for (int j = 0; j < m; j++) {
        cin >> t >> l >> r;
        l--;
        r--;
        if (t == 2) {
            cin >> x;
        }

        if (t == 1) {
            ll sum = 0;
            for (int i = 0; i < 20; i++) {
                sum += query(0, 0, n - 1, l, r, i) * (1LL<<i);
            }
            cout << sum << endl;
        } else {
            for (int i = 0; i < 20; i++) {
                if (x & (1LL<<i))
                    update(0, 0, n - 1, l, r, i);
            }
        }
    }

    return 0;
}