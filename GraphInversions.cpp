/*
TopCoder SRM 627 Div 1 Medium GraphInversions

頂点数と辺数が等しいので、グラフはちょうど1個の閉路を含む。このグラフは閉路の各
頂点に木が付いた形をしている。このグラフ上の単純道（各頂点を高々1個しか含まない
道）はO(N²)本である。始点を終点を決めると、同じ木の中に終点があるか、始点から閉
路上の頂点に向かって木を上り閉路を左右どちらかに回り終点に向かって木を降りるかの
3通りしかない。よって始点を決めてグラフを辿ればO(N²)で全ての単純路が列挙できる。
inversionはグラフを辿りながら、これまでのパスに含まれる頂点のうち、最後に追加し
た頂点の値よりも大きいものの個数を足していけば良い。単純に計算するとO(N)になって
しまうが、0-1000を幅32の32個のブロックに分けて、ブロック中に含まれる頂点の個数も
管理しておくことでO(√N)で求められる（平方分割）。
*/

#include <vector>
#include <algorithm>
#include <climits>
#include <functional>
using namespace std;

class GraphInversions{public:
int getMinimumInversions( vector <int> A, vector <int> B, vector <int> V, int K )
{
    int N = (int)A.size();
    vector<vector<int>> E(N);
    for (int i=0; i<N; i++)
        E[A[i]].push_back(B[i]),
        E[B[i]].push_back(A[i]);

    vector<int> used(N);
    int C[1024] = {};
    int Cs[32] = {};
    int k = 0;
    int ans = INT_MAX;

    function<void (int, int)> search;
    search = [&](int p, int s) -> void
    {
        used[p] = true;
        C[V[p]]++;
        Cs[V[p]/32]++;
        k++;

        int t;
        for (t=V[p]+1; t%32!=0; t++)
            s += C[t];
        for (; t<1024; t+=32)
            s += Cs[t/32];

        if (k==K)
            ans = min(ans, s);
        else
            for (int c : E[p])
                if (!used[c])
                    search(c, s);

        Cs[V[p]/32]--;
        C[V[p]]--;
        k--;
        used[p] = false;
    };
    
    for (int i=0; i<N; i++)
        search(i, 0);

    return ans<INT_MAX ? ans : -1;
}};
