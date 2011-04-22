/*
 * quadrado.cpp
 *
 *  Created on: Apr 22, 2011
 *      Author: deborasilva
 */

#include <stdio.h>
#include <set>

using namespace std;

#define MAX 1000

class Point {
  public:
	int x, y;

	bool operator== (const Point& other) {
		return (x == other.x) && (y == other.y);
	}

	Point& operator+= (const Point& other) {
		x += other.x;
		y += other.y;
	}

	const Point operator+ (const Point& other) const {
		Point r = *this;
		r += other;
		return r;
	}

	bool operator< (const Point& other) const {
		if (x == other.x) {
			return y < other.y;
		}
		return x < other.x;
	}
};

int n;
Point p[MAX];
set<Point> point_set;

bool is_in_set(const Point& pt) {
	return point_set.find(pt) != point_set.end();
}

int calc() {
	int nq = 0;
	Point p3, p4, delta;
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			delta.x = p[i].y - p[j].y;
			delta.y = p[j].x - p[i].x;
			p3 = delta + p[i];
			p4 = delta + p[j];
			if (is_in_set(p3) && is_in_set(p4)) {
				nq++;
			}
		}
		point_set.erase(p[i]);
	}
	return nq;
}

int main() {
	while (1) {
		scanf("%d", &n);
		if (!n) break;
		point_set.clear();
		for (int i = 0; i < n; ++i) {
			scanf("%d %d", &p[i].x, &p[i].y);
			point_set.insert(p[i]);
		}
		printf("%d\n", calc());
	}
	return 0;
}
