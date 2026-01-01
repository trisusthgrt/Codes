#include <bits/stdc++.h>
using namespace std;

string suma(string a, string b){
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    int n = max(a.size(), b.size());
    string res = "";
    int carry = 0;

    for(int i = 0; i < n; i++){
        int x = (i < a.size() ? a[i] - '0' : 0);
        int y = (i < b.size() ? b[i] - '0' : 0);

        int sum = x + y + carry;
        res.push_back((sum % 2) + '0');
        carry = sum / 2;
    }

    if(carry) res.push_back('1');

    reverse(res.begin(), res.end());
    return res;
}

// ✅ SIMPLE BINARY STRING COMPARISON
bool isGreater(string a, string b){
    if(a.size() != b.size())
        return a.size() > b.size();   // longer = bigger
    return a > b;                     // lexicographical compare
}

void fun(vector<vector<string>>& str, int t){
    string maxi = "0";

    for(int i = 0; i < t; i++){
        string sum = suma(str[i][0], str[i][1]);

        if(isGreater(sum, maxi))
            maxi = sum;
    }

    cout << maxi << endl;
}

int main(){
    int t = 3;
    vector<vector<string>> str = {
        {"101","100"},
        {"110","10"},
        {"1000","11"}
    };

    fun(str, t);
    return 0;
}
