/*
 * gemeos.cpp
 *
 *  Created on: Apr 22, 2011
 *      Author: deborasilva
 */

#include <vector>
#include <algorithm>
#include <functional>
#include <stdio.h>

using namespace std;

#define MAX 1024
#define SI (sizeof(long long))
#define MAXV (1 + 1024/(SI))

struct Vert {
	long long val[MAXV];
	int nv;

	Vert() : nv(MAXV) { }

	bool operator< (const Vert& rhs) const {
		for (int i = 0; i < nv; ++i) {
			if (val[i] < rhs.val[i]) {
				return true;
			}
		}
		return false;
	}

	bool operator== (const Vert& rhs) const {
		for (int i = 0; i < nv; ++i) {
			if (val[i] != rhs.val[i]) {
				return false;
			}
		}
		return true;
	}

	void setnv(int new_nv) {
		nv = new_nv/SI + ((new_nv % SI != 0) ? 1 : 0);
	}

	void set(int p) {
		val[p/SI] |= 1 << (p % SI);
	}

	void clear() {
		for (int i = 0; i < MAXV; ++i) {
			val[i] = 0;
		}
	}
};

vector<Vert> v;

long long ncomb2(long long n) {
	return (n * (n - 1))/2;
}

int main() {
	int m, n;
	int a, b;

	while (1) {
		scanf("%d %d", &n, &m);
		if (!m && !n) break;
		v.clear();
		v.reserve(n);
		for (int i = 0; i < n; ++i) {
			v[i].clear();
			v[i].set(i);
			v[i].setnv(n);
		}
		for (int i = 0; i < m; ++i) {
			scanf("%d %d", &a, &b);
			v[a-1].set(b-1);
			v[b-1].set(a-1);
		}
		sort(v.begin(), v.end());
		int neq = 1;
		long long nc = 0;
		for (int i = 1; i < n; ++i) {
			if (v[i] == v[i-1]) {
				neq++;
			} else {
				if (neq > 1) {
					nc += ncomb2(neq);
				}
				neq = 1;
			}
		}
		if (neq > 1) {
			nc += ncomb2(neq);
		}
		printf("%lld\n", nc);
	}
	return 0;
}
