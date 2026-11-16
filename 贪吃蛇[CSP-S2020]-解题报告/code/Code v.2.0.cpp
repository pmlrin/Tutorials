s.erase(iterator) //删除所指位置 
s.erase(first,second); // 删除 [first,second) 之间的数
s.erase(x); //删除值为 x 的数

set<int>::iterator it1 = s.begin(); //begin() 返回第一个元素地址
while (it1 != s.end()) //end() 返回最后一个元素的下一个地址
{ 
    cout << *it1 << " ";
    ++it1; 
}

set<int>::reverse_iterator it1 = s.rbegin(); //反向迭代器 
while (it1 != s.rend()) 
{ 
    cout << *it1 << " "; 
    ++it1; 
}
cout << endl;

void _20pts() 
{ 
	if(s[3].hp-s[1].hp>=s[2].hp) ans=1;
	else ans=3; //为什么比较要加等号？
	return; 
} //两行代码得 20 分，高效骗分。


void solve40(Snakes tmp[]) 
{ 
	ans=n; 
	Snakes s[20]; 
	for(int i=1;i<=n;i++) 
		s[i]=tmp[i]; //复制数组
	sort(s+1,s+1+ans,cmp); //无脑排序
	while(true) 
	{ 
		if(s[ans].hp-s[1].hp>=s[2].hp) //判断这条蛇能不能吃
			s[1].hp=s[ans].hp-s[1].hp,s[1].id=s[ans].id,ans--; 
		else break; //不能吃就跳出循环
		sort(s+1,s+1+ans,cmp); 
	} 
} 

