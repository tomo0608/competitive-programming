#include<bits/stdc++.h>

struct Point{
    // R^2上の点
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y){}

    Point operator+(const Point &p)
    {
        return {x + p.x, y + p.y};
    }

    Point operator-(const Point &p)
    {
        return {x - p.x, y - p.y};
    }

    Point operator*(const double k){
        return {k*x, k*y};
    }

    Point operator/(const double k){
        return {x/k, y/k};
    }

    double operator*(const Point &p){
        return x*p.x + y*p.y;
    }

    double operator^(const Point &p){
        return x*p.y - y*p.x;
    }

    double getangle(){
        // 偏角を度数で求める(0 <= angle <= 360)
        if(y >= 0.0){
            double I = x / sqrt((*this)*(*this));
            double angle = acos(I) * 180.0 / 3.14159265358979;
            return angle;
        }
        else{
            double I = x / sqrt((*this)*(*this));
            double angle = acos(I) * 180.0 / 3.14159265358979;
            return 360.0 - angle;
        }
    }
};

