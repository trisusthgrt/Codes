#include <bits/stdc++.h>
using namespace std;

void fun(vector<string> str, int n, string s){
    int N = str.size();
    int i = -1;

    // Find index of s
    for(int k = 0; k < N; k++){
        if(str[k] == s){
            i = k;
            break;
        }
    }

    // If not found
    if(i == -1){
        cout << -1 << endl;
        return;
    }

    int cw = abs(i - n);   // clockwise distance
    int ccw = N - cw;     // counter-clockwise

    cout << min(cw, ccw) << endl;
}

int main(){
    fun({"blue","yellow","black","red","green"}, 3, "blue");
    fun({"blue","yellow","black","red","green"}, 0, "blue");
    return 0;
}
