#include <bits/stdc++.h>

using namespace std;

const int Digit = 12;
typedef long long LL;
const int MAX = 50;
char in_path[MAX] , out_path[MAX];
char public_key[MAX], private_key[MAX];

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

int getRand(int p){
    int k;
    do{
        k = rand() % p;
    }while(1 >= k || k >= p - 1);
    return k;
}

void Encr(int y, int root, int p)
{
    freopen(in_path, "r", stdin);
    freopen(out_path, "w", stdout);
    int k, u, c1, c2;
    char ch;
    while(ch = getchar()){
        if(ch == EOF) break;
        k = getRand(p);
        u = powmod(y, k, p);
        c1 = powmod(root, k, p);
        c2 = 1LL * u * ch % p;
        printf("%04x%08x",c1,c2);
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

void Deci(int d, int p)
{
    freopen(in_path, "r", stdin);
    freopen(out_path, "w", stdout);
    char ch[Digit + 1];
    while(ch[0] = getchar()){
        if(ch[0] == EOF) break;
        for(int i = 1; i < Digit; ++ i)
            ch[i] = getchar();
        int c1 = hextodec(ch, 0, 4);
        int c2 = hextodec(ch, 4, 12);
        int v = powmod(c1, d, p);
        int m = 1LL * powmod(v, p - 2, p) * c2 % p;
        printf("%c", m);
    }
    fclose(stdout);
    fclose(stdin);
}


bool check_key_len(char public_key[], char private_key[])
{
    int lenpu = strlen(public_key);
    int lenpr = strlen(private_key);
    if(lenpu != 12 || lenpr != 4)
        return false;
    return true;
}

bool check_keynum(int y, int p, int root, int d)
{
    int tmp = powmod(root, d, p);
    if(tmp != y) return false;
    return true;
}

int main()
{
    int d, n, op, y, root, p;
    static char public_key[100], private_key[100];
    puts("输入 1 加密，输入 2 解密:");
    while(~scanf("%d",&op)){
        if(op == 1){
            puts("输入公钥:");
            scanf("%s", public_key);
            y = hextodec(public_key, 0, 4);
            p = hextodec(public_key, 4, 8);
            root = hextodec(public_key, 8, 12);
            puts("输入加密文件路径");
            scanf("%s", in_path);
            puts("输入加密后文件名称路径");
            scanf("%s", out_path);
            Encr(y, root, p);
        }
        else {
            puts("输入公钥和私钥");
            scanf("%s %s", public_key, private_key);
            if(!check_key_len(public_key, private_key)){
                puts("解密的公私钥不匹配！");
                break;
            }
            else{
                y = hextodec(public_key, 0, 4);
                p = hextodec(public_key, 4, 8);
                root = hextodec(public_key, 8, 12);
                d = hextodec(private_key, 0, 4);

                if(!check_keynum(y, p, root, d)){
                    puts("解密的公私钥不匹配！");
                    break;
                }
                else{
                    puts("公私钥匹配\n输入需要解密文件路径:");
                    scanf("%s", in_path);
                    puts("输入解密密后文件名称路径:");
                    scanf("%s", out_path);
                    Deci(d, p);
                }
            }
        }
    }
    return 0;
}
