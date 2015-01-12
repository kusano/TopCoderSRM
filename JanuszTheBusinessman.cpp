#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

class JanuszTheBusinessman{public:
int makeGuestsReturn( vector <int> arrivals, vector <int> departures )
{
    int n = (int)arrivals.size();
    vector<pair<int,int> > A;
    for (int i=0; i<n; i++)
        A.push_back(make_pair(arrivals[i], departures[i]));
    sort(A.begin(), A.end());

    int ans = 0;
    int t = 0;
    for (int i=0; i<n; i++)
        if (t<A[i].first)
        {
            for (int j=i; j<n; j++)
                if (A[j].first<=A[i].second)
                    t = max(t, A[j].second);
            ans++;
        }
    return ans;
}};
