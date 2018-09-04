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

const int N = 100100;

int n,m;
int arr[N];
vector<pair<int, int>> vec;

vector<int> segTree[4 * N];

int build(int index, int l, int r) {
    if (l == r) {
        if (l >= n) {
            return 0;
        } else {
            segTree[index].pb(vec[l].second);
        }
    } else {
        int mid = (l + r) / 2;

        build(2 * index + 1, l, mid);
        build(2 * index + 2, mid + 1, r);
        merge(segTree[2 * index + 1].begin(), segTree[2 * index + 1].end(),
              segTree[2 * index + 2].begin(), segTree[2 * index + 2].end(), back_inserter(segTree[index])  );
    }
}


int query(int index, int l, int r, int x, int y, int k) {
    if (l == r) {
        return segTree[index][0];
    }

    int mid = (l + r) / 2;

    int last = (upper_bound(segTree[2 * index + 1].begin(),
                            segTree[2 * index + 1].end(), y) - segTree[2 * index + 1].begin());

    int first = (lower_bound(segTree[2 * index + 1].begin(),
                             segTree[2 * index + 1].end(), x) - segTree[2 * index + 1].begin());
    int m = last - first;
    if (m >= k) {
        return query(2 * index + 1, l, mid, x, y, k);
    } else {
        return query(2 * index + 2, mid + 1, r, x, y, k - m);
    }
}


int main() {
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    for (int i = 0; i < n; i++) {
        vec.pb(mp(arr[i], i));
    }

    sort(vec.begin(), vec.end());
    build(0, 0, n - 1);

    int l, r, k;

    for (int i = 0; i < m; i++) {
        cin >> l >> r >> k;
        l--;
        r--;

        int ans = query(0, 0, n - 1, l, r, k);
        cout << arr[ans] << endl;
    }

    return 0;
}
