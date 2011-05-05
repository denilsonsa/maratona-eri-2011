#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MASKINT 0x7fffffff
#define MAXN 1000
#define MINN 4

int mrand()
{
	return ((rand()<<15)+(rand()<<30)+rand())&MASKINT;
}

int mrandab(int a, int b)
{
	return a + (mrand() % (b-a+1));
}


#define MINX -1000000
#define MAXX 1000000

void gera_muito(int passo)
{
	int i, j;
	int tot = 30;
	
	printf("%d\n", (tot+1)*(tot+1));
	
	for (i=0; i<=tot; i++)
	{
		for (j=0; j<=tot; j++)
		{
			printf("%d %d\n", i*passo, j*passo);
		}
	}
	
}

int x[MAXN];
int y[MAXN];

void gera_aleat(int n, int minx, int maxx)
{
	int i, j;
	
	printf("%d\n", n);
	
	for (i=0; i<n; i++)
	{
		x[i] = mrandab(minx,maxx);
		y[i] = mrandab(minx,maxx);
		
		for (j=0; j<i; j++)
		{
			if (x[i] == x[j] && y[i] == y[j])
				j = i+10;
		}
		
		if (j>=i+10)
		{
			i--;
			continue;
		}
		printf("%d %d\n", x[i], y[i]);
	}
}


int main()
{
	int i;
	
	printf("6\n");
	printf("1 0\n");
	printf("0 1\n");
	printf("2 1\n");
	printf("1 2\n");
	printf("0 -1\n");
	printf("2 -1\n");
	
	printf("4\n");
	for (i=0; i<4; i++)
	{
		printf("%d %d",mrandab(MINX, MAXX),mrandab(MINX, MAXX));
	}

	printf("4\n");
	printf("1 0\n");
	printf("0 1\n");
	printf("0 0\n");
	printf("1 1\n");

	gera_aleat(MAXN, MINX, MAXX);
	gera_aleat(MAXN, MINX, MAXX);
	gera_aleat(MAXN, MINX/1000, MAXX/1000);
	gera_aleat(MAXN, MINX/1000, MAXX/1000);
	gera_aleat(MAXN, MINX/100, MAXX/100);
	gera_aleat(MAXN, MINX/100, MAXX/100);
	
	for (i=0; i<20; i++)
	{
		gera_aleat(mrandab(MINN,MAXN), MINX, MAXX);
		gera_aleat(mrandab(MINN,MAXN), MINX, MAXX);
		gera_aleat(mrandab(MINN,MAXN), MINX/1000, MAXX/1000);
		gera_aleat(mrandab(MINN,MAXN), MINX/1000, MAXX/1000);
		gera_aleat(mrandab(MINN,MAXN), MINX/100, MAXX/100);
		gera_aleat(mrandab(MINN,MAXN), MINX/100, MAXX/100);
	}
	
	gera_muito(1);
	gera_muito(10);
	gera_muito(-100);

	printf("0\n");
	return 0;
}
