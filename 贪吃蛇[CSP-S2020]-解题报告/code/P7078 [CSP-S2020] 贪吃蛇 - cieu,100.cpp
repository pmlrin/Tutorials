#include<bits/stdc++.h>
using namespace std;
namespace _yz
{
	typedef long long ll;
	const ll N=1000000+10;
	struct Snakes
	{
		ll id,hp;
		bool operator>(Snakes b)
		{
			if(this->hp==b.hp) return this->id>b.id;
			return this->hp>b.hp;
		}
		bool operator<(Snakes b)
		{
			if(this->hp==b.hp) return this->id<b.id;
			return this->hp<b.hp;
		}
		Snakes operator-(Snakes b)
		{
			Snakes _t=*this;
			_t.hp=this->hp-b.hp;
			return _t;
		}
	}s[N];
	ll n,ans=0;
	deque<Snakes>q1,q2;
	void init()
	{
		q1.clear();q2.clear();
		for(ll i=1;i<=n;i++)
			q1.push_front(s[i]);
	}
	Snakes getF() 
	{
		Snakes S;
		if(q2.empty() || (!q1.empty()&&q1.front()>q2.front()))
		     S=q1.front(),q1.pop_front();
		else S=q2.front(),q2.pop_front(); 
		return S;
	}
	Snakes getB()
	{
		Snakes S=q1.back();
		q1.pop_back();
		return S;
	}
	Snakes Check()
	{
		Snakes S;
		if(!q1.empty()) S=q1.back();
		if(!q2.empty()&&S>q2.back()) S=q2.back();
		return S; 
	}
	void solve()
	{
		while(true)
		{
			ll cnt=0;
			if(q1.size()+q2.size()<=2) {ans=1;return;}
			Snakes L=getB(),G=getF();
			Snakes T=(G-L);
			if(T<q1.back() || q1.empty())
			{
				ans=q1.size()+q2.size()+2; 
				while(true)
				{
					cnt++;
					if(q1.size()+q2.size()+1<=2){ans-=(cnt%2==0);return;}
					G=getF();T=(G-T);
					if(T>Check()){ans-=(cnt%2==0);return;}
				}
			}else q2.push_back(T);
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
			init();
			solve();
			printf("%lld\n",ans);
		}
		return;
	}
}
int main()
{
	_yz::yzmain();
	return 0;
}
