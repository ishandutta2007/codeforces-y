#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <climits>
#include <numeric>
#include <vector>
#include <cmath>
using namespace std;

double a, b, l, w;

const double EPS = 1e-8;
inline int sign(double a) {
	return a < -EPS ? -1 : a > EPS;
}

struct Point {
	double x, y;
	Point() {
	}
	Point(double _x, double _y) :
			x(_x), y(_y) {
	}
	Point operator+(const Point&p) const {
		return Point(x + p.x, y + p.y);
	}
	Point operator-(const Point&p) const {
		return Point(x - p.x, y - p.y);
	}
	Point operator*(double d) const {
		return Point(x * d, y * d);
	}
	Point operator/(double d) const {
		return Point(x / d, y / d);
	}
	bool operator<(const Point&p) const {
		int c = sign(x - p.x);
		if (c)
			return c == -1;
		return sign(y - p.y) == -1;
	}
	double dot(const Point&p) const {
		return x * p.x + y * p.y;
	}
	double det(const Point&p) const {
		return x * p.y - y * p.x;
	}
	double alpha() const {
		return atan2(y, x);
	}
	double distTo(const Point&p) const {
		double dx = x - p.x, dy = y - p.y;
		return hypot(dx, dy);
	}
	double alphaTo(const Point&p) const {
		double dx = x - p.x, dy = y - p.y;
		return atan2(dy, dx);
	}
	void read() {
		scanf("%lf%lf", &x, &y);
	}
	double abs() {
		return hypot(x, y);
	}
	double abs2() {
		return x * x + y * y;
	}
	void write() {
		cout << "(" << x << "," << y << ")" << endl;
	}
};

#define cross(p1,p2,p3) ((p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y))

#define crossOp(p1,p2,p3) sign(cross(p1,p2,p3))

Point isSS(Point p1, Point p2, Point q1, Point q2) {
	double a1 = cross(q1,q2,p1), a2 = -cross(q1,q2,p2);
	return (p1 * a2 + p2 * a1) / (a1 + a2);
}

bool inMid(Point a, Point m, Point b, bool inc = false) {
	return crossOp(a,m,b) == 0 && sign((m - a).dot(m - b)) < (inc ? 1 : 0);
}

bool crsSS(Point p1, Point p2, Point q1, Point q2) { //strict
	return crossOp(p1,p2,q1) * crossOp(p1,p2,q2) < 0 && crossOp(q1,q2,p1) * crossOp(q1,q2,p2) < 0;
}

bool crsII(double l, double r, double L, double R) {
	if (l > r)
		swap(l, r);
	if (L > R)
		swap(L, R);
	return r + EPS > L && R + EPS > l;
}

bool crsTSS(Point p1, Point p2, Point q1, Point q2) {
	return crossOp(p1,p2,q1) * crossOp(p1,p2,q2) <= 0 && crossOp(q1,q2,p1) * crossOp(q1,q2,p2) <= 0 && crsII(p1.x, p2.x, q1.x, q2.x) && crsII(p1.y, p2.y, q1.y, q2.y);
}

Point proj(Point p1, Point p2, Point q) {
	return p1 + (p2 - p1) * (p2 - p1).dot(q - p1) / (p2 - p1).abs2();
}

double calc(double t) {
	double x = cos(t) * l, y = sin(t) * l;
	Point p1(x, 0), p2(0, y);
	Point q(b, a);
	return (q - p1).det(p2 - p1) / (p1 - p2).abs();
}
int main() {
	cin >> a >> b >> l;
	if (a > b)
		swap(a, b); //a<=b
	double L = 0, R = M_PI / 2;
	while (L + 1e-12 < R) {
		double M1 = (L * 2 + R) / 3, M2 = (L + R * 2) / 3;
		if (calc(M1) < calc(M2))
			R = M2;
		else
			L = M1;
	}
	w = calc((L + R) / 2);
	w = min(w, l);
	if (l <= a)
		w = l;
	else if (l <= b)
		w = a;
	if (w < 0)
		puts("My poor head =(");
	else
		printf("%0.10lf\n", w);
	return 0;
}