#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

#define MAX 32

char m[MAX][MAX];
int foi[MAX][MAX];

vector<vector<int>> v[5];
int delta[4][2] = { {+1, 0}, {-1, 0}, {0, +1}, {0, -1}};

int n;

bool pode(int x, int y) {
    int i;

    if (x<0 or y<0 or x>=n or y>=n or m[x][y]!='.')
        return false;

    for (i=x-1; i>=0 and m[i][y]=='.'; --i)
        if(foi[i][y]) return false;
    for (i=x+1; i<n  and m[i][y]=='.'; ++i)
        if(foi[i][y]) return false;

    for (i=y-1; i>=0 and m[x][i]=='.'; --i)
        if(foi[x][i]) return false;
    for (i=y+1; i<n  and m[x][i]=='.'; ++i)
        if(foi[x][i]) return false;

    return true;
}

void resolve2(void) {
    int i, j;

    for (i=0; i<n; ++i) {
        for (j=0; j<n; ++j) {
            if (m[i][j]=='.' and !foi[i][j] and pode(i,j)) {
                foi[i][j] = 1;
            }
        }
    }

    for (i=0; i<n; ++i) {
        for (j=0; j<n; ++j) {
            if (m[i][j] == '.' and foi[i][j])
                printf("N");
            else
                printf("%c", m[i][j]);
        }
        printf("\n");
    }
}

int resolve (int x, int y, int id) {
    int i, j;

    for (i=x; i<n; ++i) {
        if (i==x) j=y;
        else j=0;

        for (; j<n; ++j) {
            if (m[i][j]>'0' && m[i][j]<'5') {
                break;
            }
        }
        if (j<n) {
            break;
        }
    }
    x=i;
    y=j;

    if (i==n) {
        resolve2();
        return 1;
    }

    int meta = m[x][y]-'0';

    if (meta) {
        for (i=0; i<(int)v[meta].size(); ++i) {
            for (j=0; j<meta; ++j) {
                int xl = x+delta[v[meta][i][j]][0];
                int yl = y+delta[v[meta][i][j]][1];

                if (!pode(xl, yl))
                    break;
                if (!foi[xl][yl])
                    foi[xl][yl] = id;
            }
            if (j<meta) continue;

            if(resolve(x, y+1, id+1))
                return 1;

            for (j=0; j<meta; ++j) {
                int xl = x+delta[v[meta][i][j]][0];
                int yl = y+delta[v[meta][i][j]][1];

                if (foi[xl][yl] == id)
                    foi[xl][yl] = 0;
            }
        }
    }

    return 0;
}

int main (void) {
    int i;

    v[1].resize(4);
    v[1][0] = {0};
    v[1][1] = {1};
    v[1][2] = {2};
    v[1][3] = {3};

    v[2].resize(6);
    v[2][0] = {0, 1};
    v[2][1] = {0, 2};
    v[2][2] = {0, 3};
    v[2][3] = {1, 2};
    v[2][4] = {1, 3};
    v[2][5] = {2, 3};

    v[3].resize(4);
    v[3][0] = {0, 1, 2};
    v[3][1] = {0, 1, 3};
    v[3][2] = {0, 2, 3};
    v[3][3] = {1, 2, 3};

    v[4].resize(1);
    v[4][0] = {0, 1, 2, 3};

    while (1) {
        scanf("%d", &n);
        if (n == 0)
            break;

        for (i=0; i<n; ++i) {
            scanf("%s", m[i]);
        }

        memset(foi, 0, sizeof(foi));
        if (!resolve(0, 0, 1))
            puts("NO SOLUTION");
    }

    return 0;
}
