// GENERATED USING SONNET 5.5 BY ANTHROPIC (https://claude.ai/)

# Cheatsheet general de programación competitiva en C++

Referencia rápida de complejidades, STL, estructuras de datos y algoritmos clásicos. Los snippets usan los alias de la plantilla (`ll`, `vi`, `vl`, `pii`, `pll`, `all()`, `sz()`, `rep()`, `INF`, `LINF`, `MOD`).

## 1. Complejidad según el tamaño de n

| n máximo | Complejidad aceptable |
| --- | --- |
| ≤ 10 | O(n!) |
| ≤ 20 | O(2^n · n) |
| ≤ 500 | O(n^3) |
| ≤ 5 000 | O(n^2) |
| ≤ 10^5 | O(n log n) |
| ≤ 10^6 | O(n) o O(n log n) con constante baja |
| ≤ 10^9 o más | O(log n) o O(1) (fórmula, búsqueda binaria) |

Regla práctica: unas 10^8 operaciones simples por segundo.

## 2. STL esencial

```cpp
sort(all(v));                          // ascendente
sort(all(v), greater<>());             // descendente
sort(all(v), [](auto& a, auto& b){ return a.se < b.se; });
v.erase(unique(all(v)), v.end());      // eliminar duplicados (ordenado)
reverse(all(v));
auto it = lower_bound(all(v), x);      // primer elemento >= x
auto jt = upper_bound(all(v), x);      // primer elemento > x
int cnt = jt - it;                     // cuántos son iguales a x
binary_search(all(v), x);              // existe x?
max_element(all(v)); min_element(all(v));
accumulate(all(v), 0LL);               // suma (usar 0LL para evitar overflow)
iota(all(v), 0);                       // 0,1,2,...
next_permutation(all(v));              // v debe estar ordenado al inicio
fill(all(v), 0);
memset(a, 0, sizeof a);                // solo 0 o -1
```

| Contenedor | Operaciones | Costo |
| --- | --- | --- |
| `vector` | acceso, push\_back | O(1) |
| `set` / `map` | insert, find, erase | O(log n) |
| `multiset` | permite repetidos | O(log n) |
| `unordered_map` | insert, find | O(1) promedio |
| `priority_queue` | push, pop, top | O(log n), O(1) |
| `deque` | push/pop en ambos extremos | O(1) |
| `bitset<N>` | operaciones por bits | O(N/64) |

```cpp
priority_queue<int> maxheap;
priority_queue<int, vector<int>, greater<int>> minheap;
set<int> s; s.lower_bound(x);          // usar el método del set, no std::lower_bound
map<string,int> m; m["a"]++;
for (auto& [k, v] : m) { }             // structured bindings (C++17)
```

## 3. Técnicas básicas

**Sumas prefijas**

```cpp
vl pre(n + 1, 0);
rep(i, 0, n) pre[i + 1] = pre[i] + a[i];
// suma de [l, r) = pre[r] - pre[l]
```

**Dos punteros (ventana deslizante)**

```cpp
int l = 0; ll sum = 0, best = 0;
rep(r, 0, n) {
    sum += a[r];
    while (sum > K) sum -= a[l++];
    best = max(best, (ll)(r - l + 1));
}
```

**Búsqueda binaria sobre la respuesta** (menor x tal que `ok(x)` es verdadero, `ok` monótona)

```cpp
ll lo = 0, hi = 1e18;                  // invariante: ok(hi) = true
while (lo < hi) {
    ll mid = lo + (hi - lo) / 2;
    if (ok(mid)) hi = mid; else lo = mid + 1;
}
// respuesta = lo
```

**Compresión de coordenadas**

```cpp
vi vals = a; sort(all(vals)); vals.erase(unique(all(vals)), vals.end());
for (auto& x : a) x = lower_bound(all(vals), x) - vals.begin();
```

## 4. Grafos

Lista de adyacencia: `vvi g(n);` o con pesos `vector<vector<pll>> g(n);` (destino, peso).

**BFS (distancias mínimas sin pesos)**

```cpp
vi d(n, -1); queue<int> q;
d[s] = 0; q.push(s);
while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : g[u]) if (d[v] < 0) { d[v] = d[u] + 1; q.push(v); }
}
```

**DFS recursivo** (cuidado con la recursión profunda, n > 10^5 puede dar stack overflow)

```cpp
void dfs(int u, int p) {
    for (int v : g[u]) if (v != p) dfs(v, u);
}
```

**Dijkstra (pesos no negativos)**, O((V+E) log V)

```cpp
vl dijkstra(int s, const vector<vector<pll>>& g) {
    vl d(g.size(), LINF);
    priority_queue<pll, vector<pll>, greater<>> pq;
    d[s] = 0; pq.push({0, s});
    while (!pq.empty()) {
        auto [du, u] = pq.top(); pq.pop();
        if (du > d[u]) continue;
        for (auto [v, w] : g[u])
            if (d[u] + w < d[v]) { d[v] = d[u] + w; pq.push({d[v], v}); }
    }
    return d;
}
```

