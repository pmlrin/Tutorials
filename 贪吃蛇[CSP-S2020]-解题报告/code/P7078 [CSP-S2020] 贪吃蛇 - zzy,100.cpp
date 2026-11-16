#include<bits/stdc++.h>
#define int long long 
#define mod 100000000
//#define qb.push_back(l-r); qb.push_back(10000000*((l/10000000)-(r/10000000))+(l%10000000));
using namespace std;
const int N=3e6+5;
const unsigned int inf=2147483642147483640;
int t,n,m;
int snake[N];
//int q1[N],q2[N];
deque<int> qa,qb;
/*
void ms()
{
	memset(q1,0,sizeof(q1));
	memset(q2,0,sizeof(q2));
}*/
int ans,turn;

void debug()
{
		int k1=qa.size(),k2=qb.size();
		cout<<"qa:";
		for(int i=1;i<=k1;++i)
		{
			int yzz=qa.front();
			cout<<yzz<<" ";
			qa.pop_front();
			qa.push_back(yzz);
		}cout<<endl;
		
		cout<<"qb:";
		for(int i=1;i<=k2;++i)
		{
			int yzz=qb.front();
			cout<<yzz<<" ";
			qb.pop_front();
			qb.push_back(yzz);
		}
		cout<<endl;
}

void work()
{turn=0;
//	ms();
	qa.clear();
	qb.clear();
	
	for(int i=1;i<=n;++i)
	{
		qa.push_front(snake[i]);
	}
	
//	int head=1,tail=n;
//	int head2=0,tail2=1;
//	while(1)
//	{
/*		int maxn=max(q1[head],q2[head2]);
		if(q1[head]>q2[head])
		{
			head++;		
		}
		else
		{
			head2++;
		}
		int minn=min(q1[tail],q2[tail2]);
		if(q1[tail]<q2[tail])
		{
			tail++;
		}
		else
		{
			tail2++;
		}
		deque<int>q;*/
		
				
//		tail2++;
		
//	}
	ans=n;
	
	while(1)
	{
//		cout<<qa.size()<<" "<<qb.size()<<endl;
		
		if(qa.size()+qb.size()<=2)
		{
			ans=1;
			return;
		}
		
	//	debug();
		
		if(ans==1) return;
		
		int l1,l2=0,r1,r2;
		l1=qa.front();
		
		if(!qb.empty())
		l2=qb.front(); 
	
		
		int l,r;
		l=max(l1,l2);
		
		if(l1>l2&&!qa.empty())
		{
			qa.pop_front();
		}
		else
		{
			qb.pop_front();
		}
		
		r=qa.back();//r1
//		r2=qb.back();
	
//		r=min(r1,r2);
		
///		if(r1<r2&&!qa.empty())
//		{
			qa.pop_back();
//		}
		
//		else
//		{
//			qb.pop_tail();
//		}
		
		int r3,r4,k;
//		cout<<" sss"<<qa.size()<<"sss ";
		if(!qa.empty())
		k=qa.back();//r3
		else
		k=qb.back();
//		r4=qb.back();
//	
//		k=min(r3,r4);
		
/*		if(r1<lr&&!qa.empty())
		{
			qa.pop_tail();
		}
		
		else
		{
			qb.pop_tail();
		}*/
//		cout<<l<<" "<<r<<" "<<k<<endl;
		
		if((10000000*((l/10000000)-(r/10000000))+(l%10000000))>k)
		{//cout<<"k";
		//	qb.push_back(l-r);
			qb.push_back(mod*((l/mod)-(r/mod))+(l%mod));
		}
		
		
		
/*		if(qa.tail()<qb.tail())
		{
			if(l-r>qa.tail())
			{
				qb.push_back(l-r);
			}	
		}*/
		--ans;
		
		if((10000000*((l/10000000)-(r/10000000))+(l%10000000))<k||qa.empty())
		{
		//	qb.push_back(l-r);
			qb.push_back(mod*((l/mod)-(r/mod))+(l%mod));
			int an=ans;
			
			turn=1;
	//		printf("\nyz ac black questions\n");
			while(1)
			{
				
		//		debug();
				
				if(qa.size()+qb.size()<=1)
				{//system("pause");
					turn++;
					break;
				}
				
				int l1=0,l2=0,r1=inf,r2=inf;
				if(!qa.empty())
			
				l1=qa.front();
				l2=qb.front(); 
		
		
				int l,r;
				l=max(l1,l2);
			
				if(l1>l2&&!qa.empty())
				{
					qa.pop_front();
				}
				else
				{
					qb.pop_front();
				}
				
				if(!qa.empty())
				r1=qa.back();//r r1
				if(!qb.empty())
				r2=qb.back();
		
				r=min(r1,r2);
			
				if(r1<r2&&!qa.empty())
				{
					qa.pop_back();
				}
		
				else
				{
					qb.pop_back();
				}
		
				int r3=inf,r4=inf,k;
				
				if(!qa.empty())
				r3=qa.back();//k r3
				if(!qb.empty())
				r4=qb.back();
		
				k=min(r3,r4);
				
				if(k==inf) k=0;
				
	//			cout<<"l: "<<l<<" r: "<<r<<" k: "<<k<<endl;
				
				if((10000000*((l/10000000)-(r/10000000))+(l%10000000))>k||an==2)
				{
					break;
				}
				else
				{
					//qb.push_back(l-r);	
					qb.push_back(mod*((l/mod)-(r/mod))+(l%mod));
				}
				
				++turn;
//				an--;
			}	
		//	cout<<"turn: "<<turn<<endl;
			if(turn%2==(114515%2))
			{
				ans++;
		
		//		cout<<"yz ak ioi \n";
			}
			return;	
		}
		
	}
	
	return;
}

#undef int

int main()
{
#define int long long 

//	freopen("snakes3.in","r",stdin);

	scanf("%lld",&t);
	--t;
	
	scanf("%lld",&n);
	
	for(int i=1;i<=n;++i)
	{
		scanf("%lld",&snake[i]);
		snake[i]=snake[i]*mod+i;
	}
	
	work();
	printf("%lld\n",ans);


while(t--)
{	
	scanf("%lld",&m);
	
	for(int i=1;i<=m;++i)
	{
		int a,b;
		scanf("%lld%lld",&a,&b);
		snake[a]=(long long)b*mod+a;
		
	}
	work();
	printf("%lld\n",ans);
}
	return 0;
} 
/*
1
5
7 10 24 48 50

*/
/*

1
15
0 1 2 2 2 2 3 3 4 5 5 6 7 8 8

8

*/
