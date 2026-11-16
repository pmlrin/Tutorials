#include<bits/stdc++.h>
using namespace std;
namespace _yz
{
	typedef int ll;
	const ll N=1200000+10; 
	char S[N];
	ll n,ans=0,rpt;
	void init()
	{
		cin>>(S+1);　
		n=strlen(S+1); ans=0;
	}　
	ll odd(ll C)//统计 AB 为奇数时的合法 C 数 
	{
		if(C%2)
		{
			if(rpt%2==0) return rpt/2;
			else return rpt/2+1;
		}
		else　
		{
			if(rpt%2==0) return rpt/2;
			else return rpt/2;
		}
	}
	void cheat()
	{
		ll C,rep;
		for(ll AB=2;AB<=n-1;AB++)
		{
			C=n-AB;　
			if(C%AB==0) rpt=C/AB;　
			else rpt=C/AB+1;
			if(AB%2) ans+=((AB-1)/2)*rpt+((AB-1)-(AB-1)/2)*odd(C);
			else if(C%2) ans+=(AB-1)*rpt;　
			else ans+=((AB-1)/2)*rpt;
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
