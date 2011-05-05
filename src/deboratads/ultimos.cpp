/*
 * ultimos.cpp
 *
 *  Created on: 04/05/2011
 *      Author: Debora
 */

#include <stdio.h>

#define MAX 128

int pos[MAX];

int main() {
	int n;
	while (1) {
		scanf("%d", &n);
		if (!n) break;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &pos[i]);
		}
		for (int i = n-1; i >= 0; --i) {
			printf("%d\n", pos[i]);
		}
		printf("0\n");
	}

	return 0;
}
