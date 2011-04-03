#include <stdio.h>
#include <string.h>

unsigned long long N;

int main() {
	while (scanf(" %llu", &N) == 1) {
		if (N == 0) break;

		// Calcula o resto modulo 42 do numero da entrada.
		// Como o numero eh muito grande para caber em um tipo numerico,
		// inevitavelmente o numero armazenado sera diferente do que
		// o numero fornecido na entrada.
		if (N % 42 == 0) printf("PREMIADO\n");
		else printf("TENTE NOVAMENTE\n");
	}
	return 0;
}
