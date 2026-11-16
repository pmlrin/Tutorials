#include<bits/stdc++.h>
using namespace std;
namespace _yz
{
	typedef long long ll;
	const ll N=1200000+10,M=200;
	struct Str{ll l,r;}C,AB,tmp;
	char S[N];
	ll n,ans=0,b[M],pre[N],suf[N],t[M],z[N];
	
	ll lb(ll x){return x&-x;}
	void update(ll x){while(x<=27) t[x]++,x+=lb(x);}
	ll query(ll x)
	{
		ll ret=0;
		while(x) ret+=t[x],x-=lb(x);
		return ret;
	}
	
	void exKMP()
	{
		ll k=2; z[1]=n;
		for(ll i=1;i+1<=n&&S[i]==S[i+1];z[2]=i,i++);
		for(ll i=3;i<=n;i++)
		{
			ll p=k+z[k]-1,y=z[i-k+1];
			if(i+y-1<p)　z[i]=y;
			else
			{
				z[i]=max(p-i+1,0ll);
				for(
					ll j=max(p-i+2,1ll);
					i+j-1<=n&&S[i+j-1]==S[j];
					z[i]=j,k=i,j++
				);
			}
		}
	}
	ll getrpt(Str AB,Str C)
	{
		ll i=AB.r;
		ll ret=z[i+1]/i+1;
		if(i+1+z[i+1]-1==n&&n%i==0) return ret-1;
		else return ret;
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
		memset(z,0,sizeof(z));
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
	void O(Str g){for(ll i=g.l;i<=g.r;i++) cout<<S[i];}
	void solve()
	{
		for(ll i=2;i<=n-1;i++)
		{
			ll rpt,a1=0,a2=0;
			get(1,i,AB); get(i+1,n,C);
			update(pre[i-1]+1);
			rpt=getrpt(AB,C);
			　
			get(i*(rpt-1)+1,n,C);
			if(rpt!=1) a1=query(suf[C.l]+1);//ABC 
			get(i*rpt+1,n,C);
			a2=query(suf[C.l]+1);//C
			if(rpt%2==0) ans+=(rpt/2)*(a1+a2);//ABABABABC
			else ans+=(rpt/2)*a1+(rpt-rpt/2)*a2;//ABABABC
		}
	}
	void main()
	{
		ll T;
		cin>>T;
		while(T--)
		{
			init();
			exKMP();
			solve();
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
