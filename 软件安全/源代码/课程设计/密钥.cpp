#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 10000;
const int MAX = 0x3f3f3f3f;
vector<int>prime, factor, proot;
bool isprime[N];
int vis[10000];

int powMod(int a, int k, int MOD)
{
    int res = 1;
    while(k){
        if(k & 1) res = (1LL * res * a) % MOD;
        k >>= 1;
        a = (1LL * a * a) % MOD;
    }
    return res;
}

bool ispRoot(int p, int rt)
{
    for(int i = 0; i < factor.size(); ++ i){
        int j = factor[i];
        if(powMod(rt, (p - 1) / j, p) == 1) return false;
    }
    return true;
}

void getPROOT(int p)
{
    int ans = 0;
    for(int i = p - 500; i <= p - 1; ++ i){
        memset(vis, 0, sizeof(vis));
        bool flag = 1;
        for(int j = 1; j <= p - 1; ++ j){
            int x = powMod(i, j, p);
            vis[x] ++;
            if(vis[x] >= 2){
                flag = 0;
                break;
            }
        }
        if(flag){
            proot.push_back(i);
        }
    }
}

void getPrime()
{
    prime.clear();
    memset(isprime, 0, sizeof(isprime));
    int tot = 0;
    for(int i = 2; i < N; ++ i){
        if(!isprime[i]){
            if(i > 1000){
                prime.push_back(i);
            }
            for(int j = i + i; j < N; j += i)
                isprime[j] = 1;
        }
    }
}

int getRand(int p)
{
    int d;
    while(true){
        d = rand() % p;
        if(1 < d && d < p - 1) break;
    }
    return d;
}

int main()
{
    getPrime();
    int len = prime.size();
    srand(time(NULL));
    int p = prime[rand() % len];
    getPROOT(p);
    int root = proot[rand() % proot.size()];
    int d = getRand(p);   //私钥
    int y = powMod(root, d, p);  // 公钥
    printf("%04x%04x%04x\n", y, p, root);
    printf("%04x\n", d);

    return 0;
}
