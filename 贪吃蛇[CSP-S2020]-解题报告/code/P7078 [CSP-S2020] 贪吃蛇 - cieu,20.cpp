#include<bits/stdc++.h>
using namespace std;
namespace _yz
{
	typedef long long ll;
	const ll N=1000000+10;
	struct Snakes{ll id,hp;}s[N];
	ll n,ans=0;
	void yzmain()
	{
		ll T,t1,t2,k;
		scanf("%lld",&T);
		for(ll qwq=1;qwq<=T;qwq++)
		{
			if(qwq==1)
			{
				scanf("%lld",&n);
				for(ll i=1;i<=n;i++)
				{
					scanf("%lld",&s[i].hp);
					s[i].id=i;
				}
			}
			else
			{
				scanf("%lld",&k);
				for(ll i=1;i<=k;i++)
				{
					scanf("%lld%lld",&t1,&t2);
					s[t1].hp=t2;
				}
			}
			if(s[3].hp-s[1].hp>=s[2].hp) ans=1;
			else ans=3; 
			printf("%lld\n",ans);
		}
		return;
	}
}
int main()
{
	//freopen("snakes.in","r",stdin);
	//freopen("out.txt","w",stdout);
	_yz::yzmain();
	return 0;
}
