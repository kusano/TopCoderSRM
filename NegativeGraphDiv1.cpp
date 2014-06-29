/*
TopCoder SRM626 Div1 Easy FixedDiceGameDiv1

行列の累乗の高速化と同じようなことをする。
C[x][y]をxからyへspecial powerを1回使った場合の最小コストとすると、
min(C[x][z], C[z][y])はspecial powerを2回使ってxからyに移動する最小コストとなる。
同様に4回、8回…special powerを使った場合の最小コストが求められる。これらを組み
合わせることで、ちょうどcharges回special powerを使った最小コストが計算できる。
special powerを使って何もしない（コスト0で同じ地点に戻る）ことを認めると、
special powerの使用回数がcharges回未満の場合に対応できる。
*/

#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class NegativeGraphDiv1{public:
long long findMin( int N, vector <int> from, vector <int> to, vector <int> weight, int charges )
{
    for (int i=0; i<(int)from.size(); i++)
        from[i]--,
        to[i]--;

    vector<vector<long long>> I(N, vector<long long>(N, 1000000000LL));
    for (int i=0; i<N; i++)
        I[i][i] = 0LL;
    
    //  C0[x][y]: special powerを使わずにxからyに行く最小コスト
    vector<vector<long long>> C0 = I;
    for (int i=0; i<(int)from.size(); i++)
        C0[from[i]][to[i]] = min(C0[from[i]][to[i]], (long long)weight[i]);
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            for (int k=0; k<N; k++)
                C0[j][k] = min(C0[j][k], C0[j][i]+C0[i][k]);

    //  C1[x][y]: special powerを1回、通常移動無しで、xからyに行く最小コスト
    vector<vector<long long>> C1 = I;
    for (int i=0; i<(int)from.size(); i++)
        C1[from[i]][to[i]] = min(C1[from[i]][to[i]], -(long long)weight[i]);

    //  C[x][y] = min(A[x][z]+B[z][y]) 
    auto mul = [&](vector<vector<long long>> A, vector<vector<long long>> B)
    {
        vector<vector<long long>> C = I;
        for (int i=0; i<N; i++)
            for (int j=0; j<N; j++)
                for (int k=0; k<N; k++)
                    C[i][j] = min(C[i][j], A[i][k]+B[k][j]);
        return C;
    };

    vector<vector<long long>> C = mul(mul(C0,C1),C0);
    vector<vector<long long>> A = C0;

    for ( ; charges>0; charges/=2)
    {
        if (charges%2 != 0)
            A = mul(A,C);
        C = mul(C,C);
    }

    return A[0][N-1];
}};
