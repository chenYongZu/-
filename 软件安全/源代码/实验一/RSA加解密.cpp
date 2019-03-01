#include <bits/stdc++.h>

using namespace std;

const int Digit = 8;
typedef long long LL;
char in_path[100], out_path[100];
char public_key[100], private_key[100];

int powmod(int a, int k, int MOD)
{
    int res = 1;
    while(k){
        if(k & 1) res = (1LL * a * res) % MOD;
        k >>= 1;
        a = (1LL * a * a) % MOD;
    }
    return res;
}

void Encr(int e, int n)
{
    freopen(in_path, "r", stdin);
    freopen(out_path, "w", stdout);
    int m;
    char ch;
    while(ch = getchar()){
        if(ch == EOF) break;
        m = powmod(ch, e, n);
        printf("%08x", m);
    }
    fclose(stdin);
    fclose(stdout);
}

int hextodec(char s[], int be, int ed)
{
    int res = 0;
    for(int i = be; i < ed; ++ i){
        if('0' <= s[i] && s[i] <= '9'){
            res = res * 16 + (s[i] - '0');
        }
        else res = res * 16 + (s[i] - 'a' + 10);
    }
    return res;
}

void Deci(int d, int n)
{
    freopen(in_path, "r", stdin);
    freopen(out_path, "w", stdout);
    char ch[Digit + 1];
    while(ch[0] = getchar()){
        if(ch[0] == EOF) break;
        for(int i = 1; i < Digit; ++ i) ch[i] = getchar();
        int c = hextodec(ch, 0, Digit);
        int m = powmod(c, d, n);
        printf("%c", m);
    }

    fclose(stdout);
    fclose(stdin);
}


bool check_key_len(char public_key[], char private_key[])
{
    int lenpu = strlen(public_key), lenpr = strlen(private_key);
    if(lenpu != lenpr || lenpu != 24) return false;
    return true;
}

bool check_keynum(int d, int e, int n, int pq, int p1, int p2)
{
    if(p1 != p2 || n != pq) return false;
    if((1LL * d * e % p1) != 1) return false;
    return true;
}
int main()
{
    int e, d, n, op;
    static char public_key[100], private_key[100];
    puts("输入 1 加密，输入 2 解密:");
    while(~scanf("%d",&op)){
        if(op == 1){
            puts("输入公钥:");
            scanf("%s", public_key);
            n = hextodec(public_key, 0, 8);
            e = hextodec(public_key, 16, 24);
            puts("输入加密文件路径");
            scanf("%s", in_path);
            puts("输入加密后文件名称路径");
            scanf("%s", out_path);
            Encr(e, n);
        }
        else {
            puts("输入公钥和私钥");
            scanf("%s %s", public_key, private_key);
            if(!check_key_len(public_key, private_key)){
                puts("解密的公私钥不匹配！");
                puts("ddddd");
            }
            else{
                int pq = hextodec(private_key, 0, 4) * hextodec(private_key, 4, 8);
                int phi_pri = hextodec(private_key, 8, 16), phi_pub = hextodec(public_key, 8, 16);
                d = hextodec(private_key, 16, 24);
                e = hextodec(public_key, 16, 24);
                n = hextodec(public_key, 0, 8);

                if(!check_keynum(d, e, n, pq, phi_pri, phi_pub)){
                    puts("解密的公私钥不匹配！");
                }
                else{
                    puts("输入需要解密文件路径:");
                    scanf("%s", in_path);
                    puts("输入解密密后文件名称路径:");
                    scanf("%s", out_path);
                    Deci(d, n);
                }
            }
        }
    }
    return 0;
}
