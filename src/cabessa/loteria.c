#include <stdio.h>
#include <assert.h>
#include <string.h>

#define MAXDIG 30

int main()
{
	int i, j;
	char c;
	
	while (1)
	{
		scanf(" %c", &c);
		
		if (c == '0')
			break;
			
		assert(c <= '9' && c>= '0');
		
		i = c - '0';
		j = 1;
		
		while (1)
		{
			scanf("%c", &c);
			if (!(c>='0'&&c<='9'))
				break;
				
			j++;
			assert (j <= MAXDIG);
			
			i = i*10 + c - '0';
			i %= 42;
		}
		
		if (!i%42)
			printf("PREMIADO\n");
		else
			printf("TENTE NOVAMENTE\n");
	}
	
	return 0;
}
