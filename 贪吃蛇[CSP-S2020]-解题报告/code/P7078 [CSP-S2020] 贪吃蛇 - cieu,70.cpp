#include<bits/stdc++.h>
using namespace std;
namespace _yz
{
	#define mp make_pair
	#define fir first
	#define sec second
	typedef long long ll;
	typedef pair<ll,ll> Snk;
	const ll N=1000000+10;
	ll hp[N],n,ans=0;
	set<Snk>s;
	
	bool operator>(Snk a,Snk b)
	{
		if(a.fir==b.fir)
			return a.sec>b.sec;
		return a.fir>b.fir;
	}
	void init()
	{
		s.clear();
		for(ll i=1;i<=n;i++)
			s.insert(mp(hp[i],i));
		ans=0;
	}
	void solve()
	{
		set<Snk>::iterator it;
		ll cnt=0;//记录第二阶段递归层数 
		while(!s.empty())
		{
			if(s.size()<=2)
			{
				if(!cnt) {ans=1;return;}
				ans=cnt-((cnt-s.size())%2)+1;
				return;//偶数可以吃 
			}
			it=s.end();it--;
			Snk G=*it;s.erase(it);
			it=s.begin();
			Snk L=*it;s.erase(it);
			Snk T=mp(G.fir-L.fir,G.sec); 
			s.insert(T);
			it=s.begin();
			if(it->sec!=T.sec)
			{
				if(cnt){
					ans=cnt+((cnt-s.size())%2);
					return;//奇数可以吃 
				}
			}
			else if(!cnt) cnt=s.size();
		}
	}
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
					scanf("%lld",hp+i);
			}
			else
			{
				scanf("%lld",&k);
				for(ll i=1;i<=k;i++)
				{
					scanf("%lld%lld",&t1,&t2);
					hp[t1]=t2;
				}
			}
			init();
			solve();
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
