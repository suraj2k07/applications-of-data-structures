#include <bits/stdc++.h>
#include <vector>
#include <string>

using namespace std;

int main() {
    for(int k=0;k<5;k++){
        string s;
        cin >> s;
        int count=0,mx=0,t=0,l=0;
        for (int i=0;i<s.length();i++){
            if(s[i]=='(') {t+=1;l+=1;}
            else {t-=1;l+=1;}
            if(t<0) {
                mx=max(mx,l-1);l=0;t=0;}
        }
        mx=max(mx,l-t);
        cout<<mx<<endl;
}}