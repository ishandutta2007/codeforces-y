#include <bits/stdc++.h>
using namespace std;
// clang-format off
namespace {  // forbidden c++
// must be an operator that execute from left to right to make sense.
// need concept to use <<, >>, so we use | for now
#define PREFERED_OPERATOR operator|
enum general_operation_t {REVERSE, };
enum comparable_operation_t {SORT, UNIQUE, PREFIX_MIN, PREFIX_MAX, };
enum integer_operation_t {PREFIX_AND, PREFIX_OR, PREFIX_XOR, };
enum number_operation_t {PREFIX_SUM, PREFIX_PROD, };
enum single_input_operation_t {NEXT_INPUT, };
enum array_input_operation_t {ARRAY_INPUT, INDEX_1, };
// enum single_output_operation_t {OUTPUT, OUTPUT_SP, OUTPUT_LN, };
enum array_output_operation_t {OUTPUT_1LINE, OUTPUT_1PER_LINE, INDEX_0, };
template <typename container_t> container_t& PREFERED_OPERATOR(container_t& a, const general_operation_t& op) { switch (op) {case REVERSE: reverse(a.begin(), a.end()); break; default: assert(false);}; return a;}
template <typename container_t> container_t& PREFERED_OPERATOR(container_t& a, const comparable_operation_t& op) { switch (op) { case SORT: {sort(a.begin(), a.end()); break;}; case UNIQUE: {sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end()); break;} case PREFIX_MIN: { for (size_t i = 1; i < a.size(); i++) a[i] = min(a[i], a[i - 1]); break;} case PREFIX_MAX: { for (size_t i = 1; i < a.size(); i++) a[i] = max(a[i], a[i - 1]); break;} default: assert(false);} return a;}
template <typename container_t> container_t& PREFERED_OPERATOR(container_t& a, const number_operation_t& op) { switch (op) { case PREFIX_SUM: { for (size_t i = 1; i < a.size(); i++) a[i] += a[i - 1]; break; } case PREFIX_PROD: { for (size_t i = 1; i < a.size(); i++) a[i] *= a[i - 1]; break; } default: assert(false);} return a;}
template <typename container_t> container_t& PREFERED_OPERATOR(container_t& a, const integer_operation_t& op) { switch (op) { case PREFIX_AND: { for (size_t i = 1; i < a.size(); i++) a[i] &= a[i - 1]; break; } case PREFIX_OR: { for (size_t i = 1; i < a.size(); i++) a[i] |= a[i - 1]; break; } case PREFIX_XOR: { for (size_t i = 1; i < a.size(); i++) a[i] ^= a[i - 1]; break; } default: break;} return a;}
template <typename T> T& operator|(T& var, const single_input_operation_t& op) {cin >> var; return var;}
template <typename container_t> container_t& PREFERED_OPERATOR(container_t& a, const array_input_operation_t& op) { switch (op) { case ARRAY_INPUT: { for (auto&& x : a) x | NEXT_INPUT; break; } case INDEX_1: { a | REVERSE; a.emplace_back(); a | REVERSE; break; } default: assert(0); } return a; }
template <typename container_t> container_t& PREFERED_OPERATOR(container_t& a, const array_output_operation_t& op) {switch (op) { case INDEX_0: { a | REVERSE; a.pop_back(); a | REVERSE; break; } case OUTPUT_1LINE: { for (auto&& x : a) cout << x << ' '; cout << '\n'; break; } case OUTPUT_1PER_LINE: { for (auto&& x : a) cout << x << '\n'; cout << '\n'; break; } default: assert(0); } return a; }
}  // namespace
// clang-format on
constexpr bool MULTI_TEST = 0;
int n, k;
vector<int> g[200001];
bool done[200001];
int f[200001];
void dfs(int u) {
    done[u] = 1;
    for (auto&& v : g[u]) {
        if (done[v]) {
            swap(v, g[u].back());
            g[u].pop_back();
            break;
        }
    }
    f[u] = 0;
    for (auto&& v : g[u]) {
        dfs(v);
        f[u] += f[v];
    }
    f[u]++;
}
constexpr int64_t base = 1e9 + 7;
int64_t power(int64_t a, int64_t x) {
    int64_t res = 1;
    while (x) {
        if (x % 2) (res *= a) %= base;
        (a *= a) %= base;
        x /= 2;
    }
    return res;
}
int64_t fact[200001];
int64_t inv[200001];
int64_t C(int n, int k) {
    if (n < k) return 0;
    return ((fact[n] * inv[k]) % base * inv[n - k]) % base;
}
vector<int> weight;
vector<pair<int, int64_t>> children;
int64_t solve_vertex() {
    children.clear();
    for (auto&& x : weight) children.emplace_back(x, C(x, k));
    int64_t children_size = 0;
    int64_t children_weight = 0;
    for (auto&& [sz, w] : children) {
        children_size += sz;
        (children_weight += w) %= base;
    }
    int64_t res = 0;
    // set this vertex as root
    // use at least 2 children
    (res += (C(children_size, k) - children_weight) * n) %= base;
    // use the root + k - 1
    (res += (C(children_size, k - 1) * n)) %= base;

    // the root is in one of the children
    for (auto&& [sz, w] : children) {
        children_size -= sz;
        (children_weight -= w) %= base;
        int64_t config_count = 0;
        // use at least 2 children
        config_count += C(children_size, k) - children_weight;
        // use the smallest subtree + k - 1
        config_count += C(children_size, k - 1);
        // choose the root
        (config_count *= sz) %= base;
        // multiply with the weight of the subtree
        (res += config_count * (children_size + 1)) %= base;
        children_size += sz;
        (children_weight += w) %= base;
    }
    return res;
}

void solve() {
    cin >> n >> k;
    fact[0] = 1;
    for (int i = 1; i <= n; i++) (fact[i] = fact[i - 1] * i) %= base;
    inv[n] = power(fact[n], base - 2);
    for (int i = n; i >= 1; i--) (inv[i - 1] = inv[i] * i) %= base;
    for (int i = 1, x, y; i < n; i++) {
        cin >> x >> y;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    dfs(1);
    int64_t ans = 0;
    for (int u = 1; u <= n; u++) {
        weight.clear();
        for (auto&& v : g[u]) weight.emplace_back(f[v]);
        if (f[u] != n) weight.emplace_back(n - f[u]);
        (ans += solve_vertex()) %= base;
    }
    (ans += base) %= base;
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    if constexpr (MULTI_TEST) cin >> t;
    while (t--) solve();
}