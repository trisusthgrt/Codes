#include<bits/stdc++.h>
using namespace std;

class Solution{
public:
 int Defeating(int n,int exp,vector<int>&poweri,vector<int>&bonusi){
  int c=0;
  vector<pair<int,int>>res;
  for(int i=0;i<n;i++){
    res.push_back({poweri[i],bonusi[i]});
  }
  sort(res.begin(),res.end());

  for(auto &i:res){
   int f= i.first;
   int s=i.second;
   if(f<=exp){
    c++;
    exp+=s;
   }
   else{
    break;
   }
  }
  return c;
 }
};
int main(){
  Solution sol;
  int n=3;
  int exp=128;
  vector<int>poweri={121,130,135};
  vector<int>bonusi={0,0,20};

  int res = sol.Defeating(n,exp,poweri,bonusi);
  cout<<res<<endl;
  return 0;


}