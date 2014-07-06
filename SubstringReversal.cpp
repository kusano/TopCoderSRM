/*
TopCoder Open Algorithm 2014 Round 2C Easy SubstringReversal

答えのxは自分より右に自分より辞書順で小さい文字が存在する最左の位置である。ある
位置がこの条件を満たしたときに、より右が答えのxにならないことは自明。ある位置xが
この条件を満たし、xより左の位置がこの条件を満たさないのは、例えば、
　S = aabaaaaa, x = 2
この場合、bをより右に送るために、x<2は答えにならない。
yについては全て試せば良い。
*/

#include <string>
#include <algorithm>
#include <vector>
using namespace std;

class SubstringReversal{public:
vector<int> solve(string S)
{
    int n = (int)S.size();

    for (int x=0; x<n; x++)
    if (*min_element(S.begin()+x, S.end()) < S[x])
    {
        string as = S;
        int ay = 0;
        for (int y=x; y<n; y++)
        {
            string s = S;
            reverse(s.begin()+x, s.begin()+y+1);
            if (s < as)
                as = s,
                ay = y;
        }
        return vector<int>{x, ay};
    }

    return vector<int>{0, 0};
}};
