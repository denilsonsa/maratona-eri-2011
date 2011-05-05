#include <stdio.h>
#include <assert.h>

#define MAXN 1000

int main()
{
	int n, soma, i, t;
	
	while (1)
	{
		scanf("%d", &n);
		if (!n)
			break;
		assert(2<=n && n<=MAXN);
		soma = 0;
		for (i=1; i<n; i++)
		{
			scanf("%d", &t);
			soma+=t;
		}
		printf("%d\n", n*(n+1)/2-soma);
	}
	return 0;
}
