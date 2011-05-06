#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <algorithm>

#define MAXN (1000)
#define MAXM (MAXN*MAXN)

using namespace std;

int m, n;

typedef struct{
		int v[MAXN];
}tipo;

int fc (const void*e1, const void *e2)
{
	tipo *t1, *t2;
	int i;
	
	t1 = (tipo*)e1;
	t2 = (tipo*)e2;
	
	for (i=0; i<n; i++)
	{
		if (t1->v[i] != t2->v[i])
			return t1->v[i] - t2->v[i];
	}
	return 0;
}


tipo adj[MAXN];

#define comb(n) ((n)*((n)-1)/2)

int igual(int v1[], int v2[])
{
	int i;
	
	for (i=0; i<n; i++)
	{
		if (v1[i]!=v2[i])
			return 0;
	}
	
	return 1;
}



int main()
{
	int i, a, b, j, resp;
		
	while (1)
	{
	
		assert(scanf("%d %d", &n, &m)==2);
		resp = 0;
		
		if (n == 0)
		{
			assert(m==0);
			break;
		}
		
		memset(adj, 0, sizeof(adj));
		
		for (i=0; i<m; i++)
		{
			scanf("%d %d", &a, &b);
			a--;
			b--;
			
			adj[a].v[b] = adj[b].v[a] = 1;
		}
		
		for (i=0; i<n; i++)
			adj[i].v[i] = 1;
		
		qsort(adj, n, sizeof(adj[0]), fc);
		
		for (i=0; i<n; )
		{
			for (j=i+1; j<n; j++)
			{
				if (!igual(adj[i].v, adj[j].v))
					break;
			}
			resp+=comb(j-i);
			i = j;
		}
		printf("%d\n", resp);
	}

	return 0;
}
