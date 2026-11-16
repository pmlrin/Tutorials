#include<bits/stdc++.h>
using namespace std;
namespace _yz
{
	typedef long long ll;
	const ll N=1200000+10,M=200;
	struct Str{ll l,r;}C,AB,tmp;
	char S[N];
	ll n,ans=0,b[N],pre[N],suf[N],t[M],nxt[N],r[N];
	
	ll lb(ll x){return x&-x;}
	void update(ll x){while(x<=27) t[x]++,x+=lb(x);}
	ll query(ll x)
	{
		ll ret=0;
		while(x) ret+=t[x],x-=lb(x);
		return ret;
	}
	
	void KMP()
	{
		memset(b,0,sizeof(b));
		memset(nxt,0,sizeof(nxt));
		ll j=nxt[0]=nxt[1]=0;
		for(ll i=2;i<=n-1;i++)
		{
			while(j&&S[i]!=S[j+1]) j=nxt[j];
			if(S[i]==S[j+1]) j++;
			nxt[i]=j;
		}
		for(ll i=n-1;i>=1;i--)
		{
			ll e=i-nxt[i];
			if(i%e) continue;
			if(r[e]==1) r[e]=i/e;
			else if(r[i]==1) r[i]=r[e]/(i/e);
		}
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
			b[S[i]]++; pre[i]=pre[i-1];
			if(b[S[i]]%2==1) pre[i]++;
			else pre[i]--; r[i]=1;
		}
		memset(b,0,sizeof(b));
		for(ll i=n;i>=1;i--)
		{
			b[S[i]]++; suf[i]=suf[i+1];
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
			rpt=r[i];
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
			KMP();
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
