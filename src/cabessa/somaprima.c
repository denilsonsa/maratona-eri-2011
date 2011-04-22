#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAXN (1000*1000)

#define MAXP (MAXN/2)

char ehprimo[MAXP];
int np;
int primo[MAXP];
char ehsp[MAXN+1];



void crivo()
{
	int i, j;
	
	memset(ehprimo, 1, sizeof(ehprimo));
	
	ehprimo[0] = ehprimo[1] = 0;
	
	for (i=2; i<MAXP/i; i++)
	{
		if (!ehprimo[i])
			continue;
			
		for (j=i*i; j<MAXP; j+=i)
			ehprimo[j] = 0;
	}
	
	np = 0;
	for (i=0; i<MAXP; i++)
	{
		if (ehprimo[i])
		{
			primo[np] = i;
			np++;
		}
	}
	
}

void somas()
{
	int i, j, soma;
	
	memset(ehsp, 0, sizeof(ehsp));
	
	for (i=0; i<np; i++)
	{
		soma = primo[i];
		
		for (j=i+1; j<np; j++)
		{
			soma += primo[j];
			if (soma > MAXN)
				break;
			if (ehprimo[j-i+1])
			{
				ehsp[soma] = 1;
			}
		}
	}
	
}

int main()
{
	int n;
	
	crivo();
	
	somas();
	
	while (1)
	{
		scanf("%d", &n);
		if (!n)
			break;
		assert(n>=2 && n<=MAXN);
		
		if (ehsp[n])
			printf("SIM\n");
		else
			printf("NAO\n");
	}
	return 0;
}