#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;

vector<string> id2name;
vector<int> counter;
vector<int> ult_dia;
map<string,int> name2id;
map<int, set<int> > followers;

class Compara {
    bool reverse;

    public:
    Compara (const bool& revparam = false) {
        reverse=revparam;
    }

    bool operator() (const int& a, const int& b) const {
        if (reverse) {
            return counter[a]>counter[b];
        }
        return counter[a]<counter[b];
    }
};

priority_queue<int, vector<int>, Compara> ranking;

inline int getid (string s) {
    map<string,int>::iterator it = name2id.find(s);
    int id;

    if (it == name2id.end()) {
        id =name2id[s] = id2name.size();
        id2name.push_back(s);
        counter.push_back(0);
        ult_dia.push_back(0);
        followers[id] = set<int>();
    }
    else {
        id = it->second;
    }

    return id;
}

inline void lembra_jogo(int dia, int id) {
    if (ult_dia[id] < dia) {
        ++counter[id];
        ult_dia[id] = dia;
    }
}

int main (void) {
    int i, n;

    while (1) {
        scanf("%d", &n);
        if (!n) break;

        id2name.clear();
        name2id.clear();
        counter.clear();
        ult_dia.clear();
        followers.clear();

        for (i=0; i<n; ++i) {
            char cmd[16];
            char a[16], b[16];
            int ida, idb;
            int dia;

            scanf("%d %s", &dia, cmd);
            if (cmd[0]=='S' or cmd[0]=='U') {
                scanf(" %[^,], %s", a, b);
                ida = getid(a);
                idb = getid(b);

                if (cmd[0]=='S') {
                    followers[idb].insert(ida);
                }
                else {
                    followers[idb].erase(ida);
                }
            }
            else {
                scanf("%s", a);
                ida = getid(a);
                lembra_jogo(dia, ida);

                set<int>::iterator it;

                for (it = followers[ida].begin(); it != followers[ida].end(); ++it) {
                    lembra_jogo(dia, *it);
                }
            }
        }

        counter.push_back(0x3f3f3f3f);
        int menor = id2name.size();
        for (i=0; i<id2name.size(); ++i) {
            if (counter[i] < counter[menor])
                menor = i;
        }

        ...
    }

    return 0;
}
