#include<bits/stdc++.h>
using namespace std;
namespace _yz
{
	typedef int ll;
	const ll N=1200000+10,M=200;
	struct Str{ll l,r;}C,AB,tmp;
	char S[N];　
	ll n,ans=0,b[M],pre[N],suf[N],t[M];
	
	ll lb(ll x){return x&-x;}
	void update(ll x){while(x<=27) t[x]++,x+=lb(x);}
	ll query(ll x)
	{
		ll ret=0;
		while(x)　ret+=t[x],x-=lb(x);
		return ret;
	}
	
	void get(ll l,ll r,Str &g){g.l=l;g.r=r;}
	void init()
	{
		cin>>(S+1);
		n=strlen(S+1); ans=0;
		memset(b,0,sizeof(b));
		memset(t,0,sizeof(t));
		memset(pre,0,sizeof(pre));
		memset(suf,0,sizeof(suf));
		for(ll i=1;i<=n;i++)
		{
			b[S[i]]++;　pre[i]=pre[i-1];
			if(b[S[i]]%2==1) pre[i]++;
			else pre[i]--;
		}
		memset(b,0,sizeof(b));
		for(ll i=n;i>=1;i--)
		{
			b[S[i]]++;　suf[i]=suf[i+1];
			if(b[S[i]]%2==1) suf[i]++;
			else suf[i]--;
		}
	}
	ll equal(Str g,Str h)
	{
		if(g.r-g.l!=h.r-h.l) return 0;
		for(ll i=0;i<=g.r-g.l;i++)
			if(S[g.l+i]!=S[h.l+i]) return 0;
		return 1;
	}
	void O(Str g){for(ll i=g.l;i<=g.r;i++) cout<<S[i];}
	void cheat()
	{
		for(ll i=2;i<=n-1;i++)
		{
			get(1,i,AB);　get(i+1,n,C);
			update(pre[i-1]+1);
			ans+=query(suf[C.l]+1);
			for(ll j=i;j<=n;j+=i)
			{
				if(j+i>=n) break;
				get(j+1,j+i,tmp);
				if(equal(AB,tmp)==0) break;
				get(j+i+1,n,C);
				ans+=query(suf[C.l]+1);
			}
		}
	}
	void main()
	{
		ll T;
		cin>>T;
		while(T--)
		{
			init();
			cheat();
			cout<<ans<<endl;
		}
		return;
	}
}
int main()
{
	_yz::main();
	return 0;
}　
