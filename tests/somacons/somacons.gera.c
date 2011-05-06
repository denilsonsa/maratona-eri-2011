#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MASKINT 0x7fffffff
#define MAXN (1000*1000*1000)
#define MINN 2

int mrand()
{
	return ((rand()<<15)+(rand()<<30)+rand())&MASKINT;
}

int mrandab(int a, int b)
{
	return a + (mrand() % (b-a+1));
}


int main()
{
	int i, j, t;
	printf("5\n");
	printf("6\n");
	printf("7\n");
	printf("8\n");
	printf("9\n");
	printf("10\n");
	
	for (i=MINN; i<MINN+10000; i++)
	{
		printf("%d\n", i);
	}
	
	for (i=0; i<100; i++)
	{
		t = mrandab(MINN+10000, MAXN-10000);
		for (j=t; j<t+100; j++)
		{
			printf("%d\n", j);
			mrandab(MINN+10000, MAXN-10000);
		}
	}

	for (i=MAXN; i>MAXN-10000; i++)
	{
		printf("%d\n", i);
	}
	
	for (i=2; i<MAXN; i*=2)
	{
		printf("%d\n", i);
	}

	
	printf("0\n");
	return 0;
}


