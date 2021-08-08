#include<bits/stdc++.h>

namespace geometry{
    using scalar = long double; // long double
    const scalar EPS = 1e-10, PI = acos(-1), INF = 1e18;
    inline int sign(const scalar &r){return r <= -EPS ? -1: r >= EPS ? 1: 0;}
    inline bool eq(scalar a, scalar b){return sign(a-b) == 0;}

    using Point = std::complex<scalar>;
    double radian_to_degree(scalar r){return r*180.0/PI;}
    double degree_to_radian(scalar d){return d*PI/180.0;}
    std::istream &operator>>(std::istream &is, Point &p){
        scalar a, b;
        is >> a >> b;
        p = Point(a, b);
        return is;
    }

    std::ostream &operator<<(std::ostream &os, const Point &p) { os  <<std::setprecision(20) <<  p.real() << ' ' << p.imag(); return os; }

    #define POINT(...) Point __VA_ARGS__; input(__VA_ARGS__)
    bool compare_x(const Point &a, const Point &b){
        return eq(a.real(), b.real())? (a.imag() < b.imag()): (a.real() < b.real());
    }
    bool compare_y(const Point &a, const Point &b){
        return eq(a.imag(), b.imag())? (a.real() < b.real()): (a.imag() < b.imag());
    }

    scalar cross(const Point &a, const Point &b){ // 外積
        return a.real()*b.imag() - a.imag() * b.real();
    }

    scalar dot(const Point &a, const Point &b){ // 内積
        return a.real()*b.real() + a.imag() * b.imag();
    }

    scalar GetAngle(const Point &a, const Point &b, const Point &c){ // 角abc(小さい方)
        const Point v(b-a), w(c-b);
        scalar alpha = std::atan2(v.imag(), v.real()), beta = std::atan2(w.imag(), w.real());
        scalar theta = abs(beta - alpha);
        return std::min(theta, 2*PI - theta);
    }

    struct Line{ // 直線
        Point a, b;

        Line(Point a = 0, Point b = 0):a(a),b(b){};
        Line(scalar A, scalar B, scalar C){ // Ax + By = C;
            if (eq(A, 0)) {
                a = Point(0, C / B);
                b = Point(1, C / B);
            } else if (eq(B, 0)) {
                a = Point(C / A, 0);
                b = Point(C / A, 1);
            } else {
                a = Point(0, C / B);
                b = Point(C / A, 0);
            }
        }
        friend std::istream &operator>>(std::istream &is, Line &l) { is >> l.a >> l.b; return is; }
        friend std::ostream &operator<<(std::ostream &os, Line &l) { os  << l.a << ' ' << l.b; return os; }
    };

    struct Segment:Line{ // 線分
        Segment(Point a = Point(), Point b = Point()): Line(a,b){}
    };

    struct Circle{ // 円
        Point p;
        scalar r;

        Circle(Point p = 0, scalar r = 0.0):p(p),r(r){};
    };

    using Points = std::vector<Point>;
    using Polygon = std::vector<Point>;
    using Segments = std::vector<Segment>;
    using Lines = std::vector<Line>;
    using Circles = std::vector<Circle>;

    constexpr int COUNTER_CLOCKWISE = 1;
    constexpr int CLOCKWISE = -1;
    constexpr int ONLINE_BACK = -2; // C->A->B
    constexpr int ONLINE_FRONT = 2; // A->B->C
    constexpr int ON_SEGMENT = 0; // A->C->B

    int ccw(const Point &a, Point b, Point c){ // a,b,cの順に見てcが
        b = b - a, c = c - a;
        if(sign(cross(b, c))==1)return COUNTER_CLOCKWISE;
        if(sign(cross(b, c))==-1)return CLOCKWISE;
        if(sign(dot(b, c))==-1)return ONLINE_BACK;
        if(norm(b) < norm(c))return ONLINE_FRONT;
        return ON_SEGMENT;
    }

    bool Parallel(const Line &l0, const Line &l1){
        return sign(cross(l0.b - l0.a, l1.b - l1.a)) == 0;
    }

    bool  Orthogonal(const Line &l0, const Line &l1){
        return sign((dot(l0.b - l0.a, l1.b - l1.a))) == 0;
    }

    Point Projection(const Line &l, const Point &p){ // pのLineへの射影
        return l.a + (l.b - l.a) * dot(l.b-l.a,p-l.a)/dot(l.b - l.a, l.b - l.a);
    }

    Point Projection(const Segment &s, const Point &p){
        return s.a + (s.b - s.a) * dot(s.b-s.a,p-s.a)/dot(s.b - s.a, s.b - s.a);
    }

    Point Reflection(const Line &l, const Point &p){
        return p + (Projection(l, p) - p) * scalar(2.0);
    }

