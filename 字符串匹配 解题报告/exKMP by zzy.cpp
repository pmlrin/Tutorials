#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e7+15;

char s[N],p[N];
int sl,pl;
int z[N],ext[N];

void getz()
{
	z[0]=pl;
	int now=0,p0=1;
	while(now+1<pl&&p[now]==p[now+1]) ++now;
	z[1]=now;
	for(int i=2;i<pl;++i)
	{
		if(i+z[i-p0]<p0+z[p0])
		{
			z[i]=z[i-p0];
		}
		else
		{
			now=p0+z[p0]-i;
			now=max(now,0ll);	
			while(now+i<pl&&p[now]==p[now+i]) ++now;
			z[i]=now;
			p0=i;
		}
	}
}

void exkmp()
{
	getz();
	
	int now=0,p0=0;
	
	while(now<pl&&now<sl&&p[now]==s[now])++now;
	
	ext[0]=now;
	
	for(int i=1;i<sl;++i)
	{
		if(i+z[i-p0]<p0+ext[p0])
		{
			ext[i]=z[i-p0];
		}
		else
		{
			now=p0+ext[p0]-i;
			now=max(now,0ll);
			while(now<pl&&now+i<sl&&p[now]==s[now+i]) ++now;
			ext[i]=now;
			p0=i;
		}
	}
	
}

#undef int
int main()
{
#define int long long

	scanf("%s",&s);
	scanf("%s",&p);
	sl=strlen(s);
	pl=strlen(p);
	exkmp();
	
	int wz=0,ws=0;
	
	for(int i=0;i<pl;++i)
	{
		wz=wz^((i+1)*(z[i]+1));
	}
	for(int i=0;i<sl;++i)
	{
		ws=ws^((i+1)*(ext[i]+1));
	}
	printf("%lld\n%lld",wz,ws);
	
	return 0;
}
