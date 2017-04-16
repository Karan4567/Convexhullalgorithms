#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
int order(pair<int,int> a, pair<int,int> b, pair<int,int> c);
void convexHull(vector<pair<int,int> > p);
void test();
void input();
int main(){
	clock_t startTime = clock();
	input();
	double executiontime = double( clock() - startTime ) / (double)CLOCKS_PER_SEC;
	cout<<endl<<executiontime<<" seconds."<<endl;
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
void convexHull(vector<pair<int,int> > p){
	int n = p.size();
	vector<pair<int,int> > res;
	if(n < 3) return;
	int id = 0;
	for(int i = 1;i < n;i++){
		if(p[i].x < p[id].x) id = i;
	}
	int a = id, b;
	do{
		res.push_back(p[a]);
		b = (a+1)%n;

		for(int i = 0;i < n;i++){
			if(order(p[a],p[i],p[b]) == 2) b = i;
		}
		a = b;
	}while(a != id);
	cout<<"Points on the convex hull in anti-clockwise order:\n";
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

