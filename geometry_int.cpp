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
typedef std::vector<Point> Polygon;
Polygon Convex_Hull(Polygon& p){
    // 凸包を求める, 出力後pはソートされる
    sort(p.begin(),p.end());
    int n = p.size(), k = 0;
    if(k >= 3){
        Polygon ch(2 * n);
        for(int i = 0; i < n; ch[k++] = p[i++]){
            while(k >= 2 && (ch[k-1] - ch[k-2])^(p[i] - ch[k-1]) < 0)--k;
        }
        for(int i = n-2, t = k+1; i >= 0; ch[k++] = p[i--]){
            while(k >= t && (ch[k-1] - ch[k-2])^(p[i]-ch[k-1]) < 0)--k;
        }
        ch.resize(k-1);
        return ch;
    }else{
        return p;
    }
}