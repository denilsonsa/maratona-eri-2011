#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;



#define MAXN (1000*1000)
#define MAXM (1000)
#define INF 0x3f3f3f3f
#define MAXSTR 15

map<string,int> nome;
set<int>  segue[MAXM];
//set<int> ehseguido[MAXN];
set<int> diaperdido[MAXM];


int main()
{
	int n, i, dia;
	int usados;
	vector<string> resp;
	char nome1[MAXSTR+1];
	char nome2[MAXSTR+1];
	char operacao[MAXSTR+1];
	int ind1, ind2;
	map<string,int>::iterator it;
	set<int>::iterator itset;
	int menor;
	
	while (1)
	{
		scanf("%d", &n);
		if (!n)
			break;
		
		assert(1<= n && n<=MAXN);
		
		usados = 0;
		
		for (i=0; i<n; i++)
		{
			scanf("%d %s %[a-z]", &dia, operacao, nome1);
			
			assert(1 <= strlen(nome1) && strlen(nome1) <= MAXSTR);
			
			it = nome.find(nome1);
			if (it == nome.end())
			{
				nome[nome1] = usados;
				ind1 = usados;
				usados++;
			}
			else
			{
				ind1 = it->second;
			}
			
			
			if (!strcmp(operacao, "PUBLISH"))
			{
				diaperdido[ind1].insert(dia);
				for (itset = segue[ind1].begin(); itset!=segue[ind1].end(); ++itset)
					diaperdido[*itset].insert(dia);
			}
			else 
			{

				scanf("%*c %s", nome2);
				assert(1 <= strlen(nome2) && strlen(nome2) <= MAXSTR);

				it = nome.find(nome2);
				if (it == nome.end())
				{
					nome[nome2] = usados;
					ind2 = usados;
					usados++;
				}
				else
				{
					ind2 = it->second;
				}


				if (!strcmp(operacao, "UNSUBSCRIBE"))
				{
					segue[ind2].erase(ind1);
				}
				else if (!strcmp(operacao, "SUBSCRIBE"))
				{
					segue[ind2].insert(ind1);
				}
				else
				{
					assert(0);
				}
			}
		}
		
		assert(usados <= MAXM);
		
		menor = INF;
		
		for (i=0; i<usados; i++)
		{
			menor = min(menor, (int)diaperdido[i].size());
		}

		for (it = nome.begin(); it != nome.end(); ++it)
		{
			if ((int)diaperdido[it->second].size() == menor)
				resp.push_back(it->first);
		}
		
		sort(resp.begin(), resp.end());
		
		for (i=0; i<(int)resp.size(); i++)
		{
			if (i)
				putchar(' ');
			printf("%s", resp[i].c_str());
		}
		printf("\n");
		
		// zerar map e sets usados

		nome.clear();
		resp.clear();
		for (i=0; i<usados; i++)
		{
			diaperdido[i].clear();
			segue[i].clear();
		}
		
	}
	
	
	return 0;
}



/* SOLUCAO PARA A VERSAO ANTERIOR DO ENUNCIADO

#define MAXN 100
#define EPS 1e-8L


long double mat[2][MAXN][MAXN];

int n;


int dif()
{
	int i, j;
	for (i=0; i<n; i++)
		for (j=0; j<n; j++)
			if (fabs(mat[0][i][j]-mat[1][i][j]) > EPS)
				return 1;
	return 0;
}

void mul (int dest, int src)
{
	int i, j, k;
	for (i=0; i<n; i++)
		for (j=0; j<n; j++)
			mat[dest][i][j] = 0L;
			
	for (i=0; i<n; i++)
		for (j=0; j<n; j++)
			for (k=0; k<n; k++)
			{
				mat[dest][i][j] += mat[src][i][k]*mat[src][k][j];
			}
	
}

int main()
{
	int i, j;
	double d;
	long double menor;
	int qual;
	
	while (1)
	{
		scanf("%d", &n);
		if (!n)
			break;
		assert(2<=n && n<= MAXN);
		for (i=0; i<n; i++)
		{
			for (j=0; j<n; j++)
			{
				scanf("%lf", &d);
				mat[0][i][j] = d;
			}
		}
		mul(1,0);
		while (dif())
		{
			mul(0,1);
			mul(1,0);
		}
		qual = -1;
		menor = 2.0L;
		for (i=0; i<n; i++)
		{
			if (fabs(mat[1][0][i]-menor) > EPS && mat[1][0][i] < menor)
			{
				qual = i;
				menor = mat[1][0][i];
			}
		}
		printf("%d\n", qual+1);
	}
	return 0;
}

*/