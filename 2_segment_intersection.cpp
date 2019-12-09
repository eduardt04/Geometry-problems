/// Given 4 points A1, A2, A3, A4 determine the intersection of [A1A3] and [A2A4]
#include <fstream>
#include <iostream>
using namespace std;
ifstream fin("input.in");

struct Point {
    int x, y;
    Point(int a = 0, int b = 0) : x(a), y(b) {};
};

void print_Intersection(Point a) {
    cout<<"The intersection is the point: ("<<a.x<<","<<a.y<<")."<<endl;
}

void print_Intersection(Point a, Point b) {
    cout<<"The intersection is the segment: [("<<a.x<<","<<a.y<<"),("<<b.x<<","<<b.y<<")]."<<endl;
}

int main() {
    Point v[5];
    int i, x, y;

    for(i = 1; i <= 4; i++) {
        fin>>x>>y;
        v[i] = *(new Point(x, y));
    }
    
    int a1 = v[1].y - v[2].y, b1 = v[2].x - v[1].x, c1 = v[1].x * v[2].y - v[1].y * v[2].x;
    int a2 = v[3].y - v[4].y, b2 = v[4].x - v[3].x, c2 = v[3].x * v[4].y - v[3].y * v[4].x;
    int det = a1 * b2 - a2 * b1;

    if(det != 0) {
        int detx = -c1 * b2 + c2 * b1, dety = -a1 * c2 + a2 * c1;
        float x = (float)detx / det, y = (float)dety / det;
        
        if(v[1].x != v[2].x) {
           if(x <= max(v[1].x, v[2].x) && x >= min(v[1].x, v[2].x)) {
                print_Intersection(*(new Point(x, y)));
                return 0;
            } 
        }
        else 
            if(y <= max(v[1].y, v[2].y) && y >= min(v[1].y, v[2].y)) {
                print_Intersection(*(new Point(x, y)));
                return 0;
            }
        cout<<"The segments don't intersect.";
    }
    else {
        if(a1 * c2 - a2 * c1 != 0 || b1 * c2 - b2 * c1 != 0)
            cout<<"The segments don't intersect.";
        else 
            if(v[1].y != v[2].y) {
                if(!((v[3].y > max(v[2].y, v[1].y) && v[4].y > max(v[2].y, v[1].y)) || (v[3].y < min(v[2].y, v[1].y) && v[4].y < min(v[2].y, v[1].y)))) {
                    cout<<"Intersectia este un segment :["<<min(max(v[2].y, v[1].y), min(v[3].y, v[4].y))<<","<<max(max(v[2].y, v[1].y), min(v[3].y, v[4].y))<<"]";
                    int y_start = min(max(v[2].y, v[1].y), min(v[3].y, v[4].y));
                    int y_end = max(max(v[2].y, v[1].y), min(v[3].y, v[4].y));
                    
                    return 0;
                }
            }
            else 
                if(!((v[3].x > max(v[2].x, v[1].x) && v[4].x > max(v[2].x, v[1].x)) || (v[3].x < min(v[2].x, v[1].x) && v[4].x < min(v[2].x, v[1].x)))) {
                    cout<<"Intersectia este un segment :["<<min(max(v[2].x, v[1].x), min(v[3].x, v[4].x))<<","<<min(max(v[2].x, v[1].x), min(v[3].x, v[4].x))<<"]";
                    return 0;
                }
            cout<<"The segments don't intersect.";
    }
    return 0;
}