#include <cstdio>
#include <cassert>
#include <set>
#include <vector>
#include <utility>


#define MAXN (1000)
#define MAXCOORD (1000*1000)
#define MINCOORD (-MAXCOORD)

using namespace std;

set<pair<int, int> > dic;
vector<pair<int,int> > ptos;


int main()
{
	int n, i, j, resp;	
	int x, y;
	pair<int,int> p;
	
	while (1)
	{
		scanf("%d", &n);
		
		if (!n)
			break;
		
		assert(4<=n && n<= MAXN);
		
		for (i=0; i<n; i++)
		{
			scanf("%d %d", &x, &y);
			assert(MINCOORD <= x && x <= MAXCOORD);
			assert(MINCOORD <= y && y <= MAXCOORD);			
			
			p = make_pair(x,y);
			
			ptos.push_back(p);
			dic.insert(p);	
		}
		
		resp = 0;
		
		for (i=0; i<n; i++)
		{
			for (j=i+1; j<n; j++)
			{
				x = ptos[j].first - ptos[i].first;
				y = ptos[j].second - ptos[i].second;
				
				p = ptos[i];
				p.first += y;
				p.second += -x;
				
				if (dic.find(p)!=dic.end())
				{
					p = ptos[j];
					p.first += y;
					p.second += -x;		
					if (dic.find(p)!=dic.end())
						resp++;
				}

				p = ptos[i];
				p.first += -y;
				p.second += x;
				
				if (dic.find(p)!=dic.end())
				{
					p = ptos[j];
					p.first += -y;
					p.second += x;		
					if (dic.find(p)!=dic.end())
						resp++;
				}
				
				// TODO : gerar outros dois pontos e chegar no set.
				
			}
		}
		
		printf("%d\n", resp/4);
		
		ptos.clear();
		dic.clear();
	}
	
	return 0;
}
