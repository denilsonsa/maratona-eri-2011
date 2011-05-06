#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MASKINT 0x7fffffff
#define MAXN (1000)
#define MINN 2

int mrand()
{
	return ((rand()<<15)+(rand()<<30)+rand())&MASKINT;
}

int mrandab(int a, int b)
{
	return a + (mrand() % (b-a+1));
}

int vetor[MAXN];

void embaralha(int n)
{
	int i;
	int temp, t;
	for (i=n-1; i>0; i--)
	{
		t = mrandab(0, i);
		temp = vetor[i];
		vetor[i] = vetor[t];
		vetor[t] = temp;
	}
}


char adj[MAXN][MAXN];

typedef struct
{
	int u, v;
}aresta;

aresta a[MAXN*(MAXN-1)/2];

void embaralha2(int n)
{
	int i;
	aresta temp;
	int  t;
	
	for (i=n-1; i>0; i--)
	{
		t = mrandab(0, i);
		temp = a[i];
		a[i] = a[t];
		a[t] = temp;
	}
}


void gera(int n, int m)
{
	int i, j, t;
	int m2;
	
	printf("%d %d\n", n, m);
	
	for (i=0; i<n; i++)
	{
		vetor[i] = i;
	}
	
	embaralha(n);
	
	memset(adj, 0, sizeof(adj));
	
	for (i=1; i<n; i++)
	{
		t = mrandab(0, i-1);
		adj[vetor[i]][vetor[t]] = 1;
		adj[vetor[t]][vetor[i]] = 1;
		printf("%d %d\n", vetor[i]+1, vetor[t]+1);
	}

	
	/*n-1 arestas adicionadas*/
	m -= n-1;
	m2 = 0;

	for (i=0; i<n; i++)
	{
		for (j=0; j<i; j++)
		{
			if (adj[i][j] == 0)
			{
				if (rand()%2)
				{
					a[m2].u = i;
					a[m2].v = j;
				}
				else
				{
					a[m2].u = j;
					a[m2].v = i;
				}
				m2++;
			}
		}
	}

	
	embaralha2(m2);
	
	for (i=0; i<m; i++)
	{
		printf("%d %d\n", a[i].u+1, a[i].v+1);
	}
	
}

int main()
{
	int i;
	int n;
	printf("3 2\n");
	printf("1 2\n");
	printf("2 3\n");
	printf("3 3\n");
	printf("3 2\n");
	printf("1 3\n");
	printf("2 1\n");
	printf("5 5\n");
	printf("1 2\n");
	printf("1 5\n");
	printf("2 3\n");
	printf("2 5\n");
	printf("4 5\n");
	
	

	gera(MAXN, MAXN*(MAXN-1)/2);

	gera(MAXN, MAXN-1);

	gera(MAXN, MAXN-1);
	gera(MAXN, MAXN-1);
	gera(MAXN, MAXN-1);
	gera(MAXN, MAXN-1);
	gera(MINN, MINN-1);
	
	for (i=0; i<256; i++)
	{
		n = 16;
		gera(n, mrandab(n-1,n*(n-1)/2));
	}	

	for (i=0; i<8; i++)
	{
		gera(MAXN, mrandab(MAXN-1,MAXN*(MAXN-1)/8));
		n = mrandab(MINN, MAXN/10);
		gera(n, n*(n-1)/2);
		gera(n, n-1);
	}

	for (i=0; i<25; i++)
	{
		n = mrandab(MINN, MAXN);
		gera(n, mrandab(n-1,n*(n-1)/2));
	}
	
	
	printf("0 0\n");
	return 0;
}
