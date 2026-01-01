#include<bits/stdc++.h>
using namespace std;

int main(){
  vector<int>arr={12,33,22,55,1,34,33};
  vector<int>arr1={2,2,2,2,2};
  int c=0;
  sort(arr.begin(),arr.end());
  int l=0;
  int r=arr.size()-1;
  while(l<=r){
    if(arr[l]!=arr[r]){
      l++;
      r--;
      c++;
    }
    else{
      l++;
      c++;
    }
  }
  int d=0;
  sort(arr1.begin(),arr1.end());
  int a=0;
  int b=arr1.size()-1;
  while(a<=b){
    if(arr1[a]!=arr1[b]){
      a++;
      b--;
      d++;
    }
    else{
      a++;
      d++;
    }
  }
  cout<<c<<endl;
  cout<<d<<endl;
vector<int>arr2={22,44,44,11,55,22};
  int m=0;
  int e=0;
  int n=arr2.size()-1;
  while(m<=n){
    if(arr2[m]!=arr2[n]){
      e++;
      m++;
      n--;

    }
    else{
      m++;
      e++;
    }
  }
  cout<<e<<endl;
  return 0;
}