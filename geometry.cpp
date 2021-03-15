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

    Point operator*(const Point &p){
        return x*p.x + y*p.y;
    }

    Point operator^(const Point &p){
        return x*p.y - y*p.x;
    }
};
