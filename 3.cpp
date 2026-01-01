#include <bits/stdc++.h>
using namespace std;

long long bitOperation(const vector<int>& res, const vector<int>& res1) {
    long long sum = 0, sum1 = 0;
    int pre = 0, pre1 = 0;

    for (int i = 0; i < res.size(); i++) {
        pre ^= res[i];
        sum += pre;

        pre1 ^= res1[i];
        sum1 += pre1;
    }
    return max(sum, sum1);
}

// ✅ Correct clockwise & anti-clockwise circular construction
pair<vector<int>, vector<int>> vectorCreation(const vector<int>& a, int start) {
    int n = a.size();
    vector<int> res(n), res1(n);

    // ✅ Clockwise
    int z = 0;
    for (int i = 0; i < n; i++) {
        res[z++] = a[(start + i) % n];
    }

    // ✅ Anti-clockwise
    int y = 0;
    for (int i = 0; i < n; i++) {
        res1[y++] = a[(start - i + n) % n];
    }

    return {res, res1};
}

int main() {
    vector<int> a = {1, 2, 3, 4, 5};
    long long ans = 0;

    for (int i = 0; i < a.size(); i++) {
        auto x = vectorCreation(a, i);
        vector<int> res = x.first;
        vector<int> res1 = x.second;

        ans = max(ans, bitOperation(res, res1));
    }

    cout << ans << endl;
    return 0;
}