    bool Intersect(const Line &l0, const Line &l1){
        return !eq(cross(l0.b - l0.a, l1.b - l1.a), 0.0);
    }

    bool Intersect(const Line &l, const Point &p){
        return abs(ccw(l.a, l.b, p)) != 1;
    }

    bool Intersect(const Segment &s, const Point &p){
        return ccw(s.a, s.b, p) == ON_SEGMENT;
    }

    bool Intersect(const Line &l, const Segment &s){
        return sign(cross(l.b - l.a, s.a - l.a) * cross(l.b - l.a, s.b - l.a)) <= 0;
    }

    bool Intersect(const Segment &s, const Segment &t){
        return ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) <= 0 && ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
    }

    scalar Distance(const Point &p, const Point &q){
        return abs(p - q);
    }

    scalar Distance(const Line &l, const Point &p){
        return abs(p - Projection(l, p));
    }

    scalar Distance(const Line &l0, const Line &l1){
        return Intersect(l0, l1)? 0: Distance(l0, l1.a);
    }

    scalar Distance(const Segment &s, const Point &p){
        Point r = Projection(s, p);
        if(Intersect(s, r))return abs(r - p);
        return std::min(abs(s.a - p), abs(s.b - p));
    }

    scalar Distance(const Segment &s0, const Segment &s1){
        if(Intersect(s0, s1))return 0;
        return std::min({Distance(s0, s1.a), Distance(s0, s1.b), Distance(s1, s0.a), Distance(s1, s0.b)});
    }

    scalar Distance(const Line &l, const Segment &s){
        if(Intersect(l, s))return 0;
        return std::min(Distance(l, s.a), Distance(l, s.b));
    }

    bool Intersect(const Circle &c, const Line &l){
        return Distance(l, c.p) <= c.r + EPS;
    }

    bool Intersect(const Circle &c, const Point &p){
        return Distance(p, c.p) <= c.r + EPS;
    }

    int Intersect(const Circle &c1, const Circle &c2){ // 二つの円の共通接線の本数
        scalar d = Distance(c1.p, c2.p), r = c1.r + c2.r;
        if(sign(d-r) == 1)return 4;
        if(sign(d-r) == 0)return 3;
        if(sign(d-abs(c2.r-c1.r)) == 1)return 2;
        if(sign(d-abs(c2.r-c1.r)) == 0)return 1;
        return 0;
    }

    Point Crosspoint(const Line &l0, const Line &l1){
        scalar A = cross(l0.b - l0.a, l1.b - l1.a);
        scalar B = cross(l0.b - l0.a, l0.b - l1.a);
        if(eq(A, 0.0) && eq(B, 0.0))return l1.a;
        return l1.a + (l1.b - l1.a)*B/A;
    }

    Point Crosspoint(const Segment &s0, const Segment &s1){
        scalar A = cross(s0.b - s0.a, s1.b - s1.a);
        scalar B = cross(s0.b - s0.a, s0.b - s1.a);
        if(eq(A, 0.0) && eq(B, 0.0))return s1.a;
        return s1.a + (s1.b - s1.a)*B/A;
    }

    std::pair<Point,Point> Crosspoint(const Circle &c, const Line &l){ // 交点がないとバグる, 1個のときは同じものが二つ出力される
        Point pj = Projection(l, c.p), high = pj - c.p;
        Point v = (l.b - l.a) * std::sqrt(std::max(scalar(0.0),std::norm(c.r) - std::norm(high)))/abs(l.b - l.a);
        return std::pair(pj - v, pj + v);
    }

    std::pair<Point,Point> Crosspoint(const Circle &c1, const Circle &c2){// 交点がないとバグる, 1個のときは同じものが二つ出力される
        Point v = c2.p - c1.p, w(-v.imag(), v.real());
        scalar d = abs(v);
        scalar x = (d*d + c1.r*c1.r - c2.r*c2.r)/(2*d);
        scalar y = std::sqrt(std::max(c1.r*c1.r - x*x, scalar(0.0)));
        return std::pair(c1.p + v*x/d - w*y/d, c1.p + v*x/d + w*y/d);
    }

    std::pair<Point, Point> tangent(const Circle &c, const Point &p){// pからcへの接線の接点2つ
        return Crosspoint(c, Circle(p, sqrt(norm(c.p - p) - c.r * c.r)));
    }

    Lines getCommonTangent(Circle c1, Circle c2){// c1, c2の共通接線(最大4本)
        Lines ls;
        if(c1.r < c2.r)std::swap(c1, c2);
        scalar g = norm(c1.p - c2.p);
        if(eq(g, 0.0))return ls;
        Point u = (c2.p - c1.p)/std::sqrt(g);
        Point v = {-u.imag(), u.real()};
        for(int s: {-1, 1}){
            scalar h = (c1.r + c2.r * s)/sqrt(g);
            if(eq(1-h*h, 0)){
                ls.emplace_back(c1.p + u*c1.r, c1.p + (u+v)*c1.r);
            }else if(sign(1-h*h) == 1){
                Point uu = u * h, vv = v * std::sqrt(1 - h*h);
                ls.emplace_back(c1.p + (uu + vv)*c1.r, c2.p - (uu + vv)*(c2.r * s));
                ls.emplace_back(c1.p + (uu - vv)*c1.r, c2.p - (uu - vv)*(c2.r * s));
            }
        }
        return ls;
    }

    scalar Area2(const Polygon &p){ // 多角形の面積の二倍
        scalar A = 0.0;
        for(int i = 0; i < p.size(); ++i){
            A += cross(p[i], p[(i==p.size()-1?0:i+1)]);
        }
        return A;
    }

    scalar common_area(Circle c1, Circle c2){// 円の共通部分の面積
        int flag = Intersect(c1, c2);
        if(flag >= 3)return scalar(0);
        if(flag <= 1){
            scalar r = std::min(c1.r, c2.r);
            return r*r*PI;
        }
        scalar d = Distance(c1.p, c2.p);
        scalar ret = 0;
        for(int i = 0; i < 2; ++i){
            scalar t = acos((d*d + c1.r*c1.r - c2.r*c2.r)/(2*d*c1.r))*2;
            ret += (t - sin(t))*c1.r*c1.r/2;
            std::swap(c1, c2);
        }
        return ret;
    }

    bool isConvex(const Polygon &p){ // 凸か
        int n = p.size();
        for(int i = 0; i < n; ++i){
            if(ccw(p[(i+n-1)%n], p[i], p[(i==n-1?0:i+1)]) == CLOCKWISE)return false;
        }
        return true;
    }

    enum{OUT, ON, IN};
    int Contains(const Polygon &P, const Point &p){ // pがPの内部なら2, 辺なら1, 外部なら0
        bool in = false;
        for(int i = 0; i < P.size(); ++i){
            if(ccw(P[i], P[(i==P.size()-1?0:i+1)], p) == ON_SEGMENT)return ON;
            Point a = P[i] - p, b = P[(i==P.size()-1?0:i+1)] - p;
            if(a.imag() > b.imag())swap(a, b);
            if(sign(a.imag()) <= 0 && 0 < sign(b.imag()) && sign(cross(a,b)) == -1)in = !in;
        }
        return in? IN: OUT;
    }

    Polygon Convex_Hull(Polygon &p, bool strict = true){// 凸包を求める, 出力後pはソートされる
        sort(p.begin(),p.end(), compare_x);
        int n = p.size();
        Polygon G1, G2, ch;
        G1.emplace_back(p[0]);G2.emplace_back(p[0]);
        G1.emplace_back(p[1]);G2.emplace_back(p[1]);
        for(int i = 2; i < n; i++){
            while(G1.size() >= 2 && (sign(cross((G1[G1.size()-1]-G1[G1.size()-2]),(p[i]-G1[G1.size()-1]))) <= -1 + strict))G1.pop_back();
            while(G2.size() >= 2 && (sign(cross((G2[G2.size()-1]-G2[G2.size()-2]),(p[i]-G2[G2.size()-1]))) >= 1 - strict))G2.pop_back();
            G1.emplace_back(p[i]);
            G2.emplace_back(p[i]);
        }
        for(int i = 0; i < G1.size();i++)ch.emplace_back(G1[i]);
        for(int i = (int)G2.size()-2; i>=1; i--)ch.emplace_back(G2[i]);
        return ch;
    }

    std::pair<scalar, std::pair<int,int>> farthest_pair(Polygon &p){ // 凸であることは前提, 直径を求める
        int n = p.size();
        auto chmax = [&](scalar &a, const scalar &b){if(sign(a-b) == -1){a = b; return true;}return false;};
        if(n == 2){ // 凸包が潰れている場合は特別処理
            return {Distance(p[0], p[1]), {0, 1}};
        }
        int i = 0, j = 0; // ある方向に最も遠い点対
        for(int k = 0; k < n; ++k){
            if(!compare_x(p[k], p[i]))i = k;
            if(compare_x(p[k], p[j]))j = k;
        }
        scalar d = 0;
        int a = i, b = j, si = i, sj = j;
        while(i != sj || j != si){
            if(chmax(d, abs(p[i]-p[j])))a = i, b = j;
            if(sign(cross(p[(i==n-1?0:i+1)]-p[i], p[(j==n-1?0:j+1)]-p[j])) == -1){
                i = (i==n-1?0:i+1);
            }else{
                j = (j==n-1?0:j+1);
            }
        }
        return {d, {a, b}};
    }

    Polygon convex_cut(Polygon &P, Line l){ // 凸多角形Pをlで切断し左側にできる凸多角形を出力
        Polygon res;
        for(int i = 0; i < P.size(); ++i){
            Point now =P[i], nxt = P[(i==P.size()-1?0:i+1)];
            if(ccw(l.a, l.b, now) != CLOCKWISE)res.emplace_back(now); // 直線の右にさえなければ必要
            if(ccw(l.a, l.b, now) * ccw(l.a, l.b, nxt) < 0)res.emplace_back(Crosspoint(Line(now, nxt), l));
        }
        return res;
    }

    std::pair<scalar, std::pair<int,int>> closest_pair(Points &p){ //点の集合の中で最も近い2点とその間の距離を出力
        std::vector<std::pair<Point, int>>  dat(p.size());
        for(int i = 0; i < p.size(); ++i)dat[i] = {p[i], i};
        auto cmp_x = [&](std::pair<Point, int> a, std::pair<Point, int> b){return compare_x(a.first, b.first);};
        auto cmp_y = [&](std::pair<Point, int> a, std::pair<Point, int> b){return compare_y(a.first, b.first);};
        auto chmin = [](std::pair<scalar,std::pair<int,int>> &a, const std::pair<scalar,std::pair<int,int>> &b)->bool{
            if(sign(a.first-b.first) == 1){
                a = b;
                return true;
            }
            return false;
        };
        sort(dat.begin(),dat.end(), cmp_x);
        auto rec = [&](auto &&rec, int l, int r)->std::pair<scalar, std::pair<int,int>>{
            if(r-l <= 1)return {INF, {p.size(), p.size()}};
            int m = (l+r)/2;
            scalar x = dat[m].first.real();
            std::pair<scalar, std::pair<int,int>> d = min(rec(rec,l, m), rec(rec,  m, r));
            std::inplace_merge(dat.begin()+l, dat.begin()+m, dat.begin()+r, cmp_y);
            std::vector<std::pair<Point, int> > q;
            for(int i = l; i < r; ++i){
                if(sign(abs(dat[i].first.real()-x)-d.first) == 1)continue;

                for(int j = q.size()-1; j >= 0; --j){
                    Point dz = dat[i].first - q[j].first;
                    if(sign(dz.imag() - d.first) >= 0)break;
                    chmin(d, {abs(dz), {dat[i].second, q[j].second}});
                }
                q.emplace_back(dat[i]);
            }   
            return d;
        };
        return rec(rec, 0, p.size());
    }
    
    Circle inscribed_circle(const Point &a, const Point &b, const Point &c){ // 内接円
        scalar A = Distance(b, c), B = Distance(c, a), C = Distance(a, b);
        Point x((a*A + b*B + c*C)/(A+B+C));
        scalar r = Distance(Segment(a, b), x);
        // scalar r = abs(Area2({a,b,c}))/(A+B+C);
        return Circle(x, r);
    }

    Circle circumscribed_circle(const Point &a, const Point &b, const Point &c){ // 外接円
        Point m1((a+b)/scalar(2)), m2((b+c)/scalar(2));
        Point v((b-a).imag(), (a-b).real()), w((b-c).imag(), (c-b).real());
        Line s(m1, Point(m1 + v)), t(m2, Point(m2 + w));
        Point o = Crosspoint(s, t);
        return Circle(o, Distance(o, a));
    }

    Circle minimum_bounding_circle(Points &p){
        if(p.size() == 1)return Circle(p[0]);
        if(p.size() == 2)return Circle((p[0]+p[1])/scalar(2), abs(p[0]-p[1])/scalar(2));
        Circle c(Point(), INF);
        Points ch = Convex_Hull(p);
        int K = ch.size();
        auto check = [&](Circle c){
            for(int i = 0; i < K; ++i)if(sign(abs(ch[i]-c.p)-c.r) == 1)return false;
            return true;
        };
        for(int i = 0; i < K; ++i)for(int j = i+1; j < K; ++j){
            Circle tc((ch[i] + ch[j])/scalar(2), Distance(ch[i], ch[j])/scalar(2));
            if(check(tc) && (c.r > tc.r)){
                c = tc;
            }
            for(int k = j+1; k < K; ++k){
                int flag = ccw(ch[i], ch[j], ch[k]);
                if(abs(flag) != 1)continue;
                tc = circumscribed_circle(ch[i], ch[j], ch[k]);
                if(check(tc) && (c.r > tc.r)){
                    c = tc;
                }
            }
        }
        return c;
    }
}

using namespace geometry;