#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 100
#define EPS 1e-6L

int quali[MAXN];
int dist[MAXN][MAXN];


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
	int i, j, b, k;
	long double maior, temp, raiz;
	int qual;
	
	while (1)
	{
		assert(scanf("%d %d", &n, &b)==2);
		if (!n)
			break;
			
		assert(1<= b && b<= n && n <= MAXN);
		assert(2<=n && n<= MAXN);

		for (i=0; i<n; i++)
		{
			assert(scanf("%d", &quali[i]) == 1);
		}
		
		for (i=0; i<n; i++)
		{
			for (j=0; j<n; j++)
			{
				assert(scanf("%d", &dist[i][j]) == 1);
			}
		}
		
		for (i=0; i<n; i++)
		{
			for (j=0; j<n; j++)
			{
				raiz = sqrt((long double) quali[i]);
				temp = raiz;
				for (k=0; k<n; k++)
				{
					if (k == i)
						continue;
					temp += (long double)quali[k]/(long double)dist[i][k];
				}
				if (i==j)
					mat[0][i][j] = raiz/temp;
				else
					mat[0][i][j] = ((long double)quali[j]/(long double)dist[i][j])/temp;
			}
		}
		
		mul(1,0);
		while (dif())
		{
			mul(0,1);
			mul(1,0);
		}
		qual = -1;
		maior = -1;
		for (i=0; i<n; i++)
		{
			if (fabs(mat[1][0][i]-maior) > EPS && mat[1][0][i] > maior)
			{
				qual = i;
				maior = mat[1][0][i];
			}
		}
		printf("%d\n", qual+1);
	}
	return 0;
}