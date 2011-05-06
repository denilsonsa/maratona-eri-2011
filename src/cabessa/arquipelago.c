#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAXN 50
#define TERRA 12345 
#define NAVIO 2222

char mapa [MAXN+2][MAXN+2];
char ehult [MAXN+2][MAXN+2];
int tab[MAXN+2][MAXN+2];
int m, n;

int delta[4][2] = {	{ 1, 0},
					{-1, 0},
					{ 0, 1},
					{ 0,-1}};

/*
2222  -> navio
12345 -> terra
0     -> agua
100X  -> X vizinhos necessarios
c     -> coberto por c navios (em particular, nao pode ter ninguem aqui)
-1    ->fronteira
*/

#define precisa(x) ((x)>=1000&&(x)<=1004)

void cobreviz (int a, int b)
{
	int i, j, k;
	
	for (k=0; k<4; k++)
	{
		for (i = a + delta[k][0], j = b + delta[k][1]; tab[i][j] >= 0 && tab[i][j]<=4; i += delta[k][0], j += delta[k][1])
		{
			tab[i][j]++;
		}
	}
}

void descobreviz (int a, int b)
{
	int i, j, k;
	
	for (k=0; k<4; k++)
	{
		for (i = a + delta[k][0], j = b + delta[k][1]; tab[i][j] >= 0 && tab[i][j]<=4; i += delta[k][0], j += delta[k][1])
		{
			tab[i][j]--;
		}
	}
}

int pracima(int a, int b)
{
	for (a--; tab[a][b] >= 0 && tab[a][b] <= 4; a--)
	{
		if (tab[a][b] == 0)
			return 1;
	}
	return 0;
}

int nvizinhos(int a, int b)
{
	int resp = 0;
	if (tab[a][b-1] == NAVIO)
		resp++;
	if (tab[a-1][b] == NAVIO)
		resp++;
	if (tab[a][b+1] == NAVIO)
		resp++;
	return resp;
}

void imprime()
{
	int i, j;
	for (i=1; i<=n; i++)
	{
		for (j=1; j<=m; j++)
		{
			if (tab[i][j] == NAVIO)
				printf("N");
			else
				printf("%c",mapa[i][j]);
		}
		printf("\n");
	}
	
}


/*
4 4
...1
X...
X...
..2.
*/


int avalia()
{
	int i, j, t;
	
	
	for (i=1; i<=n; i++)
	{
		for (j=1; j<=m; j++)
		{
			if (tab[i][j] == 0)
				return 0;
			if (tab[i][j] >=1000 && tab[i][j] <= 1004)
			{
				t = nvizinhos(i,j);
				if (tab[i+1][j] == NAVIO)
					t++;
				if (t+1000!=tab[i][j])
					return 0;
			}
		}
	}
	return 1;
}

int bt(int a, int b)
{
	int nv;
	
	if (b == m+1)
		return bt(a+1, 1);
	
	if (a > n)
		return avalia();
	
	if (ehult[a][b]) /*eh a ultima chance de alguem*/
	{
		if (pracima(a,b)) /*se tem zero pra cima*/
		{
			if (tab[a][b] != 0) /*estah em conflito, o zero acima não pode ser sat */
				return 0;
			else /*eh obrigado a ter navio*/
			{
				cobreviz(a,b);
				tab[a][b] = NAVIO;
				if (bt(a, b+1))
					return 1;
				tab[a][b] = 0;
				descobreviz(a,b);
				return 0;
			}
		}
	}
	
	if (a>1)
	if (precisa(tab[a-1][b]) )   /*tem um porto adjacente acima */
	{
		nv = nvizinhos(a-1,b);
		if (nv > (tab[a-1][b]-1000))
			return 0;
		if (nv == (tab[a-1][b]-1000))
			return bt(a, b+1);
		if (nv + 1 != (tab[a-1][b]-1000))
			return 0;
		if (tab[a][b] != 0)
			return 0;
		cobreviz(a,b);
		tab[a][b] = NAVIO;
		if (bt(a, b+1))
			return 1;
		tab[a][b] = 0;
		descobreviz(a,b);
		return 0;
	}


	if(tab[a][b] == 0)
	{
		cobreviz(a,b);
		tab[a][b] = NAVIO;
		if (bt(a, b+1))
			return 1;
		tab[a][b] = 0;
		descobreviz(a,b);
		if (bt(a, b+1))
			return 1;
		return 0;
	}
	return bt(a, b+1);
}


int main()
{
	int i, j;
	
	while (1)
	{
		assert(scanf("%d %d", &n, &m) == 2);
		
		if (!n)
		{
			assert(!m);
			break;
		}
		
		assert(2 <= n && n <= 50);
		assert(2 <= m && m <= 50);
		
		for (i=1; i<=n; i++)
		{
			scanf("%s", &mapa[i][1]);
			for (j=1; j<=m; j++)
			{
				switch(mapa[i][j])
				{
					case '.':
						tab[i][j] = 0;
						break;
					case 'X':
						tab[i][j] = TERRA;
						break;
					default:
						if (mapa[i][j] >= '0' && mapa[i][j] <= '4')
							tab[i][j] = 1000 + (int) mapa[i][j] - '0';
						else
							assert(0);
				}
			}
		}
		
		for (i=0; i<=n+1; i++)
		{
			tab[i][0] = -1;
			tab[i][m+1] = -1;
		}

		for (j=0; j<=m+1; j++)
		{
			tab[0][j] = -1;
			tab[n+1][j] = -1;
		}
		
		
		memset(ehult, 0, sizeof(ehult));
		
		for (i=1; i<=n; i++)
		{
			for (j=1; j<=m; j++)
			{
				if (tab[i][j] == 0 && tab[i+1][j]!=0 && tab[i-1][j] == 0)
					ehult[i][j] = 1;
			}
		}
		
		if (bt(1,1))
		{
			imprime();
		}
		else
			printf("IMPOSSIVEL\n");
	}
	return 0;
}
