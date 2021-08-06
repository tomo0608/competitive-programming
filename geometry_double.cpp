#include<bits/stdc++.h>

namespace geometry{
    const double EPS = 1e-8, PI = acos(-1);

    inline bool eq(double a, double b){return abs(a-b) < EPS;}

    using Point = std::complex<double>;
    double radian_to_degree(double r){return r*180.0/PI;}
    double degree_to_radian(double d){return d*PI/180.0;}
    std::istream &operator>>(std::istream &is, Point &p){
        double a, b;
        is >> a >> b;
        p = Point(a, b);
        return is;
    }
    std::ostream &operator<<(std::ostream &os, const Point &p) { os  <<std::setprecision(10) <<  p.real() << ' ' << p.imag(); return os; }
    #define POINT(...) Point __VA_ARGS__; input(__VA_ARGS__)
    bool operator<(const Point &a, const Point &b){
        return a.real() != b.real()? a.real() < b.real(): a.imag() < b.imag();
    }
    double cross(const Point &a, const Point &b){
        return a.real()*b.imag() - a.imag() * b.real();
    }
    double dot(const Point &a, const Point &b){
        return a.real()*b.real() + a.imag() * b.imag();
    }
    double GetAngle(const Point &a, const Point &b, const Point &c){ // 角abc(小さい方)
        const Point v(b-a), w(c-b);
        double alpha = std::atan2(v.imag(), v.real()), beta = std::atan2(w.imag(), w.real());
        double theta = abs(beta - alpha);
        return std::min(theta, 2*PI - theta);
    }

    struct Line{
        Point a, b;

        Line(Point a = 0, Point b = 0):a(a),b(b){};
        Line(double A, double B, double C){ // Ax + By = C;
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

    struct Segment:Line{
        Segment(Point a = Point(), Point b = Point()): Line(a,b){}
    };

    struct Circle{
        Point p;
        double r;

        Circle(Point p = 0, double r = 0.0):p(p),r(r){};
    };

    using Points = std::vector<Point>;
    using Polygon = std::vector<Point>;
    using Segments = std::vector<Segment>;
    using Lines = std::vector<Line>;
    using Circles = std::vector<Circle>;

    int ccw(const Point &a, Point b, Point c){ // a,b,cの順に見て
        b = b - a, c = c - a;
        if(cross(b, c) > EPS)return +1; // "COUNTER_CLOCKWISE"
        if(cross(b, c) < -EPS)return -1; // "CLOCKWISE"
        if(dot(b, c) < -EPS)return +2; // "ONLINE_BACK"
        if(std::norm(b) < std::norm(c))return -2;  // "ONLINE_FRONT"
        return 0; // "ON_SEGMENT"
    }

    bool Parallel(const Line &l0, const Line &l1){
        return abs(cross(l0.b - l0.a, l1.b - l1.a)) < EPS;
    }

    bool  Orthogonal(const Line &l0, const Line &l1){
        return abs(dot(l0.b - l0.a, l1.b - l1.a)) < EPS;
    }

    Point Projection(const Line &l, const Point &p){ // pのLineへの射影
        return l.a + (l.b - l.a) * dot(l.b-l.a,p-l.a)/dot(l.b - l.a, l.b - l.a);
    }

    Point Projection(const Segment &s, const Point &p){
        return s.a + (s.b - s.a) * dot(s.b-s.a,p-s.a)/dot(s.b - s.a, s.b - s.a);
    }
    Point Reflection(const Line &l, const Point &p){
        return p + (Projection(l, p) - p) * 2.0;
    }


    bool Intersect(const Line &l0, const Line &l1){
        return !eq(cross(l0.b - l0.a, l1.b - l1.a), 0.0);
    }

    bool Intersect(const Line &l, const Point &p){
        return abs(ccw(l.a, l.b, p)) != 1;
    }

    bool Intersect(const Segment &s, const Point &p){
        return ccw(s.a, s.b, p) == 0;
    }

    bool Intersect(const Line &l, const Segment &s){
        return cross(l.b - l.a, s.a - l.a) * cross(l.b - l.a, s.b - l.a) < EPS;
    }

    bool Intersect(const Segment &s, const Segment &t){
        return ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) <= 0 && ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
    }

    double Distance(const Point &p, const Point &q){
        return abs(p - q);
    }

    double Distance(const Line &l, const Point &p){
        return abs(p - Projection(l, p));
    }

    double Distance(const Line &l0, const Line &l1){
        return Intersect(l0, l1)? 0: Distance(l0, l1.a);
    }

    double Distance(const Segment &s, const Point &p){
        Point r = Projection(s, p);
        if(Intersect(s, r))return abs(r - p);
        return min(abs(s.a - p), abs(s.b - p));
    }

    double Distance(const Segment &s0, const Segment &s1){
        if(Intersect(s0, s1))return 0;
        return min({Distance(s0, s1.a), Distance(s0, s1.b), Distance(s1, s0.a), Distance(s1, s0.b)});
    }

    double Distance(const Line &l, const Segment &s){
        if(Intersect(l, s))return 0;
        return min(Distance(l, s.a), Distance(l, s.b));
    }

    bool Intersect(const Circle &c, const Line &l){
        return Distance(l, c.p) <= c.r + EPS;
    }

    bool Intersect(const Circle &c, const Point &p){
        return Distance(p, c.p) <= c.r + EPS;
    }

    Point Crosspoint(const Line &l0, const Line &l1){
        double A = cross(l0.b - l0.a, l1.b - l1.a);
        double B = cross(l0.b - l0.a, l0.b - l1.a);
        if(eq(A, 0.0) && eq(B, 0.0))return l1.a;
        return l1.a + (l1.b - l1.a)*B/A;
    }

    Point Crosspoint(const Segment &s0, const Segment &s1){
        double A = cross(s0.b - s0.a, s1.b - s1.a);
        double B = cross(s0.b - s0.a, s0.b - s1.a);
        if(eq(A, 0.0) && eq(B, 0.0))return s1.a;
        return s1.a + (s1.b - s1.a)*B/A;
    }

    double Area2(const Polygon &p){ // 多角形の面積の二倍
        double A = 0.0;
        for(int i = 0; i < p.size(); ++i){
            A += cross(p[i], p[(i+1)%p.size()]);
        }
        return A;
    }

    bool isConvex(const Polygon &p){
        int n = p.size();
        for(int i = 0; i < n; ++i){
            if(ccw(p[(i+n-1)%n], p[i], p[(i+1)%n]) == -1)return false;
        }
        return true;
    }
}

using namespace geometry;