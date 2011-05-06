#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>

#define MAX_BARS 100

int dist[MAX_BARS][MAX_BARS];

void gera (int casos, int max_bars, bool sorteia) {
    for (int caso=0; caso<casos; ++caso) {
        int bars = lrand48() % (max_bars-2) + 2;
        if (not sorteia) bars = max_bars;

        printf("%d %d\n", bars, int(lrand48()%bars+1));
        for (int i=0; i<bars; ++i) {
            printf("%d\n", int(lrand48() % 1000));
        }

        memset(dist, 0, sizeof(dist));
        for (int i=0; i<bars; ++i) {
            for (int j=i+1; j<bars; ++j) {
                dist[i][j] = dist[j][i] = lrand48() % 1000 + 1;
            }
        }

        for (int i=0; i<bars; ++i) {
            for (int j=0; j<bars; ++j) {
                if (j) printf(" ");
                printf("%d", dist[i][j]);
            }
            puts("");
        }
    }
}

int main (void) {

    srand48(time(0));

    printf( "3 1\n"
            "1\n"
            "2\n"
            "3\n"
            "0 1 2\n"
            "1 0 2\n"
            "2 2 0\n"
            "4 1\n"
            "3\n"
            "8\n"
            "5\n"
            "7\n"
            "0 1 2 3\n"
            "1 0 5 3\n"
            "2 5 0 4\n"
            "3 3 4 0\n");

    for (int i=10; i>0; --i) {
        gera(10, MAX_BARS/i, 1);
    }

    gera(10, MAX_BARS, 0);

    puts("0 0");

    return 0;
}
