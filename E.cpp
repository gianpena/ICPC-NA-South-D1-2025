#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin>>n;

    map<int,int> distances;
    for(int i=0;i<n;++i){
        int k;
        cin>>k;
        distances[k]++;
    }

    int l = 1, r = 1000;
    int ans = r;

    auto valid = [&](int n) {
        map<int,int> frequencies;
        for(int i=0, c=1;i<=2*(n-1);++i){
            frequencies[i] = c;
            if(i >= n-1) c--;
            else c++;
        }
        for(auto &[key,value] : distances) {
            if(frequencies[key] < value) return false;
        }
        return true;

    };

    while(l <= r) {

        int m = l + ((r-l)>>1);
        if(valid(m)) {
            ans = m;
            r = m-1;
        } else l = m+1;
        
    }

    cout<<ans<<'\n';
}