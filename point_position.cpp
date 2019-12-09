/// Given 4 points A1, A2, A3, A4 determine whether the polygon is convex or not
/// If it is convex, determine the position of A4 relative to the circle circumscribing the triangle A1A2A3

#include <fstream>
#include <vector>
#include <cmath>

#define PI 3.14159265
using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

struct point {
    float x, y;
    point(float a = 0, float b = 0) : x(a), y(b) {};
};

int orientation_Test(point p, point q, point r) {
    return q.x * r.y + p.x * q.y + r.x * p.y - q.x * p.y - r.x * q.y - p.x * r.y;
}

/// scalar product of BA and BC
float scalar_Product(point a, point b, point c) {
    return (a.x - b.x) * (c.x - b.x) + (a.y - b.y) * (c.y - b.y);
}

/// norm of AB
float norm(point a, point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int main() {
    vector<point> p;
    float i, x, y;

    /// empty the first position
    p.push_back(*(new point(0, 0)));
    
    for(i = 1; i <= 4; i++) {
        fin>>x>>y;
        p.push_back(*(new point(x, y)));
    }
    
    if((orientation_Test(p[1], p[2], p[3]) < 0 && orientation_Test(p[2], p[3], p[4]) < 0 && orientation_Test(p[3], p[4], p[1]) < 0 && orientation_Test(p[4], p[1], p[2]) < 0) || (orientation_Test(p[1], p[4], p[3]) < 0 && orientation_Test(p[4], p[3], p[2]) < 0 && orientation_Test(p[3], p[2], p[1]) < 0 && orientation_Test(p[2], p[1], p[4]) < 0)) {
        fout<<"convex"<<endl;
        /// cos of angle A1A2A3
        float cosa2 = scalar_Product(p[1], p[2], p[3]) / (norm(p[2], p[1]) * norm(p[2], p[3]));
        /// cos of angle A1A4A3
        float cosa4 = scalar_Product(p[1], p[4], p[3]) / (norm(p[4], p[1]) * norm(p[4], p[3]));
        
        /// value of angle A1A2A3 in degrees
        float a2 = acos(cosa2) * 180.0 / PI;
        /// value of angle A1A4A3 in degrees
        float a4 = acos(cosa4) * 180.0 / PI;
        
        fout<<a2<<" "<<a4<<endl;
        
        /// if the value of the two is 180 degrees, then they are angles opposed on a circle
        if(a2 + a4 == 180)
            fout<<"On the edge of the circle";
        /// if the value of the angle is higher than 180, the points and closer so A4 is on the interior of the circle
        else if(a2 + a4 > 180)
            fout<<"On the interior of the circle";
        else fout<<"Out of the circle";
    }
    else fout<<"Not convex";
    return 0;
}