/*
TopCoder SRM626 Div1 Easy FixedDiceGameDiv1

A[x]をAliceの目がxになる確率、B[y]をBobの目がyになる確率とする。
Aliceが勝つxとyの組み合わせについて、A[x]*B[y]を合計すればAlceが勝つ確率となる。
x*A[x]*B[y]の合計がAliceの目の期待値のうちのAliceが勝つ分なので、Aliceが勝つ確率
で割れば、求める答えとなる。
*/

#include <vector>
#include <algorithm>
using namespace std;

class FixedDiceGameDiv1{public:
double getExpectation( int a, int b, int c, int d )
{
    int M = max(a*b, c*d) + 1;

    //  b面のダイスをa個振ったときの目の確率を求める
    auto calc = [&](int a, int b) -> vector<double>
    {
        vector<double> P(M);
        P[0] = 1.0;
        for (int i=0; i<a; i++)
        {
            vector<double> T = P;
            P = vector<double>(M);
            for (int j=0; j<M-b; j++)
                for (int k=1; k<=b; k++)
                    P[j+k] += T[j]/b;
        }
        return P;
    };

    vector<double> A = calc(a, b);
    vector<double> B = calc(c, d);

    //  Aliceが勝つ確率
    double p = 0.0;
    //  Aliceの目の期待値
    double s = 0.0;

    for (int i=0; i<M; i++)
    for (int j=0; j<i; j++)
    {
        p += A[i]*B[j];
        s += A[i]*B[j] * i;
    }

    return p>0.0 ? s/p : -1.0;
}};
