#include <stdio.h>
#include <stdlib.h>

#define MAX 64

double sistema[MAX][MAX];

inline
void swap(double *a, double *b) {
    double t = *a;
    *a = *b;
    *b = t;
}

// metodo de gauss
void gauss(int n, int m) {
    int i, j, k;

    for (j=0; j<m-1; j++) {
        for (i=0; i<n; i++) {
            double pivot =  sistema[i][j]/sistema[j][j];
            if(i!=j) {
                for(k=0; k<m; k++) {
                    sistema[i][k] = sistema[i][k] - pivot * sistema[j][k];
                }
            }
        }
    }
}

int main(void) {
    int i, j;
    int n;

    while (1) {
        scanf("%d", &n);
        if (!n) break;

        // le a matriz, deixando a primeira linha livre
        for (i=1; i<=n; ++i)
            for (j=0; j<n; ++j)
                scanf("%lf", &sistema[i][j]);

        // subtrai a identidade, ignorando a primeira linha
        for (i=1; i<=n; ++i) {
            sistema[i][i-1] -= 1;
        }

        // acha a transposta
        for (i=1; i<=n; ++i)
            for (j=0; j<i; ++j)
                swap(&sistema[i][j], &sistema[j+1][i-1]);

        // adiciona coluna de 0s no sistema
        for (i=1; i<=n; ++i)
            sistema[i][n] = 0;

        // adiciona linha de 1s no sistema (soma das probabilidades = 1)
        for (i=0; i<=n; ++i)
            sistema[0][i] = 1;

        // matriz cresceu uma linha e uma coluna
        gauss(n+1, n+1);

        // imprime a resposta
        for(i=0; i<n; i++) {
            if (i) printf(" ");
            printf("%3.5f", sistema[i][n] / sistema[i][i]);
        }
        printf("\n");
    }

    return 0;
}
