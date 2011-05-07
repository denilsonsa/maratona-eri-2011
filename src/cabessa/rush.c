#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXN 100
#define INF 0x3f3f3f3f

#define min(a,b) ((a)<(b)?(a):(b))

int fila[MAXN];
int pai[MAXN];
char foi[MAXN];
int adj[MAXN][MAXN];

int n;

int busca(int s, int t)
{
	int i,at;
	int ini=0, fim=1;
	
	fila[0] = s;
	memset(foi, 0, sizeof(foi));
	foi[s] = 1;
	pai[s] = -1;
	
	while (ini!=fim)
	{
		at = fila[ini];
		ini++;
		if (at == t)
			return 1;
		for (i=0; i<n; i++)
		{
			if (adj[at][i]>0 && !foi[i])
			{
				fila[fim] = i;
				fim++;
				foi[i] = 1;
				pai[i] = at;
			}
		}
	}
	return 0;
}

int fluxo(int s, int t)
{
	int i;
	int f, ftotal = 0;
	assert(s!=t);
	while (busca(s, t))
	{		
		f = INF;
		for (i=t; i!=s; i=pai[i])
		{
			f = min(f,adj[pai[i]][i]);
		}
		
		ftotal+=f;
		
		for (i=t; i!=s; i=pai[i])
		{
			adj[pai[i]][i]-=f;
			adj[i][pai[i]]+=f;
		}
	}
	return ftotal;
}

int grau[MAXN];

int main()
{
	int i, j, p, m, u, v, w;
	int achei;
	
	while (1)
	{
		assert(scanf("%d %d %d", &p, &n, &m)==3);
		
		if (p == 0)
		{
			assert(n == 0 && m == 0);
			break;
		}
		
		assert(1 <= p && p <= 1000);
		assert(2 <= n && n <= MAXN);
		assert(1 <= m && m <= n*(n-1));
		
		n++;
		
		for (i=0; i<n; i++)
		{
			grau[i] = 0;
			
			for (j=0; j<n; j++)
			{
				adj[i][j] = 0;
			}
		}
		
		
		
		for (i=0; i<m; i++)
		{
			assert(scanf("%d %d %d", &u, &v, &w)==3);
			assert(1 <= u && u <= n);
			assert(1 <= v && v <= n);
			assert(1 <= w && w <= 10);
			
			assert(adj[u][v] == 0);
			
			adj[u][v] = w;
			
			grau[u] ++;
		}
		
		achei = 0;
		for (i=1; i<n; i++)
		{
			if (grau[i] == 0)
			{
				adj[i][0] = INF;
			}
			achei = 1;
		}
		assert(achei == 1);
		
		achei = fluxo(1,0);
		
		if (achei < p)
		{
			printf("COM GARGALOS\n");
		}
		else
		{
			printf("SEM GARGALOS\n");
		}
	}

	return 0;
}
