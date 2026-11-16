#include<bits/stdc++.h>
using namespace std;
namespace _yz
{
	typedef int ll;
	const ll N=1200000+10;
	struct Str{ll l,r;}C,AB,tmp;
	struct Cnt{ll b[30];}cnt[N]; 
	char S[N];　
	ll n,ans=0,t[N];
	void init()
	{
		cin>>(S+1);
		n=strlen(S+1); ans=0;
		memset(cnt,0,sizeof(cnt));
		for(ll i=1;i<=n;i++)
		{
			cnt[i]=cnt[i-1];
			cnt[i].b[S[i]-'a'+1]++;
		}
	}
	void get(ll l,ll r,Str &g){g.l=l;g.r=r;}
	ll count(Str g)
	{
		ll jud=0;
		for(ll i=1;i<=26;i++)
		{
			ll ct=cnt[g.r].b[i]-cnt[g.l-1].b[i];
			if(ct%2==1) jud++;
		}
		return jud;
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
			for(ll j=0;j<=26;j++) t[j]=0;
			for(ll j=AB.l;j<=AB.r-1;j++)//此处减一小细节 
				t[count((Str){AB.l,j})]++;
			for(ll j=0;j<=26;j++) t[j]+=t[j-1];
			ans+=t[count(C)];　
			for(ll j=i;j<=n;j+=i)
			{　
				if(j+i>=n)　break;
				get(j+1,j+i,tmp);　
				if(equal(AB,tmp)==0)　break;
				get(j+i+1,n,C);
				ans+=t[count(C)];
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
