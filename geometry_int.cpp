#include<bits/stdc++.h>

struct Point{
    // R^2上の点
    long long x, y;
    Point(long long x = 0, long long y = 0): x(x), y(y){}

    Point operator+(const Point &p)
    {
        return {x + p.x, y + p.y};
    }

    Point operator-(const Point &p)
    {
        return {x - p.x, y - p.y};
    }

    Point operator*(const long long k){
        return {k*x, k*y};
    }

    Point operator/(const long long k){
        assert(k);
        return {x/k, y/k};
    }

    long long operator*(const Point &p){
        return x*p.x + y*p.y;
    }

    long long operator^(const Point &p){
        return x*p.y - y*p.x;
    }

    bool operator<(const Point &p){
        if(x < p.x)return true;
        if(x > p.x)return false;
        if(y < p.y)return true;
        return false;
    }
    
    double getangle(){
        // 偏角を度数で求める(0 <= angle <= 360)
        if(y >= 0.0){
            double I = (long double)x / sqrt((*this)*(*this));
            double angle = acos(I) * 180.0 / 3.14159265358979;
            return angle;
        }
        else{
            double I = (long double)x / sqrt((*this)*(*this));
            double angle = acos(I) * 180.0 / 3.14159265358979;
            return 360.0 - angle;
        }
    }
};
std::ostream &operator<<(std::ostream &os, const Point &p) { os << '(' << p.x << ", " << p.y << ')'; return os; }
typedef std::vector<Point> Polygon;
Polygon Convex_Hull(Polygon& p){
    // 凸包を求める, 出力後pはソートされる
    sort(p.begin(),p.end());
    int n = p.size();
    Polygon G1, G2, ch;
    G1.emplace_back(p[0]);G2.emplace_back(p[0]);
    G1.emplace_back(p[1]);G2.emplace_back(p[1]);
    for(int i = 2; i < n; i++){
        while(G1.size() >= 2 && (((G1[G1.size()-1]-G1[G1.size()-2])^(p[i]-G1[G1.size()-1])) <= 0))G1.pop_back();
        while(G2.size() >= 2 && (((G2[G2.size()-1]-G2[G2.size()-2])^(p[i]-G2[G2.size()-1])) >= 0))G2.pop_back();
        G1.emplace_back(p[i]);
        G2.emplace_back(p[i]);
    }
    for(int i = 0; i < G1.size();i++)ch.emplace_back(G1[i]);
    for(int i = (int)G2.size()-2; i>=1; i--)ch.emplace_back(G2[i]);
    return ch;
}