**Ordenamiento topológico (Kahn)**

```cpp
vi indeg(n, 0), order; queue<int> q;
rep(u, 0, n) for (int v : g[u]) indeg[v]++;
rep(u, 0, n) if (!indeg[u]) q.push(u);
while (!q.empty()) {
    int u = q.front(); q.pop(); order.pb(u);
    for (int v : g[u]) if (--indeg[v] == 0) q.push(v);
}
// si sz(order) < n, hay ciclo
```

**DSU (Union-Find)** con compresión de caminos y unión por tamaño; base de Kruskal (ordenar aristas por peso y unir si `unite` devuelve true)

```cpp
struct DSU {
    vi p, s;
    DSU(int n) : p(n), s(n, 1) { iota(all(p), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (s[a] < s[b]) swap(a, b);
        p[b] = a; s[a] += s[b];
        return true;
    }
};
```

**Floyd-Warshall** (n ≤ \~400)

```cpp
rep(k, 0, n) rep(i, 0, n) rep(j, 0, n)
    if (d[i][k] < LINF && d[k][j] < LINF) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
```

Bellman-Ford: usar si hay pesos negativos (O(VE)). Para ciclos negativos, una iteración extra que aún relaje indica ciclo.

## 5. Estructuras de datos

**Fenwick Tree (BIT)**: suma de prefijo con actualización puntual, O(log n)

```cpp
struct BIT {
    int n; vl t;
    BIT(int n) : n(n), t(n + 1, 0) {}
    void add(int i, ll v) { for (++i; i <= n; i += i & -i) t[i] += v; }
    ll sum(int i) { ll r = 0; for (++i; i > 0; i -= i & -i) r += t[i]; return r; } // [0..i]
};
```

**Segment Tree iterativo** (suma, intervalo \[l, r)); para mínimo cambiar `+` por `min` y el neutro por INF

```cpp
struct Seg {
    int n; vl t;
    Seg(int n) : n(n), t(2 * n, 0) {}
    void set(int i, ll v) { for (t[i += n] = v; i > 1; i >>= 1) t[i >> 1] = t[i] + t[i ^ 1]; }
    ll query(int l, int r) {
        ll s = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) s += t[l++];
            if (r & 1) s += t[--r];
        }
        return s;
    }
};
```

**Sparse Table** (RMQ estático, consulta O(1)): `st[k][i] = min(st[k-1][i], st[k-1][i + (1 << (k-1))])`; consulta en \[l, r\] con `k = 31 - __builtin_clz(r - l + 1)` y `min(st[k][l], st[k][r - (1 << k) + 1])`.

**Pila monótona** (siguiente elemento mayor)

```cpp
vi nxt(n, n); stack<int> st;
rep(i, 0, n) {
    while (!st.empty() && a[st.top()] < a[i]) { nxt[st.top()] = i; st.pop(); }
    st.push(i);
}
```

## 6. Programación dinámica

Pasos: definir el estado, la transición, el caso base y el orden de cálculo.

**Mochila 0/1** (capacidad W), O(nW)

```cpp
vl dp(W + 1, 0);
rep(i, 0, n) for (int w = W; w >= wt[i]; --w) dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
```

Para mochila con repetición, recorrer `w` de menor a mayor.

**LIS en O(n log n)** (estrictamente creciente; usar `upper_bound` para no decreciente)

```cpp
vl d;
for (ll x : a) {
    auto it = lower_bound(all(d), x);
    if (it == d.end()) d.pb(x); else *it = x;
}
// longitud = sz(d)
```

**LCS** de `a` y `b`

```cpp
vvi dp(n + 1, vi(m + 1, 0));
rep(i, 1, n + 1) rep(j, 1, m + 1)
    dp[i][j] = a[i-1] == b[j-1] ? dp[i-1][j-1] + 1 : max(dp[i-1][j], dp[i][j-1]);
```

**DP sobre máscaras**: `dp[mask][i]` con n ≤ 20; recorrer submáscaras con `for (int s = m; s; s = (s - 1) & m)`.

Otros clásicos: cambio de monedas (mínimo o número de formas), distancia de edición, DP en árboles (calcular hijos antes que el padre), DP sobre dígitos.

## 7. Matemática y teoría de números

```cpp
// Criba de Eratóstenes, O(n log log n)
vector<bool> comp(N + 1, false);
for (int i = 2; (ll)i * i <= N; ++i) if (!comp[i])
    for (int j = i * i; j <= N; j += i) comp[j] = true;

// Factorización por división, O(sqrt n)
vector<pll> factor(ll n) {
    vector<pll> f;
    for (ll p = 2; p * p <= n; ++p) if (n % p == 0) {
        int c = 0; while (n % p == 0) n /= p, c++;
        f.pb({p, c});
    }
    if (n > 1) f.pb({n, 1});
    return f;
}

// MCD y MCM (C++17)
gcd(a, b); lcm(a, b);

// nCr módulo primo: precalcular factoriales
vl fact(N + 1), ifact(N + 1);
fact[0] = 1; rep(i, 1, N + 1) fact[i] = fact[i-1] * i % MOD;
ifact[N] = inv(fact[N]); per(i, 0, N) ifact[i] = ifact[i+1] * (i+1) % MOD;
auto C = [&](int n, int r) { return r < 0 || r > n ? 0LL : fact[n] * ifact[r] % MOD * ifact[n-r] % MOD; };
```

