#include <bits/stdc++.h>

using namespace std;

const int LEN = 100;
char snum[LEN];
char num[LEN];

bool isDigit(char ch){return '0' <= ch && ch <= '9';}
bool isSign(char ch){return ch == '-' || ch == '+';}
bool isPoint(char ch){return ch == '.';}
void outPutError(){puts("输入格式错误！请重新输入！");}
void outPutCorrect(double ans){printf("输入是：%s\n输出答案是：%f\n", snum, ans);}
int main()
{
    while(~scanf("%s", snum)){
        int len = strlen(snum);
        bool err = false;
        if(isPoint(snum[len - 1])) err = true;
        if(isSign(snum[0])) memcpy(num, snum + 1, -- len);
        else memcpy(num, snum, len);
        int pointnum = 0;
        int pos = len - 1;
        for(int i = 0; i < len; ++ i){
            if(isPoint(num[i])) pos = i, pointnum ++;
            if(pointnum >= 2) {
                err = true;
                break;
            }
        }
        if(pointnum == 1){
            memcpy(num + pos, num + pos + 1, len - pos - 1);
            pos --, len --;
        }
        for(int i = 0; i < len; ++ i){
            if(!isDigit(num[i])){
                err = true;
                break;
            }
        }
        if(err){
            outPutError();
            continue;
        }
        double tmp = 1, ans = 0;
        for(int i = 0; i < pos; ++ i) tmp *= 10;
        for(int i = 0; i < len; ++ i, tmp /= 10){
            ans += tmp * (num[i] - '0');
        }
        outPutCorrect(ans * ans);
    }
    return 0;
}
