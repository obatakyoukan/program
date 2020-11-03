#include<bits/stdc++.h> //std==c++14
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
	void polar(double r,double theta){ x = r*cos(theta), y= r*sin(theta) ; }
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
double arg(point a){ return a.arg(); }
double dot(point a,point b) { return a.x*b.x + a.y*b.y ; }
double cross(point a,point b) { return a.x * b.y - a.y * b.x ; }
point polar(double r,double theta){ point a; a.polar(r,theta); return a; }
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

int ccw(point p0,point p1,point p2){
	point a = p1-p0;
	point b = p2-p0;
	if(cross(a,b) > EPS ) return CCW_COUNTER_CLOCKWISE ;
	if(cross(a,b) < -EPS ) return CCW_CLOCKWISE;
	if(dot(a,b) < -EPS ) return CCW_ONLINE_BACK;
	if(a.norm() < b.norm() ) return CCW_ONLINE_FRONT;
	return CCW_ON_SEGMENT;
}


//intersect
bool intersect(point p1,point p2,point p3,point p4){return (ccw(p1,p2,p3)*ccw(p1,p2,p4) <= 0 && ccw(p3,p4,p1)*ccw(p3,p4,p2) <= 0 ) ; }
bool intersect(line l1,line l2) { return intersect(l1.s,l1.t,l2.s,l2.t) ; }
bool intersect(polygon p,line l){
	int n = p.size();
	for(int i=0;i<n;i++)  if(intersect(line(p[i],p[(i+1)%n] ) , l ) ) return true;
	return false;
}
int intersect(circle c1,circle c2){
	if(c1.r < c2.r) swap(c1,c2);
	double d = abs(c1.c-c2.c);
	double r = c1.r + c2.r;
	if(equals(d,r) ) return ICC_CIRCUMSCRIBE;
	if(d > r ) return ICC_SEPARATE;
	if(equals(d+c2.r,c1.r) ) return ICC_INSCRIBE;
	if( d + c2.r < c1.r ) return ICC_CONTAIN;
	return ICC_INTERSECT;
}

//bool intersectsc(line l,circle c){ return distancesp(l,c.c) <= c.r ; } distanceののち
int intersectcs(circle c,line l ){// 0		1		2
	if(norm(project(l,c.c) - c.c )  - c.r*c.r  > EPS ) return 0;
	double d1 = abs(c.c-l.s),d2  = abs(c.c-l.t);
	if(d1 < c.r + EPS && d2 < c.r + EPS ) return 0;
	if( (d1<c.r - EPS && d2 > c.r +EPS) || (d1 > c.r +EPS &&d2 < c.r -EPS ) ) return 1;
	point h = project(l,c.c) ;
	if(dot(l.s-h,l.t-h) < 0 ) return 2;
	return 0;
}

//distance
//line point
double distancelp(line l,point p){ return abs(cross(l.t-l.s,p-l.s)/ abs(l.t-l.s)  ); }
//segment point
double distancesp(line l,point p){ 
	if(dot(l.t-l.s,p-l.s) < 0.0 ) return abs(p-l.s);
	if(dot(l.s-l.t,p-l.t) < 0.0 ) return abs(p-l.t);
	return distancelp(l,p);
}
//segment segment 
double distancess(line l1,line l2){
	if(intersect(l1,l2) ) return 0.0;
	return min( min(distancesp(l1,l2.s) ,distancesp(l1,l2.t) ) , min(distancesp(l2,l1.s),distancesp(l2,l1.t)  ) );
}

bool intersectsc(line l,circle c){ return distancesp(l,c.c) <= c.r ; }

