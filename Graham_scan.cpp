#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
pair<int,int> p0;
int order(pair<int,int> a, pair<int,int> b, pair<int,int> c);
bool kar(pair<int,int> a, pair<int,int> b);
pair<int,int> next2top(stack<pair<int,int> > &s);
void convexhull(vector<pair<int,int> > p);
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
bool kar(pair<int,int> a, pair<int,int> b){
	int f = order(p0,a,b);
	if(f == 0)  return (((p0.x - a.x)*(p0.x - a.x)+(p0.y - a.y)*(p0.y - a.y)) <= ((p0.x - b.x)*(p0.x - b.x)+(p0.y - b.y)*(p0.y - b.y)));
	return (f == 1)?0:1;
}
pair<int,int> next2top(stack<pair<int,int> > &s){
	pair<int,int> t = s.top();
	s.pop();
	pair<int,int> item = s.top();
	s.push(t);
	return item;
}
void convexhull(vector<pair<int,int> > p){
	int n = p.size();
	vector<pair<int,int> > res;
	int id = 0;
	for(int i = 1;i < n;i++){
		if(p[i].y < p[id].y) id = i;
		else if(p[i].y == p[id].y && p[i].x < p[id].x) id = i;
	}
	swap(p[0],p[id]);
	p0 = p[0];
	sort(p.begin()+1,p.end(),kar);
	int j = 1;
	for(int i = 1;i < n-1;i++){
		if(order(p0,p[i],p[i+1]) != 0)  p[j++] = p[i];
	}
	p[j++] = p[n-1];
	if(j < 3) return;
	stack<pair<int,int> > s;
	s.push(p[0]);s.push(p[1]);s.push(p[2]);
	for(int i = 3;i < j;i++){
		while(order(next2top(s),s.top(),p[i]) != 2) s.pop();
		s.push(p[i]);
	}
	int count = 0;
	cout<<"Points on the convex hull in clockwise order:\n";
	while(!s.empty()){
		cout<<"("<<s.top().x<<","<<s.top().y<<")\t";
		count++;
		s.pop();
	}
	cout<<endl<<"Minimum no. of points required to construct the hull: "<<count<<endl;
}

void test(){
	vector<pair<int,int> > p;
	p.push_back(make_pair(1,1));
	p.push_back(make_pair(2,2));
	p.push_back(make_pair(0,3));
	p.push_back(make_pair(2,1));
	p.push_back(make_pair(3,0));
	p.push_back(make_pair(0,0));
	p.push_back(make_pair(3,3));
	convexhull(p);
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
	convexhull(p);
}
