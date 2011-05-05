#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MASKINT 0x7fffffff
#define MAXN 1000000
#define MINN 1

int mrand()
{
	return ((rand()<<15)+(rand()<<30)+rand())&MASKINT;
}

int mrandab(int a, int b)
{
	return a + (mrand() % (b-a+1));
}

char s1[MAXN+1], s2[MAXN+1];
char temp[MAXN+1];

void gera1(int n, int TAM)
{
	int i;
	char ini, fim;
	
	s1[0] = s2[0] = 0;
	
	ini = mrandab('a', 't');
	fim = mrandab(ini+1, ini+'z'-'t');
	
	for (i=0; i<TAM; i++)
	{
		temp[i] = mrandab(ini, fim);
	}
	temp[TAM] = 0;
	
	strcpy(s1, temp);	
	strcpy(s2, temp);	
	
	for (i=2; i<n/TAM; i++)
	{
		strcat(s1,temp);
	}
	for (i=2; i<n/TAM/2; i++)
	{
		strcat(s2,temp);
	}
	
	printf("%s %s\n", s1, s2);
	printf("%s %s\n", s2, s1);
	
	
}

void gera2(int n, int m)
{
	int i;
	
	for (i=0; i<n; i++)
	{
		s1[i] = mrandab('a', 'z');
	}
	s1[n] = 0;

	for (i=0; i<m; i++)
	{
		s2[i] = mrandab('a', 'z');
	}
	s2[m] = 0;
	
	printf("%s %s\n", s1, s2);
	
}

void gera3(int n, int TAM)
{
	int i;
	char ini, fim;
	
	s1[0] = s2[0] = 0;
	
	ini = mrandab('a', 't');
	fim = mrandab(ini+1, ini+'z'-'t');
	
	for (i=0; i<TAM; i++)
	{
		temp[i] = mrandab(ini, fim);
	}
	temp[TAM] = 0;
	
	strcpy(s1, temp);	
	strcpy(s2, temp);	
	
	for (i=2; i<n/TAM; i++)
	{
		strcat(s1,temp);
	}
	for (i=2; i<n/TAM/2; i++)
	{
		strcat(s2,temp);
	}
	
	printf("%s %s\n", s1, s2);
	
	s1[strlen(s1)-1] = 'z';
	
	printf("%s %s\n", s2, s1);
	
	
}

void gera4(int n)
{
	int i;
	
	for (i=0; i<n; i++)
	{
		s1[i] = mrandab('a', 'z');
	}
	s1[n] = 0;

	strcpy(s2, s1);
	
	printf("%s %s\n", s1, s2);

	s1[strlen(s1)/2] = 'z';

	printf("%s %s\n", s1, s2);

}


int main()
{
	int i;

	printf("aa aaa\n");
	printf("abra cadabra\n");
	printf("abcabcabcabcabcabc abcabcabcabc\n");
	printf("rai mano\n");

	printf("abcabcabcabcabcabc abcabcabcabcabcabcabcabcabcabcabcaba\n");	

	gera1(MAXN,5);
	gera1(MAXN,3);
	gera1(MAXN,100);
	gera1(MAXN,4);
	gera1(MAXN,18);
	gera2(MAXN,MAXN);
	gera2(MAXN,MAXN);
	gera3(MAXN,5);
	gera4(MAXN);
	
	for (i=0; i<5; i++)
	{
		gera1(mrandab(101,10003),5);
		gera1(mrandab(101,10003),3);
		gera1(mrandab(101,10003),100);
		gera1(mrandab(101,10003),4);
		gera1(mrandab(101,10003),18);
		gera2(mrandab(500, 40000),mrandab(500, 40000));
		gera3(mrandab(101,100023),5);
		gera3(mrandab(101,100033),3);
		gera3(mrandab(101,100034),100);
		gera3(mrandab(101,100035),4);
		gera3(mrandab(101,100036),18);
		gera4(mrandab(5, MAXN/100));
	}


	printf("# #\n");
	return 0;
}