//crosspoint 
//segment segment
point crosspointss(line l1,line l2){
	for(int k=0;k<2;k++){
		if(distancesp(l1,l2.s) < EPS ) return l2.s;
		if(distancesp(l1,l2.t) < EPS ) return l2.t;
		swap(l1,l2);
	}
	point base = l2.t-l2.s;
	double d1 = abs(cross(base,l1.s-l2.s) );
	double d2 = abs(cross(base,l1.t-l2.s) );
	double t = d1/(d1+d2);
	return l1.s + (l1.t-l1.s) * t;
}
//line line
point crosspointll(line l1,line l2){
	double a = cross(l1.t-l1.s,l2.t-l2.s);
	double b = cross(l1.t-l1.s,l1.t-l2.s);
	if(abs(a) < EPS && abs(b) < EPS ) return l2.s;
	return l2.s + (l2.t-l2.s) * (b/a) ;
}
//circle line
polygon crosspointCL(circle c,line l){
	polygon ps;
	point pr = project(l,c.c);
	point e = (l.t - l.s) / abs(l.t-l.s) ;
	if(distancelp(l,c.c) > c.r ) return ps;//付け足した
	if(equals(distancelp(l,c.c),c.r) ){
		ps.emplace_back(pr);
	}
	double base = sqrt(c.r*c.r - norm(pr-c.c) );
	ps.emplace_back(pr + e*base ) ;
	ps.emplace_back(pr - e*base ) ;
	return ps;
}
//circle segment
polygon crosspointCS(circle c,line l ){
	polygon res = crosspointCL(c,l);
	if(intersectcs(c,l) == 2 ) return res;
	if(res.size() > 1u ){//一つのみ削る
		if(dot(l.s-res[0] ,l.t-res[0] ) > 0) swap(res[0],res[1] );
		res.pop_back();
	}
	return res;
}
polygon crosspointcc(circle c1,circle c2){
	polygon p(2);
	double d = abs(c1.c-c2.c);
	double a = acos( (c1.r *c1.r + d*d -c2.r*c2.r) /(2*c1.r*d ) );
	double t = arg(c2.c-c1.c);
	p[0] = c1.c + polar(c1.r,t+a);
	p[1] = c1.c + polar(c1.r,t-a);
	return p;
}

int contains(polygon g,point p) { //IN:2 ON:1 OUT:0
    int n = g.size();
    bool f = false;
    for(int i=0;i<n;i++){
	point a = g[i] - p,b = g[(i+1)%n] - p;
	if( fabs(cross(a,b) ) < EPS && dot(a,b) < EPS) return 1;
	if( a.y > b.y ) swap(a,b);
	if( a.y < EPS && EPS < b.y && cross(a,b) > EPS ) f = !f;
    }
    return (f?2:0) ;
}

polygon andrewscan(polygon &s){ //convex hull
	polygon u,l;
	if(s.size() < 3) return s;
	//sort(s.begin(),s.end() );
	//最も左で最も右の点にする
	sort(s.begin(),s.end(),sort_y);
	u.push_back(s[0]);
	u.push_back(s[1]);
	l.push_back(s[s.size()-1]);
	l.push_back(s[s.size()-2]);
	for(int i=2;i<s.size();i++){
		for(int n = u.size();n>=2&&ccw(u[n-2],u[n-1],s[i]) != CCW_CLOCKWISE;n--)//凸包の辺上を含めない
		//for(int n = u.size();n>=2&&ccw(u[n-2],u[n-1],s[i]) == CCW_COUNTER_CLOCKWISE;n--)//凸包の辺上を含める場合
		u.pop_back();
		u.push_back(s[i]);
	}
	for(int i=s.size()-3;i>=0;i--){
		for(int n=l.size();n>=2&&ccw(l[n-2],l[n-1],s[i]) != CCW_CLOCKWISE;n--)//凸包の辺上を含めない	
		//for(int n=l.size();n>=2&&ccw(l[n-2],l[n-1],s[i]) == CCW_COUNTER_CLOCKWISE;n--)//凸包の辺上を含める場合
		l.pop_back();
		l.push_back(s[i]);
	}
	reverse(l.begin(),l.end());
	for(int i=u.size()-2;i>=1;i--)l.push_back(u[i]);
	return l;
	//最も左で最も右の点にする
	/*point mini = l[0];
	int base = 0;
	for(int i=0;i<l.size();i++)
	    if(mini.y > l[i].y || (mini.y==l[i].y && mini.x > l[i].x ) ){
			mini = l[i];
			base = i;
	    }
	polygon res;
	for(int i=0;i<l.size();i++)res.push_back( l[(i+base)%l.size()] );
	return res;*/
}

