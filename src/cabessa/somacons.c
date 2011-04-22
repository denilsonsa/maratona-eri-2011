#include <stdio.h>
#include <assert.h>

#define MAXN (1000*1000*1000)


int main()
{	
	int n;
	
	while (1)
	{
		scanf("%d", &n);
		if (!n)
			break;
		assert(1<=n && n <= MAXN);
		
		while (n%2 == 0)
		{
			n = n>>1;
		}
		n = n>>1;
		if (n)
			printf("SIM\n");
		else
			printf("NAO\n");
	}
	
	return 0;
}
