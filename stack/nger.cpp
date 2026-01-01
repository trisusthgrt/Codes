#include <bits/stdc++.h>
using namespace std;

int main(){
  vector<int>arr={12,3,8,10,5,15,9,1};
  stack<int>st;
vector<int>res;

  for(int i=arr.size()-1;i>=0;i--){
    if(st.empty()){
res.push_back(-1);
    }
    else if(st.top()>arr[i]){
      res.push_back(st.top());
    }
    else{
      while(!st.empty() && st.top()<=arr[i]){
        st.pop();
      }
      if(st.empty()){
        res.push_back(-1);
      }
      else{
        res.push_back(st.top());
      }
    }
    st.push(arr[i]);
  }
reverse(res.begin(),res.end());
  for(auto &i:res){
    cout<<i<<" ";
  }
  return 0;
}