double diameter(polygon &s){
	polygon p = s;
	int n = p.size();
	if(n==2) return abs(p[0]-p[1]);
	int i=0,j=0;
	for(int k=0;k<n;k++){
		if(p[i] < p[k]) i = k;
		if(!(p[j]<p[k]) ) j = k;
	}
	double res = 0;
	int si = i,sj = j;
	while( i != sj || j != si ){
		res = max(res,abs(p[i]-p[j]) );
		if(cross(p[(i+1)%n]-p[i],p[(j+1)%n]-p[j] ) < 0.0) i = (i+1)%n;
		else j = (j+1)%n;
	}
	return res;
}
bool isconvex(polygon p){
	bool f = 1;
	int n = p.size();
	for(int i=0;i<n;i++){
		int t = ccw(p[(i+n-1)%n],p[i],p[(i+1)%n] );
		f&= t!=CCW_CLOCKWISE;
	}
	return f;
}
double area(polygon p){
	double res =  0.0;
	for(int i=0;i<p.size();i++) res += cross(p[i],p[ (i+1)%p.size() ]);
	return res/2.0;
}
double area(circle c1,circle c2){
	double d = abs(c1.c-c2.c);
	if(c1.r + c2.r <= d + EPS ) return 0.0;
	if(d<=abs(c1.r-c2.r) ){
		double r = min(c1.r,c2.r);
		return PI*r*r;
	}
	double rc = (d*d + c1.r*c1.r -c2.r*c2.r)/(2*d);
	double th = acos(rc/c1.r);
	double ph = acos( (d-rc)/c2.r);
	return c1.r*c1.r*th + c2.r*c2.r*ph - d * c1.r * sin(th) ;
}

polygon convex_cut(polygon p,line l){
	polygon q;
	int n = p.size();
	for(int i=0;i<n;i++){
		point a = p[i] , b = p[(i+1)%n];
		if(ccw(l.s,l.t,a) != -1 ) q.push_back(a);
		if(ccw(l.s,l.t,a) * ccw(l.s,l.t,b) < 0) q.push_back(crosspointss(line(a,b),l) );
	}
	return q;
}
//[s,t) 再帰 devide and conquer
double inf  = 1e10;
double closest_pair_dac(polygon &p,int s,int t,double &res){
	if(t-s<=1)return inf;
	if(t-s==2){
		sort(p.begin()+s,p.begin()+t,sort_y);
		return (p[s]-p[s+1]).abs();
	}
	int mid = (s+t)/2;
	double x = p[mid].x;
	res = min(closest_pair_dac(p,s,mid,res),closest_pair_dac(p,mid,t,res) );
	auto it = p.begin();
	auto its = it+s,itm = it+mid,itt = it + t;
	inplace_merge(its,itm,itt,sort_y);
	vector<point> tmp;
	for(int i=s;i<t;i++){
		if(abs(p[i].x-x) >= res) continue;
		for(int j=tmp.size()-1;j>=0;j--){
			point d = p[i]-tmp[j];
			if(d.y >= res) break;
			res = min( res , d.abs() );
		}
		tmp.push_back(p[i]);
	}
	return res;
}
double closest_pair(polygon &p){
	double res = inf;
	sort(p.begin(),p.end());
	return  closest_pair_dac(p,0,p.size(),res);
}

int main(){
    	int n;
	cin>>n;
    	polygon p(n);
	for(int i=0;i<n;i++) p[i].input();
	printf("%0.10lf\n",closest_pair(p) );
	return 0;
}

