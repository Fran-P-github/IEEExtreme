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


ll mnorm(ll a, ll m = MOD) {
    a %= m;
    return a < 0 ? a + m : a;
}

ll madd(ll a, ll b, ll m = MOD) { return (mnorm(a, m) + mnorm(b, m)) % m; }

ll msub(ll a, ll b, ll m = MOD) { return mnorm(mnorm(a, m) - mnorm(b, m), m); }

ll mmul(ll a, ll b, ll m = MOD) { return mnorm(a, m) * mnorm(b, m) % m; }

ll mdiv(ll a, ll b, ll m = MOD) { return mmul(a, inv(b, m), m); }   // m primo y b != 0 (mod m)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());


// ---------- Solucion ----------
void solve() {
    // TODO: leer entrada y resolver
    ll a, b, p, x1, y1, x2, y2, s, x3, y3;
    cin >> a >> b >> p >> x1 >> y1 >> x2 >> y2;
    if((x1==x2) && (madd(y1,y2,p)==0)){
        cout << "POINT_AT_INFINITY" << endl;
    }
    else if((x1==x2) && (y1==y2)){
        s = mmul(madd(mmul(3, power(x1, 2, p), p), a , p), inv(mmul(2, y1, p), p), p); // s = (3(x1)^2 + a)/(2y1)
        x3 = msub(power(s, 2, p), mmul(x1, 2, p), p); // x3 = s^2 -2(x1)
        y3 = msub(mmul(s, msub(x1, x3, p), p), y1, p); // y3 = s(x1 -x3) -y1
        cout << x3 << " " << y3 << endl;
    }
    else{
        s = mmul(msub(y2, y1, p), inv(msub(x2, x1, p), p), p); // s = (y2-y1)/(x2-x1)
        x3 = msub(msub(power(s, 2, p), x1, p), x2, p); // x3 = s^2 -x1 -x2
        y3 = msub(mmul(s, msub(x1, x3, p), p), y1, p); // y3 = s(x1 -x3) -y1
        cout << x3 << " " << y3 << endl;
    }
    //dbg(n, a);
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;   // descomentar si hay multiples casos de prueba
    while (t--) solve();

    return 0;
}