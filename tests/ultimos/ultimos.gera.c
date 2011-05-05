#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MASKINT 0x7fffffff
#define MAXN 100
#define MINN 1

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

void gera(int n)
{
	int i;

	printf("%d\n", n);
	for (i=0; i<n; i++)
	{
		v[i] = i+1;
	}
	
	embaralha(n);
	
	for (i=0; i<n; i++)
	{
		printf("%d\n", v[i]);
	}
}

int main()
{
	int i;

	printf("5\n");
	printf("3\n");
	printf("4\n");
	printf("2\n");
	printf("5\n");
	printf("1\n");
	printf("2\n");
	printf("1\n");
	printf("2\n");
	
	for (i=1; i<=100; i++)
	{
		gera(i);
	}
	
	
	printf("0\n");
	
	return 0;
}
