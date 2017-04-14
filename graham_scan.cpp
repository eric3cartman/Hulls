#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define x first
#define y second

pair<int, int> pivot;

//0-->colinear 1-->clokwise 2-->counter-clockwise
int orientation(pair<int, int> p, pair<int, int> q, pair<int, int> r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) return 0; 
    return (val > 0)? 1: 2; 
}

int sqrDist(pair<int, int> a, pair<int, int> b)  {
    int dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

bool compare(pair<int, int> a, pair<int, int> b)  {
    int order = orientation(pivot, a, b);
    if (order == 0)
        return sqrDist(pivot, a) < sqrDist(pivot, b); //nearest point first
    return (order == 2);
}

void graham_scan(vector<pair<int, int> > &P)    {
    int n=P.size();
    stack<pair<int, int> > hull;
    
    int Y = 0;
    for (int i = 1; i < n; i++)
        if (P[i] < P[Y])
            Y = i;

    pair<int, int> temp = P[0];
    P[0] = P[Y];
    P[Y] = temp;

    // sort the remaining point according to polar order about the pivot
    pivot = P[0];
    sort(P.begin() + 1, P.end(), compare);
    
    //remove colinear points
    int m = 1;
    for (int i=1; i<n; i++)
    {
       while (i < n-1 && orientation(P[0], P[i],P[i+1]) == 0) i++;
       P[m] = P[i];
       m++;
    }
 
    if (m < 3) return;
   
    hull.push(P[0]);
    hull.push(P[1]);
    hull.push(P[2]);

    for (int i = 3; i < m; i++) {
        pair<int, int> top = hull.top();
        hull.pop();
        while (orientation(hull.top(), top, P[i]) != 2)   {
            top = hull.top();
            hull.pop();
        }
        hull.push(top);
        hull.push(P[i]);
    }
   // print hull
   while (!hull.empty())
   {
       pair<int, int> p = hull.top();
       cout<<p.x<<" "<<p.y<<endl;
       hull.pop();
   }
}

int main()
{
	//NUMBER OF INPUTS MUST BE GREATER THAN 3
	vector<pair<int, int> > Points;
	Points.pb(mp(4,4));
	Points.pb(mp(4,-4));
	Points.pb(mp(-4,4));
	Points.pb(mp(-4,-4));
	Points.pb(mp(0,0));
	Points.pb(mp(-2,-2));
	Points.pb(mp(-1,-1));
	
    graham_scan(Points);
    return 0;
}
