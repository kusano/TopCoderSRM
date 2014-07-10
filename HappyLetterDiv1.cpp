/*
TopCoder SRM 627 Div 1 Easy HappyLetterDiv1

残す文字と個数を決めて、それ以外の文字を全て消せるか調べれば良い。個数が偶数で、
最多の文字の個数が他の文字の個数の和以下ならば、消せる。
*/

#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class HappyLetterDiv1{public:
string getHappyLetters( string letters )
{
    vector<int> C(256);
    for (char &c : letters)
        C[c]++;

    string ans;
    for (int c=0; c<256; c++)
    {
        bool ok = false;
        for (int i=1; i<=C[c]; i++)
        {
            C[c] -= i;
            int s = accumulate(C.begin(), C.end(), 0);
            int m = *max_element(C.begin(), C.end());
            if (s%2==0 && m<=s-m)
                ok = true;
            C[c] += i;
        }
        if (ok)
            ans += (char)c;
    }

    return ans;
}};
