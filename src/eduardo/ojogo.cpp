#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
using namespace std;

#define TRACE(x) x
#define PRINT(x...) TRACE(printf(x))

#define MAX_PESSOAS 1000

char acao[30], nome1[30], nome2[30], resto[50];
int subs[MAX_PESSOAS][MAX_PESSOAS];
int perdeu_hoje[MAX_PESSOAS];
int qtd_perdeu[MAX_PESSOAS];

map<string, int> mapeamento;
vector<string> nomes;

int get_idx(string nome) {
	if (mapeamento.find(nome) == mapeamento.end()) {
		nomes.push_back(nome);

		// os comandos abaixo tem q ficar separados porque a bosta
		// do operador [] cria uma entrada no map antes de avaliar
		// o valor do .size(), ai fica tudo off-by-one... *sadface*
		int idx = mapeamento.size();
		mapeamento[nome] = idx;
	}
	return mapeamento[nome];
}

int main() {
	int N;
	while (scanf(" %d", &N) == 1) {
		if (!N) break;

		mapeamento.clear();
		nomes.clear();

		memset(subs, 0, sizeof(subs));
		memset(qtd_perdeu, 0, sizeof(qtd_perdeu));
		memset(perdeu_hoje, 0, sizeof(perdeu_hoje));
		int ultdia = -1;

		for (int t=0; t < N; t++) {
			int dia;
			scanf(" %d %s %[^\n]", &dia, acao, resto);
			if (dia != ultdia) {
				PRINT(" -> o dia %d terminou...\n", ultdia);
				for (int i=0; i < (int)mapeamento.size(); i++) {
					if (perdeu_hoje[i]) {
						PRINT("    neste dia '%s' perdeu.\n", nomes[i].c_str());
						qtd_perdeu[i]++;
					}
				}

				// cleanups diversos
				memset(perdeu_hoje, 0, sizeof(perdeu_hoje));

				// atualizando ultimo dia visto
				ultdia = dia;
			}

			if (acao[0] == 'S') { // SUBSCRIBE
				sscanf(resto, " %[^,], %s", nome1, nome2);
				PRINT(" -> SUBSCRIBE '%s' '%s'\n", nome1, nome2);
				int id1 = get_idx(nome1);
				int id2 = get_idx(nome2);
				subs[id1][id2] = 1;
			}
			else if (acao[0] == 'U') { // UNSUBSCRIBE
				sscanf(resto, " %[^,], %s", nome1, nome2);
				PRINT(" -> UNSUBSCRIBE '%s' '%s'\n", nome1, nome2);
				int id1 = get_idx(nome1);
				int id2 = get_idx(nome2);
				subs[id1][id2] = 0;
			}
			else { // PUBLISH
				sscanf(resto, " %s", nome1);
				PRINT(" -> PUBLISH '%s'\n", nome1);
				int idx = get_idx(nome1);
				perdeu_hoje[idx] = 1;
				PRINT("    '%s' perdeu.\n", nomes[idx].c_str());
				for (int i=0; i < (int)mapeamento.size(); i++) {
					if (subs[i][idx]) { // i fez subscribe de idx
						perdeu_hoje[i] = 1;
						PRINT("    '%s' leu e perdeu tb\n", nomes[i].c_str());
					}
				}
			}
		}

		// atualizando perdedores do ultimo dia
		PRINT(" -> fim da simulacao\n");
		for (int i=0; i < (int)mapeamento.size(); i++) {
			if (perdeu_hoje[i]) {
				PRINT("    neste dia '%s' perdeu.\n", nomes[i].c_str());
				qtd_perdeu[i]++;
			}
		}

		// achando menor numero de perdas
		int min_perdas = 1000123;
		for (int i=0; i < (int)mapeamento.size(); i++) {
			if (qtd_perdeu[i] < min_perdas) {
				min_perdas = qtd_perdeu[i];
			}
		}

		// pega nomes dos menos perdedores e ordena alfabeticamente
		vector<string> perdeu_menos;
		for (int i=0; i < (int)mapeamento.size(); i++) {
			if (qtd_perdeu[i] == min_perdas) {
				perdeu_menos.push_back( nomes[i] );
			}
		}
		sort(perdeu_menos.begin(), perdeu_menos.end());

		// imprime nomes dos menos perdedores
		for (int i=0; i < (int)perdeu_menos.size(); i++) {
			if (i) printf(" ");
			printf("%s", perdeu_menos[i].c_str());
		}
		printf("\n");
	}
	return 0;
}
