#include<bits/stdc++.h>
using namespace std;
int main(){
  int x;
  cin>>x;
  int ans;
  string res;
  while(x>0){
res+= x%2==0?'0':'1';
x>>=1;
  }
  reverse(res.begin(),res.end());
  ans=stoi(res);
  cout<<ans<<endl;
  return 0;
}