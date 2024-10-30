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
template <typename inputable_t> inputable_t& PREFERED_OPERATOR(inputable_t& var, const single_input_operation_t& op) {cin >> var; return var;}
template <typename container_t> container_t& PREFERED_OPERATOR(container_t& a, const array_input_operation_t& op) { switch (op) { case ARRAY_INPUT: { for (auto&& x : a) x | NEXT_INPUT; break; } case INDEX_1: { a | REVERSE; a.emplace_back(); a | REVERSE; break; } default: assert(0); } return a; }
template <typename container_t> container_t& PREFERED_OPERATOR(container_t& a, const array_output_operation_t& op) {switch (op) { case INDEX_0: { a | REVERSE; a.pop_back(); a | REVERSE; break; } case OUTPUT_1LINE: { for (auto&& x : a) cout << x << ' '; cout << '\n'; break; } case OUTPUT_1PER_LINE: { for (auto&& x : a) cout << x << '\n'; cout << '\n'; break; } default: assert(0); } return a; }
}  // namespace
// clang-format on

constexpr bool MULTI_TEST = 0;
// #define SKIP_ASSERT
#ifdef SKIP_ASSERT
#define assert(x) (x)
#endif
constexpr int base = 998'244'353;
int sum[20];

class state_t {
public:
    int f[2][2];

    static state_t from_digit(int d) {
        state_t res;
        res.f[0][0] = sum[d];
        res.f[0][1] = d == 1;
        res.f[1][0] = sum[10 + d];
        res.f[1][1] = 0;
        return res;
    }

    friend state_t combine(const state_t& l, const state_t& r) {
        state_t res;
        for (int i = 0; i <= 1; i++)
            for (int j = 0; j <= 1; j++)
                res.f[i][j] =
                        ((static_cast<int64_t>(l.f[i][0]) * r.f[0][j]) + (static_cast<int64_t>(l.f[i][1]) * r.f[1][j])) % base;
        return res;
    }
};

string c;
class segment_tree_t {
public:
    segment_tree_t *left, *right;
    int l, r, m;
    state_t state;

    segment_tree_t(int l, int r) : l(l), r(r), m((l + r) / 2) {
        if (l == r) state = state_t::from_digit(c[l] - '0');
        else {
            left = new segment_tree_t(l, m);
            right = new segment_tree_t(m + 1, r);
            state = combine(left->state, right->state);
        }
    }

    void update(int u) {
        if (l == r) {
            state = state_t::from_digit(c[l] - '0');
        } else {
            if (m >= u) left->update(u);
            else right->update(u);
            state = combine(left->state, right->state);
        }
    }
};

void solve() {
    for (int i = 0; i <= 9; i++)
        for (int j = 0; j <= 9; j++) sum[i + j]++;
    int n, m;
    cin >> n >> m;
    cin >> c;
    c = 'a' + c;
    auto tree = new segment_tree_t(1, n);
    for (int i = 1, x; i <= m; i++) {
        cin >> x;
        cin >> c[x];
        tree->update(x);
        cout << tree->state.f[0][0] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    if constexpr (MULTI_TEST) cin >> t;
    while (t--) solve();
}