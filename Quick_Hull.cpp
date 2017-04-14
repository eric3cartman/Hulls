#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define x first
#define y second

vector<pair<int, int> > hull;
//check left or right
int location(pair<int, int> p, pair<int, int> q, pair<int, int> r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) return 0; 
    return (val > 0)? 1: 2; 
}
//distance of point from line AB
int dist(pair<int, int> a, pair<int, int> b, pair<int, int> c){
	int dx = b.x - a.x;
    int dy = b.y - a.y;
    int d = dx * (a.y - c.y) - dy * (a.x - c.x);
    if (d < 0) d = -d;
    return d;
}

void findhull(pair<int, int> a, pair<int, int> b, vector<pair<int, int> > &P){
	if(P.size()==0) return;
	int dmax=-1,d=0;
	int f=-1;
	for(int i=0;i<P.size();i++){
		d=dist(a,b,P[i]);
		if(d>dmax){
			dmax=d;
			f=i;
		}
	}
	//cout<<P[f].x<<P[f].y;
	pair<int, int> A=P[f];
	hull.pb(P[f]);//include farthest point in hull
	P.erase(remove(P.begin(), P.end(), A), P.end());
	vector<pair<int, int> > right1;
	vector<pair<int, int> > right2;
	for(int i=0;i<P.size();i++){
		if(location(a,A,P[i])==1) right1.pb(P[i]);
		if(location(A,b,P[i])==1) right2.pb(P[i]);
	}
	findhull(a,A,right1);
	findhull(A,b,right2);
}

void quickhull(vector<pair<int, int> > &P){
	int n=P.size();
	vector<pair<int, int> > left;
	vector<pair<int, int> > right;
	int l=0,r=0;
	for(int i=0;i<n;i++){
		if(P[i].x < P[l].x) l=i;
		if(P[i].x > P[r].x) r=i;
	}
	hull.pb(P[l]);
	hull.pb(P[r]);
	pair<int, int> A=P[l];
	pair<int, int> B=P[r];
	pair<int, int> t;
	
	P.erase(remove(P.begin(), P.end(), A), P.end());
	P.erase(remove(P.begin(), P.end(), B), P.end());
	
	vector<pair<int, int> > S1,S2;
	//cout<<P.size();
	for(int i=0;i<P.size();i++){
		if(location(A,B,P[i])==2) left.pb(P[i]);
		else if(location(A,B,P[i])==1) right.pb(P[i]);
	}
	/*for(int i=0;i<left.size();i++){
		cout<<left[i].x<<" "<<left[i].y<<endl;
	}*/
	findhull(A,B,right);
	findhull(B,A,left);
	for(int i=0;i<hull.size();i++){
		cout<<hull[i].x<<" "<<hull[i].y<<endl;
	}
}

int main() {
	//NUMBER OF INPUTS MUST BE GREATER THAN 3
	vector<pair<int, int> > Points;
	Points.pb(mp(4,4));
	Points.pb(mp(4,-4));
	Points.pb(mp(-4,4));
	Points.pb(mp(-4,-4));
	Points.pb(mp(0,0));
	Points.pb(mp(-2,-2));
	Points.pb(mp(-1,-1));
	
    quickhull(Points);
    //cout<<Points.size();
    return 0;
}
