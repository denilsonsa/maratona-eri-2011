#include <stdio.h>
#include <string.h>

#define MAX_CRIANCAS 1010

int encontrada[MAX_CRIANCAS];

int main() {
	int N, M;
	while (scanf(" %d %d", &N, &M) == 2) {
		if (!N && !M) break;

		memset(encontrada, 0, sizeof(encontrada));
		M--;
		encontrada[M] = 1;
		for (int i = 0 ; i < N - 2; i++) {
			int X;
			scanf(" %d", &X);
			X--;
			encontrada[X] = 1;
		}

		for (int i = 0; i < N; i++) {
			if (!encontrada[i]) {
				printf("%d\n", i + 1);
				break;
			}
		}
	}
	return 0;
}
