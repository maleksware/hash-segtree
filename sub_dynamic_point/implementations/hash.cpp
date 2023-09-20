#include <bits/stdc++.h>
#define endl "\n"

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

using namespace std;
using ll = long long;
using ld = long double;

ll mod = 1e9 + 7;
ll base = 31;

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

  vector<char> s(n);
  for (int i = 0; i < n; i++) {
    cin >> s[i];
  }

  vector<ll> hashes(n + 1), bases(n + 1);

  hashes[0] = 0;
  bases[0] = 1;

  for (int i = 0; i < n; i++) {
    hashes[i + 1] = (hashes[i] * base + (s[i] - 'a' + 1)) % mod;
    bases[i + 1] = (bases[i] * base) % mod;
  }

  ll m;
  cin >> m;

  for (int num_test = 0; num_test < m; num_test++) {
    ll qtype;
    cin >> qtype;

    if (qtype == 1) {
      ll l, r;
      cin >> l >> r;

      cout << subtract(hashes[r], mul(hashes[l], bases[r - l], mod), mod) << endl; // [l; r)
    } else {
      ll x;
      char c;
      cin >> x >> c;

      s[x] = c;

      for (int i = x; i < n; i++) {
        hashes[i + 1] = (hashes[i] * base + (s[i] - 'a' + 1)) % mod;
      }
    }
  }

  return 0;
}
