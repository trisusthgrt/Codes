#include<bits/stdc++.h>
using namespace std;


class Solution{
  public:
    string maximiseNumber(string str,int k){
   string s=str;
   string ans="";
   for(int i=0;i<str.size();i++){
    int a =s[i]-'0';
    if(a==k){
     string temp=s.substr(0,i)+s.substr(i+1);
     int b=stoi(temp);
     if( !ans.empty() && b>stoi(ans)){
      ans=temp;
     }
     else if(ans.empty()){
      ans=temp;
     }
    }
   }
   return ans;
    }
};


int main(){
  Solution sol;
  string ans = sol.maximiseNumber("1321", 1);

 cout<<ans<<endl;

  return 0;
}