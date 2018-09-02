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

const int N = 2 * 1001000;
const int NEUTRO = 0;

string s;
int segTree[3][4 * N];


ll n;

void build(int id, int l, int r) {
    if (l == r) {
        if (l >= s.length()) {
            segTree[0][id] = NEUTRO;
            segTree[1][id] = NEUTRO;
            segTree[2][id] = NEUTRO;
        }
        else if (s[l] == '(') {
            //cout << "ID" << id << endl;
            segTree[0][id] = NEUTRO;
            segTree[1][id] = 1;
            segTree[2][id] = NEUTRO;
        } else {
            //cout << "ID" << id << endl;
            segTree[0][id] = NEUTRO;
            segTree[1][id] = NEUTRO;
            segTree[2][id] = 1;
        }

    } else {
        int mid = (l + r) / 2;

        build(2 * id + 1, l, mid);
        build(2 * id + 2, mid + 1, r);
        segTree[0][id] = segTree[0][2 * id + 1] + segTree[0][2 * id + 2] + min(segTree[1][2 * id + 1], segTree[2][2 * id + 2]);
        segTree[1][id] = segTree[1][2 * id + 1] + segTree[1][2 * id + 2] - min(segTree[1][2 * id + 1], segTree[2][2 * id + 2]);
        segTree[2][id] = segTree[2][2 * id + 1] + segTree[2][2 * id + 2] - min(segTree[1][2 * id + 1], segTree[2][2 * id + 2]);
        //cout << "id: " << id << " " << segTree[0][id] << " " << segTree[1][id] << " " << segTree[2][id] << endl;
    }
}

pair<int, pair<int,int>> query(int id, int l, int r, int x, int y) {
    if (r < x || l > y) {
        return mp(0, mp(0,0));
    } if (l >= x && r <= y) {
        return mp(segTree[0][id], mp(segTree[1][id], segTree[2][id]));
    } else {
        int mid = (l + r) / 2;
        pair<int, pair<int, int>> esqd = query(2 * id + 1, l, mid, x, y);
        pair<int, pair<int, int>> dir = query(2 * id + 2, mid + 1, r, x, y);
        int valor = esqd.first + dir.first + min(esqd.second.first, dir.second.second);
        int seg = esqd.second.first + dir.second.first - min(esqd.second.first, dir.second.second);
        int ter = esqd.second.second + dir.second.second - min(esqd.second.first, dir.second.second);
        return mp(valor, mp(seg,ter));
    }
}

int main() {
    cin >> s;
    n = s.length();
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
   // cout << n << endl;

    build(0,0,n-1);
//    int id = 8;
//    cout << "id: " << id << " " << segTree[0][id] << " " << segTree[1][id] << " " << segTree[2][id] << endl;
//    id = 17;
//    cout << "id: " << id << " " << segTree[0][id] << " " << segTree[1][id] << " " << segTree[2][id] << endl;
//    id = 18;
//    cout << "id: " << id << " " << segTree[0][id] << " " << segTree[1][id] << " " << segTree[2][id] << endl;
    int m;
    cin >> m;
    int l, r;
    for (int i = 0; i < m; i++) {
        cin >> l >> r;
        l--;
        r--;
        pair <int, pair<int, int>> ans = query(0,0,n-1,l,r);
        //cout << ans.first << " " << ans.second.first << " " << ans.second.second << endl;
        cout << ans.first * 2 << endl;
    }

    return 0;
}