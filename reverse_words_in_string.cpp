#include<bits/stdc++.h>
using namespace std;
string reverseWord(string s) {
        // Step 1: Remove extra spaces
        int n = s.size();
        int i = 0, j = 0;
        
        while (i < n) {
            while (i < n && s[i] == ' ') i++; // skip spaces
            cout<<s<<endl;
            while (i < n && s[i] != ' ') s[j++] = s[i++]; // copy word
            cout<<s<<endl;
            while (i < n && s[i] == ' ') i++; // skip spaces after word
            cout<<s<<endl;
            if (i < n) s[j++] = ' '; // add single space between words
            cout<<s<<endl;
        }
        cout<<s<<endl;
        s.resize(j);
cout<<s<<endl;
        // Step 2: Reverse whole string
        reverse(s.begin(), s.end());
cout<<s<<endl;
        // Step 3: Reverse each word
        int start = 0;
        for (int k = 0; k <= s.size(); k++) {
            if (k == s.size() || s[k] == ' ') {
                reverse(s.begin() + start, s.begin() + k);
                start = k + 1;
            }
        }

        return s;
    }
int main(){
  string str = "  Hello   World  ";
  string str2 = "";
  string str3 = "  World  Hello";
  string str4 = " a good   example  ";
 str =  reverseWord(str);
  cout<<str<<endl;
  str2 =reverseWord(str2);
  cout<<str2<<endl;

  str3 =reverseWord(str3);
  cout<<str3<<endl;
  str4 =  reverseWord(str4);
  cout<<str4<<endl;

  return 0;
}