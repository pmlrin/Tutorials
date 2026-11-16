#include<bits/stdc++.h>
using namespace std;
namespace _yz
{
	typedef long long ll;
	const ll N=1000000+10;
	ll n,m,nxt[N];
	char a[N],b[N];
	void getnxt()
	{
		ll j=nxt[0]=nxt[1]=0; n=strlen(b+1);
		for(ll i=2;i<=n;i++)
		{
			while(j&&b[i]!=b[j+1]) j=nxt[j];
			if(b[i]==b[j+1]) j++;
			nxt[i]=j;
		}
	}
	void KMP()
	{
		ll j=0; m=strlen(a+1);
		for(ll i=1;i<=m;i++)
		{
			while(j&&a[i]!=b[j+1]) j=nxt[j];
			if(a[i]==b[j+1]) j++;
			if(j==n) printf("%d\n",i-n+1);
		}
	}
	void main()
	{
		cin>>a+1>>b+1;
		getnxt();
		KMP();
		for(ll i=1;i<=n;i++) printf("%d ",nxt[i]); 
		return;
	}
}
int main()
{
	_yz::main();
	return 0;
}
