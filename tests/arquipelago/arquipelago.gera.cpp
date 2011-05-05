#include <cstdio>
#include <cstdlib>
#include <ctime>

int casos = 10000;
int linhas = 50;

int main (void) {

    int i, j, l, c, x;

    srand48(time(0));

    for (x=0; x<casos; ++x) {
        l = drand48() * linhas + 1;
        c = drand48() * linhas + 1;

        printf("%d %d\n", l, c);

        for (i=0; i<l; ++i) {
            for (j=0; j<c; ++j) {
                int r = lrand48()%3;
                if (r==0) {
                    printf("X");
                }
                else if (r==1) {
                    printf(".");
                }
                else {
                    r = lrand48()%5;
                    printf("%d", r);
                }
            }
            puts("");
        }
    }

    printf("0 0\n");

    return 0;
}
