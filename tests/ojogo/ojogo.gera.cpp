#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <ctime>

using namespace std;

#define CASOS 100
#define MAX_MSGS 10000
#define MAX_PPL 10000
#define ALPHA 0.5

bool segue[MAX_PPL][MAX_PPL];
string nome[MAX_PPL];

inline string generate_random_name(void) {
    string name;
    for (unsigned i=0; i<15; ++i) {
        name += 'a' + lrand48()%26;
    }
    return name;
}


int main (void) {
    int i;

    srand48(time(0));

    for (int caso=0; caso<CASOS; ++caso) {
        int msgs = drand48() * (MAX_MSGS-1) + 1;
        int ppl = drand48() * (MAX_PPL-2) + 2;

        for (i=0; i<ppl; ++i) {
            nome[i] = generate_random_name();
        }

        int dia = 1;
        memset(segue, 0, sizeof(segue));

        printf("%d\n", msgs);
        for (i=0; i<msgs; ++i) {
            double x = drand48();
            double y = drand48();

            if (x < 0.3) {
                dia++;
            }
            else if (x < 0.6) {
                dia += drand48()*10;
            }

            printf("%d ", dia);

            if (y < ALPHA) {
                printf("PUBLISH %s\n", nome[int(drand48()*ppl)].c_str());
            }
            else {
                int a = drand48()*ppl;
                int b = drand48()*ppl;

                while (a==b) b = drand48()*ppl;

                if (segue[a][b]) {
                    printf("UNSUBSCRIBE ");
                    segue[a][b]=false;
                }
                else {
                    printf("SUBSCRIBE ");
                    segue[a][b]=true;
                }
                printf("%s, %s\n", nome[a].c_str(), nome[b].c_str());
            }
        }
    }

    puts("0");

    return 0;
}
