/*
 * somaprima.cpp
 *
 *  Created on: Apr 22, 2011
 *      Author: deborasilva
 */

#include <stdio.h>
#include <string.h>

#define MAX 1000000

char ep[MAX];
int primos[MAX];
int np;

void crivo() {
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
}

bool pode(int n) {
	int soma;
	for (int i = 0; i < np; ++i) {
		for (int j = 0; j < np; ++j) {
			soma = 0;
			if (i + primos[j] > np) break;
			for (int k = 0; k < primos[j]; ++k) {
				soma += primos[i+k];
			}
			if (soma == n) return true;
			if (soma > n) break;
		}
	}
	return false;
}

int main() {
	int n;
	crivo();
	while (1) {
		scanf("%d", &n);
		if (!n) break;
		printf("%s\n", pode(n) ? "SIM" : "NAO");
	}

	return 0;
}

