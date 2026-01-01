#include<bits/stdc++.h>
using namespace std;
void fun(string s, int n, vector<string> sub){
  int sum=0;
    for(int i=0;i<n;i++){
    int idx=s.find(sub[i]);
      if(idx!=-1)
   sum+=s.length()-idx;
    }
    cout<<sum<<endl;
    
}
int main(){
  fun("qwertyuiop",1,{"d"});
  fun("qwertyuiop",2,{"ty","o"});
  return 0;
}