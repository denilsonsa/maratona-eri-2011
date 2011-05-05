#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

vector<string> id2name;
map<string,int> name2id;
vector<int> counter;
set< pair<int,int> > counter_ord;
vector<int> ult_dia;
map<int, set<int> > followers;
vector<string> resp;

inline int getid (const string s) {
    map<string,int>::iterator it = name2id.find(s);
    int id;

    if (it == name2id.end()) {
        id = id2name.size();
        
        name2id[s] = id;
        id2name.push_back(s);
        counter.push_back(0);
        counter_ord.insert(make_pair(id,0));
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
        ult_dia[id] = dia;

        counter_ord.erase(make_pair(id,counter[id]));
        ++counter[id];
        counter_ord.insert(make_pair(id,counter[id]));
    }
}

int main (void) {
    unsigned i, n;

    while (1) {
        scanf("%u", &n);
        if (!n) break;

        id2name.clear();
        name2id.clear();
        counter.clear();
        counter_ord.clear();
        ult_dia.clear();
        followers.clear();
        resp.clear();

        for (i=0; i<n; ++i) {
            char cmd[16];
            char a[16], b[16];
            int id_a, id_b;
            int dia;

            scanf("%d %s", &dia, cmd);
            if (cmd[0]=='S' or cmd[0]=='U') {
                scanf(" %[^,], %s", a, b);
                id_a = getid(a);
                id_b = getid(b);

                if (cmd[0]=='S') {
                    followers[id_b].insert(id_a);
                }
                else {
                    followers[id_b].erase(id_a);
                }
            }
            else {
                scanf("%s", a);
                id_a = getid(a);
                lembra_jogo(dia, id_a);

                set<int>::iterator it;

                for (it = followers[id_a].begin(); it != followers[id_a].end(); ++it) {
                    lembra_jogo(dia, *it);
                }
            }
        }

        int menor = counter_ord.begin()->second;
        while (counter_ord.begin()->second == menor) {
            resp.push_back(id2name[counter_ord.begin()->first]);
            counter_ord.erase(counter_ord.begin());
        }
        sort(resp.begin(), resp.end());

        for (i=0; i<resp.size(); ++i) {
            if (i) printf(" ");
            printf("%s", resp[i].c_str());
        }
        printf("\n");
    }

    return 0;
}
