#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

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
