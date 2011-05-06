/*
 * somaprima.cpp
 *
 *  Created on: Apr 22, 2011
 *      Author: deborasilva
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>

#define MAX 1000002

char ep[MAX];
int primos[MAX];
int np;
char resp[MAX];

void calculasomas() {
	int soma;
	int k;
	for (int i = 0; i < np; ++i) {
		soma = 0;
		k = 0;
		for (int j = 0; j < np; ++j) {
			if (i + primos[j] > np) break;
			for (; k < primos[j]; ++k) {
				soma += primos[i+k];
				if (soma >= MAX) {
					break;
				}
			}
			if (soma < MAX) {
				resp[soma] = 1;
			}
		}
	}
}

void crivo() {
	memset(resp, 0, sizeof(resp));
	memset(ep, 1, sizeof(ep));
	ep[0] = 0;
	ep[1] = 0;
	int i = 2;
	while (i < MAX) {
		for (int j = 2 * i; j < MAX; j += i) {
			ep[j] = 0;
		}
		i++;
		while (i < MAX) {
			if (ep[i]) break;
			i++;
		}
	}
	np = 0;
	for (i = 2; i < MAX; ++i) {
		if (!ep[i]) continue;
		primos[np] = i;
		np++;
	}
	calculasomas();
}

int main() {
	int n;
	crivo();
	while (1) {
		scanf("%d", &n);
		assert(n <= 1000000);
		if (!n) break;
		printf("%s\n", resp[n] ? "SIM" : "NAO");
	}

	return 0;
}

