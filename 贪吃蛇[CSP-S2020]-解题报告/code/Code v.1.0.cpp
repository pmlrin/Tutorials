#include <deque> 
//或者使用 <bits/stdc++.h> 
using namespace std;
deque<int>q; //定义


q.front(); //返回队首元素。 
q.back(); //返回队尾元素。 
q.pop_front(); //返回队首元素。 
q.pop_back(); //返回队尾元素。 
q.push_front(x); //从队首压入元素 x。 
q.push_back(x); //从队尾压入元素 x。 
q.size(); //返回队列大小。 
q.clear(); //清空队列。 
q.empty(); //如果队列为空，返回 1。


#include <set> 
//或者使用 <bits/stdc++.h> 
using namespace std; 
set<int>q; //定义
multiset<int>q; //定义


s.begin() //返回指向第一个元素的迭代器 
s.clear(); // 清除所有元素 O(n)
s.count(x); //返回某个值元素的个数 O(log n)
s.empty(); //如果集合为空，返回 true 
s.end(); //返回指向最后一个元素之后的迭代器 
s.find(x); //返回一个指向被查找到元素的迭代器 O(log n) 
s.insert(x); //在集合中插入元素 
s.lower_bound(x); //返回指向大于等于某值的第一个元素的迭代器 
s.upper_bound(x); //返回大于某个值元素的迭代器，和上一个都是O(log n)
s.size(); //集合中元素的数目


#include <utility> 
//或者使用 <bits/stdc++.h> 
using namespace std; 
pair<int,int>p; //定义


p=make_pair(x1,x2); //这个函数可生成一个 pair 
a=p.first; //返回第一个值 
b=p.second; //返回第二个值


struct Snakes{ 
	ll id,hp; 
	Snakes operator-(Snakes b){//内部定义 
		Snakes _t=*this; 
		_t.hp=this->hp-b.hp; 
		return _t; 
	} 
}; 
bool operator<(Snakes a,Snakes b){//外部定义 
	if(a.hp==b.hp) return a.id<b.id; 
	return a.hp<b.hp; 
}


void _20pts() 
{ 
	if(s[3].hp-s[1].hp>=s[2].hp) ans=1;
	else ans=3;
	return; 
}


if(q1.size()+q2.size()<=2) {ans=1;return;} //特判 
Snakes L=getB(),G=getF(); //Get Back/Front
Snakes T=(G-L); 
if(T<q1.back() || q1.empty()) Stage_2(); 
else q2.push_back(T);


if(T<q1.back() || q1.empty()){//此时 T == L
 	ans=q1.size()+q2.size()+2;//答案不必动态统计。
 	while(true){ 
		cnt++;
 		if(q1.size()+q2.size()+1<=2){
			ans-=(cnt%2==0);//奇偶性
			return;
		} 
		G=getF();T=(G-T); 
		if(T>Check()){ans-=(cnt%2==0);return;} 
	}//Check 判断是不是最弱蛇（两个队列） 
}
