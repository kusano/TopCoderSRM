/*
TopCoder Open 2014 Algorithm Round 2C Medium CliqueGraph

入力に2次元配列が使えないせいか、問題文が分かりづらい。要は、グラフ中のクリーク
（完全部分グラフ）の情報が与えられる。そのままでは辺が多すぎるが、

　　⓪───①　　　　　⓪　　　①
　　│＼　／│＼　　　　　＼　／　＼
　　│　×　│ ④ 　→　　　○　　 ○─④
　　│／　＼│／　　　　　／　＼　／
　　②───③　　　　　②　　　③

このように、クリークを代表する頂点を新たに作り、クリークに含まれる頂点との間に辺
を張って、元の辺を消せば辺の数を減らせる。このグラフ上の最短距離は元のグラフの最
短距離のちょうど2倍になる。このグラフの頂点数は高々2N、辺数は高々4Nであり、各頂
点からの最短距離をBFSで求めれば計算量はO(N²log(N))となる。
*/

#include <vector>
#include <queue>
using namespace std;

//  E[i]は頂点iから出る辺の行き先
//  辺の長さを全て1として、頂点sから各頂点への最短距離を返す
vector<int> BFS(vector<vector<int>> E, int s)
{
    int n = (int)E.size();
    int INF = 99999999;
    vector<int> D(n, INF);
    queue<int> Q;
    D[s] = 0;
    Q.push(s);
    while (!Q.empty()){
        int f = Q.front();
        Q.pop();
        for (int i=0; i<(int)E[f].size(); i++)
            if (D[E[f][i]]==INF)
                D[E[f][i]] = D[f]+1,
                Q.push(E[f][i]);}
    return D;
}

class CliqueGraph{public:
long long calcSum( int N, vector <int> V, vector <int> sizes )
{
    vector<vector<int>> E(N+(int)sizes.size());

    int p = 0;
    for (int i=0; i<(int)sizes.size(); i++)
    {
        for (int j=0; j<sizes[i]; j++)
            E[V[j+p]].push_back(N+i),
            E[N+i].push_back(V[j+p]);
        p += sizes[i];
    }

    long long ans = 0;
    for (int i=0; i<N; i++)
    {
        vector<int> D = BFS(E,i);
        for (int j=0; j<i; j++)
            ans += D[j];
    }

    return ans/2;
}};
