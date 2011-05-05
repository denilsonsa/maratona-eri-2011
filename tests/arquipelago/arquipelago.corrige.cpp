#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <ctime>

using namespace std;

#define MAX 128

int l, c;
char m1[MAX][MAX], m2[MAX][MAX];
bool coluna_ocupada[MAX];

int delta[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};

string
generate_random_filename(void) {
    string name;
    for (unsigned i=0; i<15; ++i) {
        int op = rand()%3;
        if (op==0) name += 'a' + rand()%26;
        else if (op==1) name += 'A' + rand()%26;
        else if (op==2) name += '0' + rand()%10;
    }
    return name + ".tmp";
}

bool pode(int i, int j) {
    if (i<0 or j<0 or i>=l or j>=c)
        return false;
    return true;
}

bool tem_sol(void) {
    char s[MAX+2];
    int i, j;
    string tmp_str = generate_random_filename();
    FILE* tmp = fopen((tmp_str+".in").c_str(), "a");
    fprintf(tmp, "%d %d\n", l, c);
    for (i=0; i<l; ++i) {
        for (j=0; j<c; ++j) {
            fprintf(tmp, "%c", m1[i][j]);
        }
        fprintf(tmp, "\n");
    }
    fprintf(tmp, "0 0\n");
    fclose(tmp);

    system(("./frota < " + tmp_str + ".in > " + tmp_str + ".out").c_str());

    tmp = fopen((tmp_str+".out").c_str(), "r");
    fscanf(tmp, "%s", s);
    fclose(tmp);
    remove((tmp_str+".in").c_str());
    remove((tmp_str+".out").c_str());

    if (strcmp(s, "IMPOSSIVEL") == 0) {
        return false;
    }
    return true;
}

bool eh_solucao(void) {
    int i, j, k;

    memset(coluna_ocupada, 0, sizeof(coluna_ocupada));

    for (i=0; i<l; ++i) {
        bool linha_ocupada = false;
        for (j=0; j<c; ++j) {
            //checa se mapa foi alterado de forma valida
            if (m2[i][j]=='N' and m1[i][j]!='.') {
                puts("1");
                return false;
            }
            if (m2[i][j]!='N' and m1[i][j]!=m2[i][j]) {
                puts("2");
                return false;
            }

            //se foi colocado um navio, checa se eh possivel fogo amigo
            if (m2[i][j] == 'N') {
               if (linha_ocupada or coluna_ocupada[j]) {
                   puts("3");
                   return false;
               }
               linha_ocupada = true;
               coluna_ocupada[j] = true;
            }

            //zera marcador de ocupacao de linha e coluna 
            if (isdigit(m2[i][j]) or m2[i][j]=='X') {
               linha_ocupada = false;
               coluna_ocupada[j] = false;
            }

            //checa se porto eh satisfeito
            if (isdigit(m2[i][j])) {
                int total = 0;
                for (k=0; k<4; ++k) {
                    if (pode(i+delta[k][0], j+delta[k][1]) and m2[i+delta[k][0]][j+delta[k][1]]=='N')
                        ++total;
                }
                if (total != m2[i][j]-'0') {
                    puts("4");
                    printf("%d %c, %d %d\n", total, m2[i][j], i, j);
                    return false;
                }
            }
        }
    }
    return true;
}

int main(int argc, char* argv[]) {

    int i;
    FILE* in  = fopen(argv[1], "r"),
        * out = fopen(argv[2], "r");

    srand(time(0));

    int tc = 1;
    while(1) {
        fscanf(in, "%d %d", &l, &c);

        if (l == 0 and c == 0) {
            puts("accept");
            fclose(in);
            fclose(out);
            return 0;
        }

        for (i=0; i<l; ++i) {
            fscanf(in, "%s", m1[i]);
        }

        fscanf(out, "%s", m2[0]);
        if (strcmp(m2[0], "IMPOSSIVEL") == 0) {
            if (tem_sol()) {
                puts("errado1");
                return 1;
            }
        }
        else {
            for (i=1; i<l; ++i) {
                fscanf(out, "%s", m2[i]);
            }

            if (not eh_solucao()) {
                puts("errado2");
                return 1;
            }
        }

        printf("Test case %d ok\n", tc++);
    }

    return 0;
}
