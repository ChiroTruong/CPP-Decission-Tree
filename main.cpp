#include <bits/stdc++.h>

using namespace std;

template<typename T,typename...A>void print(const T&t,const A&...a){
std::cout<<t;((std::cout<<' '<<a),...);std::cout<<'\n';}
template<typename...A>void fprint(A&&...a){(cout<<...<<a);}
template<typename...A>void scan(A&...a){((cin>>a),...);}
#define FOR(x, a, b) for (int x = (a); (x) <= (b); ++(x))
#define FOD(x, a, b) for (int x = (a); (x) >= (b); --(x))
#define FOE(x, a)    for (auto &x : (a))
#define ll long long

const ll  MOD  = 1e9 + 7;
const int MAXN = 2e5 + 7;
const int MAX_DEPTH = 4;
const int MIN_SAMPLE_SPLIT = 1;

struct Node{
    Node *child_l, *child_r;
    vector<pair<double, double>> store;
    double val, split_point;
    int depth;
};

Node root;

inline double deviation(double total, double total_sq, int amount){
    double var = (total_sq / amount) - ((total / amount) * (total / amount));
    return max(0.0, var);
}

void build(Node &node){
    if (node.store.size() <= MIN_SAMPLE_SPLIT || node.depth >= MAX_DEPTH){
        node.child_l = NULL;
        node.child_r = NULL;
        node.val = 0;
        FOE(x, node.store) node.val += x.second;
        if (!node.store.empty()) node.val /= node.store.size();
        return;
    }

    double total = 0, total_sq = 0;

    FOE(x, node.store){
        total += x.second;
        total_sq += x.second * x.second;
    }

    double min_epsilon = 1e16;
    double left_sum = 0;
    double left_sum_sq = 0;
    double split_idx = -1;
    double epsilon;
    
    FOR(i, 0, (int)node.store.size() - 2){
        left_sum += node.store[i].second;
        left_sum_sq += node.store[i].second * node.store[i].second;
        if (node.store[i].first == node.store[i + 1].first) continue;
        int left_amount = i + 1;
        int right_amount = node.store.size() - left_amount;
        epsilon = left_amount * deviation(left_sum, left_sum_sq, i + 1);
        epsilon += right_amount * deviation(total - left_sum, total_sq - left_sum_sq, right_amount);
        if (min_epsilon > epsilon){
            min_epsilon = epsilon;
            split_idx = i;
        }
    }

    node.val = node.store.empty() ? 0 : total / node.store.size();

    if (split_idx == -1){
        node.child_l = NULL;
        node.child_r = NULL;
        return;
    }

    Node *Left = new Node;
    Node *Right = new Node;
    node.split_point = (node.store[split_idx].first + node.store[split_idx + 1].first) / 2.0;
    Left->store.assign(node.store.begin(), node.store.begin() + split_idx + 1);
    Right->store.assign(node.store.begin() + split_idx + 1, node.store.end());
    Left->depth = node.depth + 1;
    Right->depth = node.depth + 1;

    node.child_l = Left;
    node.child_r = Right;
    build(*Left);
    build(*Right);
}

double query(const Node &node, double x){
    if (node.child_l == NULL) return node.val; 
    if (x <= node.split_point) return query(*node.child_l, x);
    return query(*node.child_r, x);
}

void solve(void){
    int n, q;
    scan(n, q);
    root.depth = 1;
    root.store.resize(n);
    FOR(i, 0, n - 1) scan(root.store[i].first, root.store[i].second);
    sort(root.store.begin(), root.store.end());
    build(root);
    double x;
    FOR(i, 1, q){
        scan(x);
        print(query(root, x));
    }
}

