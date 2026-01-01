#include <bits/stdc++.h>
using namespace std;

class Solution{
  public:
  vector<int> ArrayGeneration(int n){
vector<int>ans(n+1,0);
if(n==0){
  return ans;
}
ans[1]=1;

for(int i=1;i<=n/2;i++){
    if(2*i<=n){
        ans[2*i]=ans[i];
    }
    if((2*i+1)<=n){
        ans[2*i+1]=ans[i]+ans[i+1];
    }
  }
  return ans;
}
};

int main(){
  Solution sol;
  vector<int> ans = sol.ArrayGeneration(7);
  for(auto x: ans){
    cout<<x<<" ";
  }
  return 0;
}
