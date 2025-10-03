#include <bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin >> t;
    while(t>0){
        int n,l,o;
        cin >> n;
        vector<int> v(n,0);
        map<int,vector<int>> m;
        for (int i=0;i<n-1;i++){
            cin >> l >> o;
            m[l].push_back(o);
            m[o].push_back(l);
        }        
        int y=0;
        for(int i=1;i<=n;i++){
            if(m[i].size()==1) {v[m[i][0]]+=1;y+=1;}
        }
        int q=*max_element(v.begin(),v.end());
        cout<<y-q<<endl;
        t-=1;
    }
}