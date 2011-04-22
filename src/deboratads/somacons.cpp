/*
 * somacons.cpp
 *
 *  Created on: Apr 22, 2011
 *      Author: deborasilva
 */

#include <stdio.h>

int main() {
	int n;
	while (1) {
		scanf("%d", &n);
		if (!n) break;
		int nb = 0;
		while (n) {
			if (n & 1) {
				nb++;
			}
			n >>= 1;
		}
		printf("%s\n", (nb == 1) ? "NAO" : "SIM");
	}
	return 0;
}
