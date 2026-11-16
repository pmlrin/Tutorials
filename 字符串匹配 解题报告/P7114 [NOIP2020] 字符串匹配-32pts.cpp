#include<bits/stdc++.h>
using namespace std;
namespace _yz　
{
	typedef long long ll;
	const ll N=2000000+10,M=200+10;
	char S[N],A[N],B[N],C[N],tmp[N];
	ll n,b[M],ans=0;
	void get(ll l,ll r,char *g)
	{
		ll pos=0;
		for(ll i=l;i<=r;i++)
			g[++pos]=S[i];
		g[++pos]='\0';
		return;
	}
	ll count(char *g)
	{
		ll len=strlen(g+1),cnt=0;
		memset(b,0,sizeof(b));
		for(ll i=1;i<=len;i++) b[g[i]]++;
		for(ll i='a';i<='z';i++)
			if(b[i]%2==1)　cnt++;
		return cnt;
	}
	ll equal(char *g,char *h)
	{
		ll len=strlen(g+1);
		if(len!=strlen(h+1)) return 0;
		//cout<<g+1<<" "<<h+1<<endl;
		for(ll i=1;i<=len;i++)
			if(g[i]!=h[i]) return 0;
		return 1;
	}
	void cheat()
	{
		for(ll a=1;a<=n;a++)
		{
			for(ll b=1;b<=n;b++)
			{
				if(a+b>=n)　break;
				get(1,a,A); get(a+1,a+b,B);
				get(a+b+1,n,C);//if(a==1&&b==2) cout<<"iaurftus "<<count(A)<<" "<<count(C)<<endl;
				if(count(A)<=count(C)) ans++;
				//cout<<A+1<<" "<<B+1<<" "<<C+1<<endl;
				for(ll i=a+b;i<=n;i+=(a+b))
				{
					if(i+a+b>=n)　break;
					get(i+1,i+a,tmp);
					if(equal(tmp,A)==0)　break;
					//cout<<tmp+1<<" "<<A+1<<" A->"<<i+1<<" "<<i+a<<endl;
					get(i+a+1,i+a+b,tmp);
					if(equal(tmp,B)==0)　break;
					//cout<<tmp+1<<" "<<B+1<<" B->"<<i+1<<" "<<i+a<<endl;
					get(i+a+b+1,n,C);
					
					if(count(A)>count(C))　continue;
					//cout<<A+1<<" "<<B+1<<" "<<C+1<<" "<<i/(a+b)<<endl;
					ans++;　
					//cout<<endl;
				}
			}
		}
	}
	void main()
	{
		ll T;
		cin>>T;
		while(T--)
		{　
			cin>>(S+1);
			n=strlen(S+1);
			ans=0;
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
/*
1
kkkkkkk
*/
