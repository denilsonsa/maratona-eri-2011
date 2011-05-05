#include <stdio.h>
#include <assert.h>

#define MAXN 100

int v[MAXN];

int main()
{
	int i, n;
	
	while (1)
	{
		scanf("%d", &n);
		if (!n)
			break;
			
		assert(1<=n && n<=MAXN);
		
		for (i=0; i<n; i++)
		{
			scanf("%d", &v[i]);
		}
		
		for (i=n-1; i>=0; i--)
		{
			printf("%d\n", v[i]);
		}
		printf("0\n");
	}
	
	
	return 0;
}