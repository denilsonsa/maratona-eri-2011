#include <stdio.h>
#include <string.h>

char buf[25];

int main() {
	while (scanf(" %s", buf) == 1) {
		if (strlen(buf) == 1 && buf[0] == '0') break;

		// Calcula o resto modulo 42 do numero da entrada.
		// Como o numero eh muito grande para caber em um tipo numerico,
		// tratamos como string, caractere a caractere.
		int r = 0;
		for (int i = 0; buf[i]; i++) {
			r *= 10;
			r += buf[i] - '0';
			r %= 42;
		}

		if (r == 0) printf("PREMIADO\n");
		else printf("TENTE NOVAMENTE\n");
	}
	return 0;
}
