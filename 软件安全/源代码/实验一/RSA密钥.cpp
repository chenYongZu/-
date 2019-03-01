#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 10000;
const int MAX = 0x3f3f3f3f;
vector<int>prime;
bool isprime[N];

int getPhi(int x)
{
    int res = x;
    for(int i = 2; i * i <= x; ++ i){
        if(x % i == 0){
            res = res / i * (i - 1);
            while(x % i == 0) x /= i;
        }
    }
    if(x > 1) res = res / x * (x - 1);
    return res;
}

void getPrime()
{
    prime.clear();
    memset(isprime, 0, sizeof(isprime));
    for(int i = 2; i < N; ++ i){
        if(!isprime[i]){
            if(i > 1000) prime.push_back(i);
            for(int j = i + i; j < N; j += i) isprime[j] = 1;
        }
    }
}

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

pair<int, int> getE(int phi){
    int e, d;
    while(1){
        e = rand() % min(phi, MAX);
        int gcd = __gcd(phi, e);
        if(gcd == 1) break;
    }
    d = powMod(e, getPhi(phi) - 1, phi);
    return make_pair(e, d);
}

int main()
{
    getPrime();
    int len = prime.size();
    srand(time(NULL));
    int p = prime[rand() % len], q = prime[rand() % len];
    while(p == q) q = prime[rand() % len];
    int phi = getPhi(p * q);
    int n = p * q;
    pair<int,int> tmp = getE(phi);
    int e = tmp.first, d = tmp.second;

    printf("%08x%08x%08x\n", n, phi, e);
    printf("%04x%04x%08x%08x\n", p, q, phi, d);
    return 0;
}
