#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
#include <iostream>
#define PI 3.14159265
using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

struct Point {
    int x, y, index;
    Point(int a = 0, int b = 0, int i = 0) : x(a), y(b), index(i) {}
    bool operator==(const Point &a) {
        return (x == a.x && y == a.y);
    }
    bool operator!=(const Point &a) {
        return (x != a.x || y != a.y);
    }
};

struct Triangle {
    Point a, b, c;
    Triangle(Point pa, Point pb, Point pc) : a(pa), b(pb), c(pc) {}
};

vector<Point> p;
int n;

/// > 0 left turn, < 0 right turn
int calculate_Turn(const Point &p, const Point &q, const Point &r) {
    return (p.x - r.x) * (q.y - r.y) - (q.x - r.x) * (p.y - r.y);
}

/// scalar product of BA and BC
float scalar_Product(const Point &a, const Point &b, const Point &c) {
    return (a.x - b.x) * (c.x - b.x) + (a.y - b.y) * (c.y - b.y);
}

/// norm of AB
float norm(const Point &a, const Point &b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

float get_Angle(const Point &a, const Point &b, const Point &c) {
    float cos_angle = scalar_Product(a, b, c) / (norm(b, a) * norm(b, c));
    float angle = acos(cos_angle) * 180.0 / PI;
    return angle;
}

bool test_Triangle(Point a, Point b, Point c) {
    float angle = get_Angle(a, b, c);
    if(calculate_Turn(a, b, c) == 0)
        return false;
    else if(calculate_Turn(a, b, c) > 0)
        angle = 360 - angle;
    if(angle > 180)
        return false;
    for(int i = 1; i <= n; i++)
        if(p[i] != a && p[i] != b && p[i] != c)
            if(calculate_Turn(a, b, p[i]) <= 0 && calculate_Turn(b, c, p[i]) <= 0 && calculate_Turn(c, a, p[i]) <= 0)
                return false;
    return true;
}

int main() {
    int i, x, y;
    fin>>n;
    queue<int> q;
    p.resize((n+1) * sizeof(Point));
    vector<Triangle> t;
    t.reserve((n-2) * sizeof(Triangle));

    for(i = 1; i <= n; i++) {
        fin>>x>>y;
        p[i] = (*(new Point(x, y, i)));
        if(i > 2)
            q.push(i);
    }
    
    int left = 1, mid = 2, right;

    while (q.size() > 0) {
        right = q.front();
        q.pop();
        if(test_Triangle(p[left], p[mid], p[right])) {
            fout<<left<<" "<<mid<<" "<<right<<endl;
            t.push_back(*(new Triangle(p[left], p[mid], p[right])));
            mid = right; 
        }
        else {
            q.push(left);
            left = mid;
            mid = right;
        }
    }
    
    fin>>x>>y;
    Point query(x, y);
    
    for(i = 0; i < n-2; i++) 
        if(calculate_Turn(t[i].a, t[i].b, query) <= 0 && calculate_Turn(t[i].b, t[i].c, query) <= 0 && calculate_Turn(t[i].c, t[i].a, query) <=0) {
            if(calculate_Turn(t[i].a, t[i].b, query) == 0) {
                cout<<"The point is on the segment "<<t[i].a.index<<" "<<t[i].b.index<<endl;
                return 0;
            }
            else if(calculate_Turn(t[i].b, t[i].c, query) == 0) {
                cout<<"The point is on the segment "<<t[i].b.index<<" "<<t[i].c.index<<endl;
                return 0;
            }
            else if(calculate_Turn(t[i].c, t[i].a, query) == 0) {
                cout<<"The point is on the segment "<<t[i].c.index<<" "<<t[i].a.index<<endl;
                return 0;
            }
            else { 
                cout<<"The point is in the interior of the triangle "<<t[i].a.index<<" "<<t[i].b.index<<" "<<t[i].c.index<<endl;
                return 0;
            }
        }
    
    cout<<"The point is outside the polygon";

    return 0;
}