Fórmulas útiles:

- Suma 1..n = n(n+1)/2; suma de cuadrados = n(n+1)(2n+1)/6.
- Inverso modular con `power(a, MOD-2)` solo si MOD es primo; en otro caso, Euclides extendido.
- Módulo con negativos: `((x % M) + M) % M`.
- Teorema chino del resto, Euler (φ) y Fermat para exponentes grandes: `a^e mod m = a^(e mod φ(m))` si gcd(a, m) = 1.
- Principio de inclusión-exclusión y combinatoria: Catalan(n) = C(2n, n)/(n+1); estrellas y barras: C(n+k-1, k-1).

## 8. Strings

**Función prefijo (KMP)**: `p[i]` = longitud del borde más largo de `s[0..i]`. Buscar `pat` en `text` con `pat + '#' + text`.

```cpp
vi prefix_function(const string& s) {
    int n = sz(s); vi p(n, 0);
    rep(i, 1, n) {
        int k = p[i - 1];
        while (k && s[i] != s[k]) k = p[k - 1];
        if (s[i] == s[k]) k++;
        p[i] = k;
    }
    return p;
}
```

**Hash polinomial** (mod 2^61-1 o doble mod para evitar colisiones): `h[i+1] = (h[i] * B + s[i]) % M`; subcadena \[l, r) = `(h[r] - h[l] * pw[r-l]) % M`. Usar base aleatoria.

Otros: algoritmo Z, Trie para prefijos comunes, Manacher para palíndromos, `s.find(t)`, `s.substr(pos, len)`, `stoi`, `to_string`.

## 9. Bits

```cpp
__builtin_popcountll(x);        // cantidad de bits en 1
__builtin_ctzll(x);             // ceros al final (x != 0)
63 - __builtin_clzll(x);        // posición del bit más alto (x != 0)
x & -x;                         // bit más bajo encendido
x & (x - 1);                    // apagar bit más bajo
(x >> i) & 1;  x |= 1LL << i;  x &= ~(1LL << i);  x ^= 1LL << i;
for (int mask = 0; mask < (1 << n); ++mask) { }   // todos los subconjuntos
```

XOR: `a ^ a = 0`, `a ^ 0 = a`; sirve para encontrar el elemento único entre pares.

## 10. Geometría básica

```cpp
ll cross(pll a, pll b, pll c) {   // > 0: giro antihorario, 0: colineales, < 0: horario
    return (b.fi - a.fi) * (c.se - a.se) - (b.se - a.se) * (c.fi - a.fi);
}
// Área del polígono (fórmula del cordón): sumar cross de vértices consecutivos respecto al origen y dividir entre 2.
// Distancia: hypot(dx, dy). Comparar doubles con EPS. Ángulo: atan2(y, x).
```

Envolvente convexa: Andrew's monotone chain, O(n log n).

## 11. Entrada y salida

```cpp
ios::sync_with_stdio(false); cin.tie(nullptr);
string line; getline(cin, line);          // línea completa (usar cin >> ws antes si venías de cin >>)
while (cin >> x) { }                      // leer hasta EOF
cout << fixed << setprecision(9) << ans; // decimales
cout << '\n';                             // más rápido que endl
```

Si el problema es interactivo, usar `cout << ... << endl;` (o `flush`) después de cada consulta.

## 12. Checklist antes de enviar

1. **Overflow**: ¿algún producto o suma pasa de 2·10^9? Usar `long long` (y `1LL *` en multiplicaciones).
2. **Reiniciar** arreglos y variables globales entre casos de prueba.
3. **Casos borde**: n = 1, entrada vacía, todos iguales, valores máximos y mínimos, grafo no conexo.
4. **Off-by-one** en intervalos: decidir si son \[l, r) o \[l, r\] y mantenerlo.
5. **Formato de salida**: mayúsculas/minúsculas, espacios, salto de línea final.
6. **Tamaño de arreglos**: sumar un margen (N + 5).
7. **Complejidad**: comparar con el límite de n y el tiempo antes de codificar.
8. **Fuerza bruta**: si dudas, escribe una solución lenta y compara con casos aleatorios.
9. **Precisión**: comparar flotantes con EPS, evitar `==`.
10. **Leer bien el enunciado** dos veces: restricciones, orden de entrada y si hay múltiples casos.

## 13. Orden sugerido para resolver

Lee todos los problemas, ordénalos por dificultad estimada, resuelve primero los más fáciles, reparte el trabajo en equipo y no te quedes atascado más de 30 a 40 minutos en un mismo problema sin cambiar de enfoque o de compañero.
