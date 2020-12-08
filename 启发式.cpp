//启发式A* 
#include<stdio.h>
#include<iostream>
#include<queue>
#include<vector>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<map>
using namespace std;
const int MAXN = 362880+5;
string end="123456789ABCDEF0";
int t=0;
map<string,int>v;
map<string,string>fa;
int to[16][5]={
	2,1,4,0,0,
	3,0,2,5,0,
	3,1,3,6,0,
	2,2,7,0,0,
	3,0,5,8,0,
	4,1,4,6,9,
	4,2,5,7,10,
	3,3,6,11,0,
	3,4,9,12,0,
	4,5,8,10,13,
	4,6,9,11,14,
	3,7,10,15,0,
	2,8,13,0,0,
	3,9,12,14,0,
	3,10,13,15,0,
	2,11,14,0,0
};
struct node{
	int h,l;
	string k;
	bool operator < (const node& b) const 
	{
		return h>b.h;
	}
};
priority_queue<node>q;
string ans[2005];
int f(string x)
{
	int res=0;
	for(int i=0;i<16;i++)
	if(x[i]!=end[i])
	res++;
	return res;
}
void bfs(string x)
{
	node no;
	no.k=x;no.h=0;no.l=1;
	for(int i=0;i<16;i++)
	if(x[i]!=end[i])
	no.h++;
	q.push(no);
	while(!q.empty())
	{
		no=q.top();q.pop();
		x=no.k;
		//cout<<x<<endl;
		int l=no.l;
		if(x==end)
		{
			t=no.l;
			for(int i=t-1;i>=0;i--)
			{
				ans[i]=x;
				//cout<<ans[i]<<endl;
				x=fa[x];
			}
			return;
		}
		int pos;
		for(pos=0;x[pos]!='0';pos++);
		for(int i=1;i<=to[pos][0];i++)
		{
			//x[pos]^=x[to[pos][i]]^=x[pos]^=x[to[pos][i]];
			//cout<<x<<endl;
			string tmp=x;
			char c=x[pos];x[pos]=x[to[pos][i]];x[to[pos][i]]=c;
			//cout<<x<<endl;
			if(v[x]==0)
			{
				v[x]=1;fa[x]=tmp;
				no.k=x;no.h=f(x);no.l=l+1;
				q.push(no);
			}
			c=x[pos];x[pos]=x[to[pos][i]];x[to[pos][i]]=c;
			//x[pos]^=x[to[pos][i]]^=x[pos]^=x[to[pos][i]];
		}
	}
}
void print(string x)
{
	for(int i=0;i<16;i++)
	{
		printf("%c\t",x[i]);
		if(i%4==3)
		printf("\n");
	}
}
bool pd(string x)
{
	int res=0;
	for(int i=0;i<16;i++)
	{
		if(x[i]=='0')
		{
			res+=6-i%4-i/4;
		}
		for(int j=0;j<i;j++)
		if(x[j]>x[i])
		res++;
	}
	if(1&res) return 1;
	else return 0;
}
int main()
{
	int flg;
	string x="123456789ABCDEF0";
	printf("输入0随机生成，输入1手动输入（0-F排列）\n");
	scanf("%d",&flg);
	if(flg)
	{
		cin>>x;
	}
	else
	while(flg==0)
	{
		vector<char>vec;
		for(char c='0';c<='9';c++)
		vec.push_back(c);
		for(char c='A';c<='F';c++)
		vec.push_back(c);
		srand(time(NULL));
		int k=rand();
		for(int i=0;i<16;i++)
		{
			int p=k%(16-i);
			x[i]=vec[p];
			vec.erase(vec.begin()+p);
			k=rand();
		}
		if(!pd(x))
		{
			flg=0;
		}
		else
		{
			print(x);
			break;
		}
	}
	if(!pd(x))
	{
		printf("无解\n");
		return 0;
	}
	fa[x]="end";
	bfs(x);
	printf("总步数为%d\n",t);
	printf("输入0结束，输入1输出路径。\n");
	scanf("%d",&flg);
	if(flg)
	{
		for(int i=0;i<t;i++)
		{
			printf("****第%d步****\n",i+1);
			print(ans[i]);
		}
	}
}
