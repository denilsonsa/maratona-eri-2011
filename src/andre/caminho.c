#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 64

int distancia[MAX][MAX];
int qualidade[MAX];
double total[MAX];
double sistema[MAX][MAX];

#define ERRO 0.000001

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
        scanf("%d %*d", &n);
        if (!n) break;

        // le a qualidade dos bares
        for (i=0; i<n; ++i) {
            scanf("%d", &qualidade[i]);
            total[i]=0;
        }

        for (i=0; i<n; ++i) {
            for (j=0; j<n; ++j) {
                scanf("%d", &distancia[i][j]);
                if (i!=j)
                    total[i] += ((double)qualidade[j]) / distancia[i][j];
                else
                    total[i] += sqrt(qualidade[i]);
            }
        }

        // le a matriz, deixando a primeira linha livre
        for (i=0; i<n; ++i) {
            for (j=0; j<n; ++j) {
                if (i!=j)
                    sistema[i+1][j] = (((double)qualidade[j]) / distancia[i][j]) / total[i];
                else
                    sistema[i+1][j] = sqrt(qualidade[i]) / total[i];
            }
        }

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
        int max = n;
        sistema[max][max] = -0.1;
        for(i=0; i<n; i++) {
            sistema[i][i] = sistema[i][n] / sistema[i][i];
            printf("%3.10f ", sistema[i][i]);
            if (sistema[i][i] > sistema[max][max] + ERRO)
                max = i;
        }
        printf("\n%d\n", max+1);
    }

    return 0;
}
