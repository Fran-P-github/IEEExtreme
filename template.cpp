/*
TEMPLATE GENERATED USING SONNET 5.5 BY ANTHROPIC (https://claude.ai/)
 * Plantilla C++ para IEEEXtreme 20.0
 *
 * Compilar localmente (con debug):
 *   g++ -std=c++17 -O2 -Wall -Wextra -DLOCAL -o sol sol.cpp
 * Ejecutar:
 *   ./sol < input.txt
 *
 * En la plataforma de la competencia NO se define LOCAL,
 * por lo que dbg(...) no hace nada y no afecta el tiempo.
 */
#include <bits/stdc++.h>
using namespace std;

// ---------- Tipos ----------
using ll   = long long;
using ull  = unsigned long long;
using i128 = __int128;
using pii  = pair<int, int>;
using pll  = pair<ll, ll>;
using vi   = vector<int>;
using vl   = vector<ll>;
using vvi  = vector<vi>;
using vvl  = vector<vl>;

// ---------- Macros ----------
#define all(x)  (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x)   ((int)(x).size())
#define pb      push_back
#define fi      first
#define se      second
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define per(i, a, b) for (int i = (b) - 1; i >= (a); --i)

// ---------- Constantes ----------
constexpr int INF  = 1e9;
constexpr ll  LINF = 4e18;
constexpr ll  MOD  = 1'000'000'007;   // cambiar a 998244353 si el problema lo pide
constexpr double EPS = 1e-9;
const int dx[] = {1, 0, -1, 0, 1, 1, -1, -1};
const int dy[] = {0, 1, 0, -1, 1, -1, 1, -1};

// ---------- Debug (solo con -DLOCAL) ----------
#ifdef LOCAL
template <class A, class B>
ostream& operator<<(ostream& o, const pair<A, B>& p) {
    return o << '(' << p.first << ", " << p.second << ')';
}
template <class T, class = enable_if_t<!is_same_v<T, string>>>
auto operator<<(ostream& o, const T& v) -> decltype(v.begin(), o) {
    o << '[';
    bool first = true;
    for (const auto& x : v) { if (!first) o << ", "; first = false; o << x; }
    return o << ']';
}
void dbg_out() { cerr << endl; }
template <class H, class... T>
void dbg_out(const H& h, const T&... t) { cerr << ' ' << h; dbg_out(t...); }
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)
#else
#define dbg(...) ((void)0)
#endif

// ---------- Utilidades ----------
template <class T> bool chmin(T& a, const T& b) { return b < a ? (a = b, true) : false; }
template <class T> bool chmax(T& a, const T& b) { return b > a ? (a = b, true) : false; }

ll power(ll b, ll e, ll m = MOD) {
    ll r = 1; b %= m;
    for (; e > 0; e >>= 1, b = b * b % m) if (e & 1) r = r * b % m;
    return r;
}
ll inv(ll a, ll m = MOD) { return power(a, m - 2, m); }   // m debe ser primo

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// ---------- Solucion ----------
void solve() {
    // TODO: leer entrada y resolver
    int n;
    cin >> n;
    vl a(n);
    for (auto& x : a) cin >> x;

    dbg(n, a);

    cout << accumulate(all(a), 0LL) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;   // descomentar si hay multiples casos de prueba
    while (t--) solve();

    return 0;
}