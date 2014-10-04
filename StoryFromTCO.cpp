/*
TopCoder SRM 635 Div 1 Medium StoryFromTCO

cutoffが小さい順に貪欲にplacesを割り当てていく。
places[i]が未使用で、places[i]<=cutoff[i]が満たされているならば、そのまま。
cutoffが小さい順に見ているので、cutoff[i]以下のplacesを区別する意味が無い。
そうではない場合、もしこれまで見てきた未使用のplaces[i]があるならば使う。
ここで使えるならば以降のどこにでも使えるので区別する意味は無い。
無ければ、i以降の使えるplacesの中で最もcutoffが大きいものを選択する。
cutoffが小さいものを使うと、Example 4で無駄な交換が発生する。
使えるものが何も無ければ、return -1。
証明し切れていないような気もするけど、通った。
*/

#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

class StoryFromTCO{public:
int minimumChanges( vector <int> places, vector <int> cutoff )
{
    int n = (int)places.size();

    vector<pair<int,int> > P(n);
    for (int i=0; i<n; i++)
        P[i] = make_pair(cutoff[i], places[i]);
    sort(P.begin(), P.end());
    for (int i=0; i<n; i++)
        places[i] = P[i].second,
        cutoff[i] = P[i].first;

    int ans = 0;
    vector<bool> used(n);

    for (int i=0; i<n; i++)
        if (used[i] || places[i]>cutoff[i])
        {
            int s = -1;
            for (int j=0; j<i; j++)
                if (!used[j] && places[j]<=cutoff[i])
                    s = j;
            if (s==-1)
                for (int j=i+1; j<n; j++)
                    if (!used[j] && places[j]<=cutoff[i])
                        s = j;
            if (s==-1)
                return -1;
            ans++;
            used[s] = true;
        }
        else
        {
            used[i] = true;
        }

    return ans;
}};
