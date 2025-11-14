#include <bits/stdc++.h>
using namespace std;
using ll = long long;
class SegmentTree {
  vector<ll> segtree;
  int start;
  int real_size(int n) {
    int i = 1;
    while(i < n) {
      i <<= 1;
    }
    return i << 1;
  }
public:
  SegmentTree(int n, ll init_value = 0) {
    segtree = vector<ll>(real_size(n), init_value);
    start = segtree.size() >> 1;
  }
  SegmentTree(vector<ll> values) {
    int n = values.size();
    int rs = real_size(n);
    segtree = vector<ll>(rs, INT64_MIN);
    start = rs >> 1;
    for(int i=0;i<n;++i){
      segtree[i+start] = values[i];
    }
    for(int i=start-1;i>=1;--i){
      segtree[i] = max(segtree[i<<1], segtree[(i<<1)+1]);
    }
  }
  void update(int i, ll val) {
    i += start;
    segtree[i] = val;
    i >>= 1;
    while(i > 0) {
      segtree[i] = max(segtree[i<<1], segtree[(i<<1)+1]);
      i >>= 1;
    }
  }
  ll query(int i, int j) {
    i += start; j += start;
    ll ans = 0;
    while (i <= j) {
      if(i&1) ans = max(ans, segtree[i++]);
      if(!(j&1)) ans = max(ans, segtree[j--]);
      i >>= 1; j >>= 1;
    }
    return ans;
  }
};



vector<SegmentTree *> dp;
vector<pair<ll, ll>> intervals;
int n;
ll t,k;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin>>n>>t>>k;
  dp = vector<SegmentTree *>(n+1);
  intervals = vector<pair<ll,ll>>(n);

  for(int i=0;i<n;++i){
    ll a,b;
    cin>>a>>b;
    intervals[i] = {a,b};
  }

  sort(intervals.begin(), intervals.end(), [&](const pair<ll,ll> &p1, const pair<ll,ll> &p2) {
    return p1.first < p2.first;
  });
  int ans = -1;
  vector<ll> values;
  for(int i=0; i<n; ++i) {
    values.push_back(t - intervals[i].second + intervals[i].first);
    if (values.back() >= k) ans = 0;
  }
  dp[0] = new SegmentTree(values);
  values.clear();
  // for(int x=1; x<=n; ++x) {
  //   dp[x]->update(n-1, INT64_MIN);
  // }

  auto next_one = [&](int current) {
    int ans_idx = n;
    int l = current + 1, r = n-1;
    while (l <= r) {
      int m = l + ((r-l)>>1);
      if (intervals[m].first >= intervals[current].second) {
        ans_idx = m;
        r = m-1;
      } else {
        l = m+1;
      }
    }
    return ans_idx;
  };

  int next[n];
  for(int i=0;i<n;++i){
    next[i] = next_one(i);
  }

  for(int x = 1; x <= n; ++x) { // n
    ll highest = 0;
    values.push_back(INT64_MIN);
    for(int i=n-2; i >= 0; --i) { // n
      int j = next[i];
      if (j == n) {
        values.push_back(INT64_MIN);
        continue;
      }
      ll highest_i = dp[x-1]->query(j, n-1) - intervals[i].second; // log n
      values.push_back(highest_i + intervals[i].first);
      highest = max(highest, highest_i + intervals[i].first);
    }
    reverse(values.begin(), values.end()); // n
    dp[x] = new SegmentTree(values); // n
    values.clear(); // n
    if (highest >= k) ans = max(ans, x);
  }

  cout<<ans+1<<'\n';

}