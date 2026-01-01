#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int helper(string s){
    int ans=0;
    unordered_map<char,int>lastidx;
    int l=0;
    
    for(int r=0;r<s.length();r++){
        if(lastidx.count(s[r]) && lastidx[s[r]] >= l){
            l=lastidx[s[r]]+1;
        }
        lastidx[s[r]]=r;
        ans=max(ans,r-l+1);
    }
    return ans;
}
int main(){
    string s;
    cin>>s;
    cout<<helper(s)<<endl;
    return 0;
}
/*
Given a string s, find the length of the longest substring that contains no repeating characters.
A substring is a contiguous sequence of characters within a string.
Input
A string s consisting of ASCII characters (letters, digits, symbols, spaces, etc.)
 
 
 
Input	Output	Explanation
"abcabcbb"	3	The longest substring without repeating characters is "abc"
"bbbbb"	1	The longest substring is "b"
"pwwkew"	3	The longest substring is "wke"
 
 
*/