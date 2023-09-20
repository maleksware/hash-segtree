#include <bits/stdc++.h>
#define endl "\n"

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

using namespace std;
using ll = long long;
using ld = long double;

ll base = 31;
ll mod = 1e9 + 7;

ll binpow(ll a, ll n) {
  if (n == 0) return 1;
  if (n & 1) {
    return (a * binpow(a, n - 1)) % mod;
  } else {
    ll q = binpow(a, n / 2);
    return (q * q) % mod;
  }
}

ll subtract(ll a, ll b, ll mod) {
  a -= b;
  if (a < 0) {
    a += mod;
  }
  return a;
}

ll mul(ll a, ll b, ll mod) {
  return (a * 1ll * b) % mod;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  ll n;
  cin >> n;

  string s;
  cin >> s;

  ll m;
  cin >> m;

  vector<pair<ll, ll>> queries(m);

  for (int i = 0; i < m; i++) {
    cin >> queries[i].first >> queries[i].second;
  }

  vector<ll> hashes(n + 1), bases(n + 1);

  hashes[0] = 0;
  bases[0] = 1;

  for (int i = 0; i < n; i++) {
    hashes[i + 1] = (hashes[i] * base + (s[i] - 'a' + 1)) % mod;
    bases[i + 1] = (bases[i] * base) % mod;
  }

  for (int i = 0; i < m; i++) {
    ll l = queries[i].first;
    ll r = queries[i].second;

    cout << subtract(hashes[r], mul(hashes[l], bases[r - l], mod), mod) << endl; // [l; r)
  }

  return 0;
}
