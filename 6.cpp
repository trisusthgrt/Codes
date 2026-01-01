#include<bits/stdc++.h>
using namespace std;
void fun(int n){
set<int>s;
int m=n;
for(int i=2;i<m;i++){
  n=m;
while(n>0){
  int a= n%i;
  n=n/i;
  s.insert(a);
}

if(s.size()==1){
  cout<<i<<endl;
  return;
}
s.clear();
}
return ;
}
int main(){
  int n=41;
  fun(n);

  return 0;
}