#include<bits/stdc++.h>
using namespace std;

void fun(string s){

  unordered_map<char,int>mp;
  for(auto &i :s){
    mp[i]++;
  }
  for(int i=0;i<s.length();i++){
    if(mp[s[i]]==1){
      cout<<i+1<<endl;
      return;
    }
  }
  cout<<-1<<endl;
  return ;
}
int main(){
  fun("hello");
  fun("autaismut");
  fun("asddsa");
 
  return 0;
}
