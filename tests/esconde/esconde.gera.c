#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MASKINT 0x7fffffff
#define MAXN 1000
#define MINN 2

int mrand()
{
	return ((rand()<<15)+(rand()<<30)+rand())&MASKINT;
}

int mrandab(int a, int b)
{
	return a + (mrand() % (b-a+1));
}

int v[MAXN];

void embaralha(int n)
{
	int i;
	int temp, t;
	for (i=n-1; i>0; i--)
	{
		t = mrandab(0, i);
		temp = v[i];
		v[i] = v[t];
		v[t] = temp;
	}
}


void gera_caso(int n)
{
	int i;
	for (i=0; i<n; i++)
	{
		v[i] = i+1;
	}
	embaralha(n);
	
	printf("%d %d\n", n, v[0]);
	
	for (i=1; i<(n-1); i++)
	{
		printf("%d\n", v[i]);
	}
}


int main()
{
	int cas;
	
	printf("3 2\n");
	printf("1\n");
	printf("5 1\n");
	printf("2\n");
	printf("3\n");
	printf("4\n");
	printf("4 4\n");
	printf("3\n");
	printf("2\n");

	gera_caso(MINN);

	for (cas=8; cas < 100; cas++)
	{
		gera_caso(mrandab(MINN, MAXN));
	}
	
	gera_caso(MAXN);
	gera_caso(MAXN);
	gera_caso(MAXN);
	gera_caso(MAXN);
	

	printf("0 0\n");
	return 0;
}
