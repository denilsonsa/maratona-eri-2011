#include <stdio.h>
#include <assert.h>
#include <string.h>

#define MAX (1000*1000)

char r[MAX+1], s[MAX+1];
char t1[2*MAX+1], t2[2*MAX+2];

int mdc(int a, int b)
{
	if (a < b)
	{
		return mdc (b, a);
	}
	
	if (b == 0)
		return a;
	
	return mdc (b, a%b);
}

int main()
{
	int i;
	int x, y;
	while (1)
	{
		assert(scanf("%s %s",r,s) == 2);
		
		if (!strcmp(r,"#"))
		{
			assert(!strcmp(s,"#"));
			break;
		}
		
		for (i=0; r[i]; i++)
			assert(r[i]<='z' && r[i] >= 'a');
		
		for (i=0; s[i]; i++)
			assert(s[i]<='z' && s[i] >= 'a');
		
		assert(strlen(r)<=MAX);
		assert(strlen(s)<=MAX);
				
		strcpy(t1, r);
		strcat(t1, s);

		strcpy(t2, s);
		strcat(t2, r);
		
		if (strcmp(t1,t2))
		{
			printf("NAO\n");
		}
		else
		{
			x = strlen(r);
			y = strlen(s);
			i = mdc(x,y);
			printf("%d %d\n", y/i,x/i);
		}
		
	}
	return 0;
}
