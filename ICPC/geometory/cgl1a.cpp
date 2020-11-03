#include<bits/stdc++.h>
using namespace std;
 
#define EPS (1e-10)
#define equals(a,b) ( fabs(a-b) < EPS )
#define PI 3.141592653589793238

// COUNTER CLOCKWISE
static const int CCW_COUNTER_CLOCKWISE = 1;
static const int CCW_CLOCKWISE = -1;
static const int CCW_ONLINE_BACK = 2;
static const int CCW_ONLINE_FRONT = -2;
static const int CCW_ON_SEGMENT = 0;

//Intersect Circle and Circle
static const int ICC_SEPARATE = 4;
static const int ICC_CIRCUMSCRIBE = 3;
static const int ICC_INTERSECT = 2;
static const int ICC_INSCRIBE = 1;
static const int ICC_CONTAIN = 0;

struct point{
	double x,y;
	//construct
	point() {} 
	point(double x,double y):x(x),y(y){}
	//演算子
	point operator + (point p) { return point(x+p.x,y+p.y); }
	point operator - (point p) { return point(x-p.x,y-p.y); }
	point operator * (double k) { return point(x*k,y*k); }
	point operator / (double k) { return point(x/k,y/k); }
	point operator / (point p) { return point( (x*p.x + y*p.y)/p.norm()  , (-x*p.y + y*p.x)/p.norm() ) ; }
	bool operator < (point p) { return x!=p.x ? x<p.x : y<p.y; }
	bool operator == (point p) { return equals(x,p.x) && equals(y,p.y) ; }
	//function
	double arg() { return atan2(y,x) ; }
	double norm(){return x*x+y*y; }
	double abs() { return sqrt(norm() ) ;}
	double dot(point p) { return p.x*x + p.y*y; }
	double cross(point p) { return x*p.y - y*p.x; }

	//input output
	void input(){cin>>x>>y;}
	void print(){cout<<x<<' '<<y<<endl;};

};

bool sort_x(point a,point b){
	return a.x!=b.x?a.x<b.x:a.y<b.y ;
}
bool sort_y(point a,point b){
	return a.y!=b.y?a.y<b.y:a.x<b.x ;
}

typedef vector<point> polygon;

struct segment{
	point s,t;
	segment() {}
	segment(point s,point t) : s(s),t(t){}
	void input(){s.input(),t.input(); }
};
typedef segment line;

struct circle{
	point c;
	double r;
	circle() {}
	circle(point c,double r) : c(c),r(r){}

};

double norm(point a){	return a.norm(); }
double abs(point a){ return a.abs(); }
double dot(point a,point b) { return a.x*b.x + a.y*b.y ; }
double cross(point a,point b) { return a.x * b.y - a.y * b.x ; }

point orth(point p){ return point(-p.y,p.x); }

//isOrthgonal 垂直
bool isOrthogonal(point a,point b) { return equals(dot(a,b), 0.0 ) ; }
bool isOrthogonal(point a,point b,point c,point d) { return isOrthogonal(a-b,c-d) ; }
bool isOrthogonal(line l1,line l2 ){ return isOrthogonal(l1.t-l1.s,l2.t-l2.s); }
//isParallel 平行
bool isParallel(point a,point b) { return equals(cross(a,b), 0.0) ; }
bool isParallel(point a,point b,point c,point d) { return isParallel(a-b,c-d); }
bool isParallel(line l1,line l2) { return isParallel(l1.t-l1.s,l2.t-l2.s) ; }

point project(line l,point p){
	point base = l.t-l.s;
	double r = dot(p-l.s,base) / norm(base) ;
	return l.s + base*r;
}
point reflect(line l,point p){
	return p + (project(l,p) - p) *2.0;
}




int main(){
    	line l;
	l.input();
	int q;
	cin>>q;
	for(int i=0;i<q;i++){
		point a;
		a.input();
		point b = project(l,a);
		printf("%0.10lf %0.10lf\n",b.x,b.y);
	}
	return 0;
}

