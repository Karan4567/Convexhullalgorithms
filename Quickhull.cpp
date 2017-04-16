#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
int order(pair<int,int> a, pair<int,int> b, pair<int,int> c);
double getdistance(pair<int, int> p0, pair<int, int> a, pair<int, int> b);
void quickhull(vector<pair<int,int> > p, pair<int, int> a, pair<int, int> b, vector<pair<int, int> >&res);
void convexHull(vector<pair<int,int> > p);
void test();
void input();
int main(){
	clock_t startTime = clock();
	input();
	double exeTime = double( clock() - startTime ) / (double)CLOCKS_PER_SEC;
	cout<<endl<<exeTime<<" seconds."<<endl;
	return 0;
}
int order(pair<int,int> a, pair<int,int> b, pair<int,int> c){
	int det = (b.x-a.x)*(c.y-b.y) - (c.x-b.x)*(b.y-a.y);
	if(det == 0)
        return 0;
	if(det < 0)
        return 1;
	return 2;
}
double getdistance(pair<int, int> p0, pair<int, int> a, pair<int, int> b){
	double m = (double)((b.y-a.y)*1.0)/(b.x-a.x);
	double c = a.y-m*a.x;
	double dist = (abs(m*p0.x-p0.y+c))/sqrt(m*m+1);
	return dist;
}
void quickhull(vector<pair<int,int> > p, pair<int, int> a, pair<int, int> b, vector<pair<int, int> >&res){
	int n = p.size();
	if(n == 0) return;
	double dist = 0;
	int id;
	for(int i = 0;i < n;i++){
		if(dist < getdistance(p[i],a,b)){
			id = i;
			dist = getdistance(p[i],a,b);
		}
	}
	res.push_back(p[id]);
	vector<pair<int, int> >p1, p2;
	for(int i = 0;i < n;i++){
		if(order(a, p[i], p[id]) == 2)  p1.push_back(p[i]);
		else if(order(p[id], p[i], b) == 2) p2.push_back(p[i]);
	}
	quickhull(p1,a,p[id],res);
	quickhull(p2,p[id],b,res);
}
void convexHull(vector<pair<int,int> > p){
	int n = p.size();
	vector<pair<int, int> > res, p1, p2;
	int id1 = 0, id2 = 0;
	for(int i = 1;i < n;i++){
		if(p[i].x < p[id1].x) id1 = i;
		else if(p[i].x > p[id2].x) id2 = i;
	}
	res.push_back(p[id1]); res.push_back(p[id2]);
	int f;
	for(int i = 0;i < n;i++){
		f = order(p[id1], p[i], p[id2]);
		if(f == 2)  p1.push_back(p[i]);
		else if(f == 1) p2.push_back(p[i]);
	}
	quickhull(p1,p[id1],p[id2],res);
	quickhull(p2,p[id2],p[id1],res);
	cout<<"Points comprising the convex hull:\n";
	for(int i = 0; i < res.size();i++)
		cout<<"("<<res[i].x<<","<<res[i].y<<")\t";
}
void test(){
	vector<pair<int,int> > p;
	p.push_back(make_pair(1,1));
	p.push_back(make_pair(2,2));
	p.push_back(make_pair(0,3));
	p.push_back(make_pair(1,2));
	p.push_back(make_pair(3,1));
	p.push_back(make_pair(0,0));
	p.push_back(make_pair(3,3));
	p.push_back(make_pair(4,4));
	convexHull(p);
}
void input(){
	int n,x,y;
	vector<pair<int,int> > p;
	ifstream in;
	in.open("n=100.txt");
	in>>n;
	for(int i = 0;i < n;i++){
		in>>x>>y;
		p.push_back(make_pair(x,y));
	}
	convexHull(p);
}

