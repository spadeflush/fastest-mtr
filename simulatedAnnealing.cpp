#pragma GCC optimize("Ofast")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
random_device rd;
mt19937 gen(rd());
//TODO: update constant values
double temp = 1;
double mintemp = 0.000000001;
double alpha = 0.995;
double itercnt = 50;
double goal = 1;
int nc = 300000;

const int n = 97, m = 240;
int dist[100][100];
uniform_int_distribution<int> dis(0, n - 1);
uniform_int_distribution<int> dis2(0, n * n);
double fs;

struct sol {
    int arr[n];
};
sol genn() {
    sol e;
    for(int i = 0; i < n; i++) e.arr[i] = i;
    return e;
}
sol adj(sol now) {
    int a = dis(gen);
    int b = dis(gen);
    if(b > a) {
        int k = (int)sqrt(dis2(gen)) % min(15, n - b) + 1;
        while(b > a + 1) {
            for(int i = 0; i < k; i++) {
                swap(now.arr[b + i], now.arr[b - 1 + i]);
            }
            b--;
        }
    }
    else {
        int k = (int)sqrt(dis2(gen)) % min(15, b + 1) + 1;
        while(b < a - 1) {
            for(int i = 0; i < k; i++) {
                swap(now.arr[b - i], now.arr[b + 1 - i]);
            }
            b++;
        }
    }
    return now;
}
double f(sol a) {
    int cnt = 0;
    for(int i = 0; i < n - 1; i++) cnt += dist[a.arr[i]][a.arr[i + 1]];
    return 456./cnt;
}
double prob(double oldsol, double newsol, double tp) {
    return exp((newsol - oldsol) / goal / tp);
}
void printsolution(sol a) {
    for(int i = 0; i < n; i++) cout << a.arr[i] + 1 << ' ';
    cout << '\n';
}
void input() {
    int t, tt, ttt, tttt;
    char comma;
    for(int i = 0; i < m; i++) {
        cin >> t >> comma >> tt >> comma >> ttt >> comma >> tttt;
        tt--; ttt--;
        dist[tt][ttt] = tttt;
    }
}
void precompute() {
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}
void initiaize() {
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
        dist[i][j] = (i == j ? 0 : 1e9);
    }
}
int main() {
    srand(time(NULL));
    freopen("dist.csv", "r", stdin);
    initiaize();
    input();
    precompute();
    double mx = 0;
    while(fs < 1.25) {
        temp = 1;
        double bottom = 1e-6;
        sol solution = genn();
        fs = f(solution);
        int cnt = nc;
        while(cnt > 0) {
            for(int i = 0; i < itercnt; i++) {
                sol newsol = adj(solution);
                double ap = prob(fs, f(newsol), max(temp, bottom));
                if(ap > 1.0 * rand() / RAND_MAX){
                    if(abs(fs - f(newsol)) >= 1e-3) cnt = nc;
                    else cnt--;
                    solution = newsol;
                    fs = f(newsol);
                }
                else cnt--;
            }
            temp *= alpha;
            if(cnt % 50000 > 0 && cnt % 50000 < 50) cerr << cnt << ' ' << temp << ' ' << fs << '\n';
        }
        if(fs < 1.13) continue;
        freopen("MTR_record.txt", "a", stdout);
        time_t now = time(0);
        char* dt = ctime(&now);
        cout << fs << ' ' << dt;
        freopen("MTR_sol.txt", "a", stdout);
        cout << fs << ' ' << dt;
        for(int i = 0; i < n; i++) cout << solution.arr[i] + 1 << ' ';
        cout << '\n';
        cout << 456./fs << '\n';
        cout << '\n';
        mx = max(fs, mx);
        cerr << mx << '\n';
    }
    return 0;
}