int32_t main(void){
    #ifdef IS_CHIRO
        freopen("INPUT.INP", "r", stdin);
        freopen("OUTPUT.OUT", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    solve();
    return 0;
}

/*
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣠⣤⣤⣤⣤⣤⣤⣤⣤⣤⣀⣀⣀⣀⣀⣀⣀⣤⣴⣖⢂⣀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⣄
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⣿⠿⠁⠘⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠈⠘⠻⢿⣿⣿⣿⣶⡀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⣿⠏⣀⡀⠀⠮⠿⢾⣿⣿⣿⣿⣿⣿⡿⠿⠿⠛⠛⠁⠀⢘⡏⣿⣿⡷⠿⢿⣿⣿⡟⠀⠀⠀⠀⠘⣿⣿⣿⠿⠏
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿⡏⣽⠏⠁⠀⠀⠀⠉⣟⣿⠿⠛⠛⠉⠀⠀⠀⠀⢀⣀⠀⣰⣿⣿⣿⣧⠀⠀⠁⠈⠀⠀⢀⣤⠀⢰⣿⣿⣿⣿⡀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣏⣰⣿⢀⣠⣦⣤⡄⠀⠀⠀⠀⠀⠀⣀⣀⣀⣴⣶⣿⣯⣤⣿⣿⣿⣿⣿⢠⣤⣴⡄⣰⣶⣾⣿⣦⣰⣿⣿⣿⣿⣳
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⣿⠇⢸⣿⣿⣿⣇⣘⣷⡆⠀⢰⣿⣿⣿⣿⣿⠛⣿⣿⣿⣿⣿⣿⣿⡇⣿⣿⣿⣷⣿⣿⣿⣿⣿⣏⣹⣿⣿⣿⡆
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣿⣿⢀⣿⣿⣿⣯⠻⣿⣿⡇⠀⣿⣿⣿⣿⣿⡇⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣺⣿⣿⣯⣿⣿⣿⣿⣿⣿⣿
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣽⣿⣿⣿⣿⢸⣿⣿⣿⢋⣾⣿⣿⡇⢸⣿⣿⣿⣿⣿⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣼⣿⣿⣿⣧⣼⣿⣿⣿⣿⡟⣰⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠸⠇
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⡿
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠙⠃
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠿⠙⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⣿⣿⠋⠀⢸⣿⣿⠻⣿⡿⢰⣿⣿⣿⡹⠟
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⣼⡿⠿⠻⠏⠻⡿⠀⠿⠏⠀⠰⠈⠁⠃⠀⠁⠁⣾⣿⣿⣿⡇
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡿⣿⡿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣭⠀⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠩⠃⠀⠀⠀⣼⣿⣿⣿⢿⡿⢀⡀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠘⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⠀⠀⠀⠀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⠛⣿⡬⠀⠀⠈⠳⣄⡀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡴⠁⠀⠈⠇⠘⣿⠹⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⠑⠠⠈⢭⣉⣑⡲⠀⠀⢀⣴⣿⣿⣿⡟⣄⢹⠁⠀⠀⠀⠀⠀⠱⡀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⠎⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣷⡀⠀⠐⠢⣀⠀⠀⠀⠀⠀⣠⣶⣶⣿⣿⣿⣿⡟⣵⣉⡇⠀⠀⠀⠀⠀⠀⠀⠘⠒⢤
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡔⠃⠀⠀⠀⠀⠀⠀⠀⠀⡄⡆⣿⣿⣿⣿⣿⣿⡧⠀⠀⠀⠀⠈⠓⠀⣶⣾⣿⣿⣿⣿⣿⣿⣿⣇⣇⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⡆
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣜⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⡇⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⣰⣿⣿⣿⣿⣿⣿⣿⣿⠟⢸⢘⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡞
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡾⡅⠈⠉⢧⡀⠀⠀⠀⠀⠀⠀⠀⠀⡇⡇⣿⣿⣿⣿⣿⣿⣷⠀⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⣿⣿⣿⡿⢀⡏⣼⠦⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠃
⠀⠀⠀⠀⠀⠀⠀⠀⣠⠖⠃⠹⣄⠀⠘⣷⡀⠀⠀⠀⠀⠀⠀⠀⡧⣗⡈⠻⢿⣿⣿⣿⣿⡆⠀⠀⠀⢠⣿⣿⣿⣿⣿⡿⠟⠛⣛⣡⠞⢁⠃⠀⠈⡆⠀⠀⠀⠀⠀⠀⠀⠀⠻⡄
⠓⠲⣄⠀⠀⢀⣠⠎⠁⠀⠀⠀⠘⢦⠀⠈⣿⡀⠀⠀⠀⠀⠀⠀⡧⢍⡙⠿⣍⠙⢻⣿⣿⣿⡆⠀⢀⣼⣿⡿⢟⣉⠤⠖⣛⣉⡥⠶⣶⡏⢀⡀⠘⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣻
⠀⠀⠈⠉⠒⠋⠁⠀⠀⠀⠀⠀⠀⠈⢃⡀⠘⣧⡀⠀⠀⠀⠀⠀⣷⣄⠙⠂⠄⢙⡂⠉⠛⣛⣿⠀⡘⠛⠉⣒⠋⠁⠐⠚⠁⣄⣤⣴⣿⡇⠀⡁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⠁
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢧⠀⠘⣿⡄⠀⠀⠀⠰⠏⠉⠀⠀⠀⠀⠈⠁⠒⠄⠀⠰⠄⠀⠉⠀⠀⠀⠀⠀⠀⠻⠷⣿⣿⠀⠀⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⡀⠀⠈⢿⣆⠀⣴⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡄⠀⠀⠀⠀⢸⣿⣿⡄⠀⢶⣤⣀⡀⠀⠀⠀⠀⠀⣀⣀⣴
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠠⠖⠉⠀⠀⠙⠦⠄⠠⠛⠁⣷⣤⣶⣶⠶⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣷⣶⣦⣼⣿⣿⣧⠀⣦⡀⠉⠙⠛⠓⠒⠿⠛⠛⠛⠙⠇
⠒⠦⣄⣀⣀⣠⠴⠒⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠏⠀⠰⠁⠀⠀⠀⠀⠀⠀⠀⠀⣰⡟⠀⠀⠀⠀⠀⠀⢿⣿⣿⡏⠉⠉⠁⠀⠀⠈⢉⠙⠒⠒⠒⠒⠚⠋⠛⠛⠁
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⣦⡀⠀⠀⠀⠀⠀⠀⢀⣤⣾⣿⡅⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⠀⠀⠀⠀⠀⠀⢨⠀⠀⠀⠀⠀⠀⠀⠀⡇
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡟⠁⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣾⡀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⡇⠀⠀⠀⠀⠀⠠⠀⠀⠀⠀⠀⠀⠀⠀⠃
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⠀⢀⡤⠤⣄⠀⠀⠀⣴⣿⣿⣿⡏⡆⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠃
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠻⢋⠀⠀⠀⢙⡢⢶⣿⣿⣿⡟⠃⠇⠀⠀⠀⣀⡤⠴⠚⠛⠿⣛⠻⠀⠀⠀⠀⠀⢀⠂⠀⠀⠀⠀⠀⠀⠀⡅
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢓⠤⠀⠉⠀⠀⠘⠛⢿⡋⠐⢶⡤⠐⠮⣁⠀⠒⢄⠀⢀⣀⣭⠄⣀⠒⠳⠚⠙⠀⠀⠀⠀⠀⠀⠀⠀⡁
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⠀⠀⠀⠀⠀⠂⠓⠛⠃⠀⠈⠁⠀⠘⠁⠀⠪⠎⠩⢭⣍⡀⢀⡀⢀⣀⡀⣀⡀⠀⠀⠀⠀⠀⠀⡁
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠁⠐⠒⠒
*/

