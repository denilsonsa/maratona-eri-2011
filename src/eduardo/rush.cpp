#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

#define NUM_INTERSECOES 110

#define TRACE(x) 
#define PRINT(x...) TRACE(printf(" -> " x))

int cap[NUM_INTERSECOES][NUM_INTERSECOES];
int fluxo[NUM_INTERSECOES][NUM_INTERSECOES];
int vis[NUM_INTERSECOES];
int P, N, M;
int U, V, W;
int SINK, SOURCE;

int ford_fulkerson(int u, int capres=0x3f3f3f3f) {
	if (u == SINK) {
		PRINT("chegou no sink com capres=%d\n", capres);
		return capres;
	}

	vis[u] = 1;
	for (int v=0; v <= SINK; v++) if (!vis[v] && cap[u][v] - fluxo[u][v] > 0) {
		int f = ford_fulkerson(v, min(capres, cap[u][v] - fluxo[u][v]));
		if (f) {
			fluxo[u][v] += f;
			fluxo[v][u] -= f;
			return f;
		}
	}
	return 0;
}

int main() {
	while (scanf(" %d %d %d", &P, &N, &M) == 3) {
		if (!P && !N && !M) break;

		memset(cap, 0, sizeof(cap));
		memset(fluxo, 0, sizeof(fluxo));

		for (int m=0; m < M; m++) {
			scanf(" %d %d %d", &U, &V, &W);
			U--; V--;
			cap[U][V] = W;
		}

		SINK = N;
		SOURCE = N+1;

		cap[SOURCE][0] = 0x3f3f3f3f;
		for (int i=0; i < N; i++) {
			bool bairro = true;
			for (int j=0; j < N; j++) {
				if (cap[i][j] > 0) bairro = false;
			}
			if (bairro) cap[i][SINK] = 0x3f3f3f3f;
		}

		int FluxoMaximo = 0, f = 0;
		do {
			memset(vis, 0, sizeof(vis));
			f = ford_fulkerson(SOURCE);
			PRINT("passei %d unidades de fluxo\n", f);
			FluxoMaximo += f;
		} while (f > 0);

		PRINT("FluxoMaximo: %d   P: %d\n", FluxoMaximo, P);
		if (FluxoMaximo < P) {
			printf("HORARIO RUIM\n");
		} else {
			printf("HORARIO BOM\n");
		}
	}
	return 0;
}
