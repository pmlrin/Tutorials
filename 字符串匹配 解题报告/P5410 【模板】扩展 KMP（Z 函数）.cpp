#include<bits/stdc++.h>
using namespace std;
namespace _yz
{
	typedef long long ll;
	const ll N=20000000+10; 
	char a[N],b[N];
	ll n,m,z[N],ext[N],ans;
	void exKMP()　
	{　
		ll k=1; n=strlen(b); z[0]=n;
		for(ll i=0;i+1<=n-1&&b[i]==b[i+1];z[1]=i+1,i++);
		for(ll i=2;i<=n-1;i++)
		{
			ll p=k+z[k]-1,y=z[i-k];
			if(i+y-1<p) z[i]=y;　
			else
			{
				for(
					ll j=z[i]=max(p-i+1,0ll);
					i+j<=n-1&&b[i+j]==b[j];
					z[i]=j+1,k=i,j++
				);
			}
		}
	}
	void getext()
	{
		ll k=0; m=strlen(a);
		for(ll i=0;i<=min(n,m)-1&&a[i]==b[i];ext[0]=i+1,i++);
		for(ll i=1;i<=m-1;i++)
		{
			ll p=k+ext[k]-1,y=z[i-k];
			if(i+y-1<p) ext[i]=y;
			else　
			{
				for(
					ll j=ext[i]=max(p-i+1,0ll);
					i+j<=m-1&&j<=n-1&&a[i+j]==b[j];
					ext[i]=j+1,k=i,j++
				);
			}
		}
	}
	void main()
	{
		cin>>a>>b;　
		exKMP(); getext();
		for(ll i=0;i<=n-1;i++) ans^=(i+1)*(z[i]+1);
		printf("%lld\n",ans); ans=0;
		for(ll i=0;i<=m-1;i++) ans^=(i+1)*(ext[i]+1);
		printf("%lld\n",ans);
		return;
	}
}
int main()
{
	_yz::main();
	return 0;
}
