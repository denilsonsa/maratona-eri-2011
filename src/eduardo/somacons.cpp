#include <stdio.h>
#include <algorithm>
using namespace std;

#define MAX 200010
long long soma[MAX];

int main() {
	soma[0] = 0;
	for (int i=1; i < MAX; i++) {
		soma[i] = soma[i-1] + i;
	}

	int N;
	while (scanf(" %d", &N) == 1 && N) {
		for (int i=2; i < MAX; i++) {
			long long diff = soma[i] - N;
			//printf("N=%d i=%d soma[i]=%lld diff=%lld\n", N, i, soma[i], diff);
			if (binary_search(soma, soma+i-1, diff)) {
				printf("SIM\n");
				goto fim;
			}
		}
		printf("NAO\n");
fim:	;
	}

	return 0;
}
