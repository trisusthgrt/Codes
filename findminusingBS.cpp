#include<bits/stdc++.h>
using namespace std;
int findMin(vector<int> nums) 
    {
        int n = nums.size();
        int start = 0, end = n-1;
        if(nums[start] < nums[end])
        {
            return 0;
        }
        while(start <= end)
        {
            int mid = start + (end - start)/2;
            int next = (mid+1)%n;
            int prev = (mid + n - 1)%n;
            if(nums[mid] <= nums[next] && nums[mid] <= nums[prev])
            {
                return mid;
            }
          

            else if(nums[end]<nums[mid])
                start = mid+1;
            else 
                end= mid-1;
        }
        return -1;

        // int l=0;
        // int r=nums.size()-1;
        // while(l<r){
        //     int mid=l+(r-l)/2;
        //     if(nums[mid]<nums[r]){
        //         r=mid;
        //     }
        //     else{
        //         l=mid+1;
        //     }
        // }
        // return l;
    }
int main(){
  int a=findMin({2,2,2,0,2,2});
  cout<<a<<endl;
  int b=findMin({5,6,7,7,8,1,1,2,3,4,4});
  cout<<b<<endl;

  return 0;
}