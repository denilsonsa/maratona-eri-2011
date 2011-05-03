/*
 * concstr.cpp
 *
 *  Created on: Apr 22, 2011
 *      Author: deboratads
 */

#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;

#define MAX 1000001

char lhs[MAX], rhs[MAX];
long long m, n;
long long lhs_l, rhs_l;

long long mdc() {
	long long a = lhs_l;
	long long b = rhs_l;
	if (a < b) {
		long long t = a;
		a = b;
		b = t;
	}
	long long r;
	long long mod;
	do {
		r = b;
		mod = a%b;
		a = b;
		b = mod;
	} while (mod != 0);
	return r;
}

bool calcula() {
	string ab = lhs;
	ab += rhs;
	string ba = rhs;
	ba += lhs;
	if (ab != ba) {
		return false;
	}
	long long mdc_rl = mdc();
	long long mmc = (lhs_l * rhs_l)/mdc_rl;
	m = mmc/lhs_l;
	n = mmc/rhs_l;
	return true;
}

int main() {
	while (1) {
		scanf("%s %s", lhs, rhs);
		lhs_l = strlen(lhs);
		rhs_l = strlen(rhs);
		if (lhs_l == 1 && rhs_l == 1 && lhs[0] == '#' && rhs[0] == '#') {
			break;
		}
		if (!calcula()) {
			printf("NAO\n");
		} else {
			printf("%lld %lld\n", m, n);
		}
	}
	return 0;
}

