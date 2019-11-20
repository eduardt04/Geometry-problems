#include <fstream>
#include <vector>
#include <stack>    
//#include <algorithm>
//#include <iomanip>
using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

struct Point {
    double x,y;
};
vector<Point> p;
stack<Point> s;

/// test if 3 poins make a left turn or not
int isLeft(const Point &P, const Point &Q, const Point &R) {
    return ((Q.x - P.x) * (R.y - P.y) - (Q.y - P.y) * (R.x - P.x) > 0);
}
 
/// sort points by polar angle
int comparer(const Point &P, const Point &Q) {
    return isLeft(p[0], P, Q);
}

/// get the next element in stack 
Point nextInStack(stack<Point> s) {
    Point t = s.top();
    s.pop();
    Point sec = s.top();
    s.push(t);
    return sec;
}

int main() {
    int n, tp, i;
    fin>>n;
    p.resize(n);

    for(i = 0; i < n; i++)
        fin>>p[i].x>>p[i].y;
    
    /// find the bottom-left most point
    for(i = 1; i < n; i++)
        if(p[0].x > p[i].x || (p[0].x == p[i].x && p[0].y > p[i].y))
            swap(p[0], p[i]);
    
    /// sort points by their angle with p[0]
    sort(p.begin() + 1, p.end(), comparer);
    
    s.push(p[0]);
    s.push(p[1]);
    for(int i = 2; i < n; i++) {
        /// eliminate points until the points make a left turn
        while(s.size() >= 2 && !isLeft(nextInStack(s), s.top(), p[i]))
            s.pop();
        s.push(p[i]);
    }

    int k = s.size();
    vector<Point> convex_hull;

    while(!s.empty()) {
        convex_hull.push_back(s.top());
        s.pop();
    }

    fout<<k<<endl;
    for(int i = k - 1; i >= 0; i--)
        fout<<fixed<<setprecision(6)<<convex_hull[i].x<<' '<<convex_hull[i].y<<'\n';

    return 0;
}