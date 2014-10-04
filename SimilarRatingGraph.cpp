/*
TopCoder SRM 635 Div 1 Easy SimilarRatingGraph

素直に似ている区間の開始位置の組み合わせを試せば良い。
片方のdateの長さを他方に掛ければ整数で計算できる。
*/

#include <vector>
#include <algorithm>
using namespace std;

class SimilarRatingGraph{public:
double maxLength( vector <int> date, vector <int> rating )
{
    int n = (int)date.size();
    double ans = 0;

    for (int a=0; a+1<n; a++)
    for (int b=0; b+1<n; b++)
    if (a!=b)
    {
        double l = 0;
        long long f1 = (date[a+1]-date[a]);
        long long f2 = (date[b+1]-date[b]);
        for (int i=1; a+i<n && b+i<n; i++)
        {
            long long d1 = date[a+i]-date[a+i-1];
            long long r1 = rating[a+i]-rating[a+i-1];
            long long d2 = date[b+i]-date[b+i-1];
            long long r2 = rating[b+i]-rating[b+i-1];

            if (!(d1*f2==d2*f1 && r1*f2==r2*f1))
                break;
            l += hypot((double)d1, (double)r1);
        }
        ans = max(ans, l);
    }

    return ans;
}};
