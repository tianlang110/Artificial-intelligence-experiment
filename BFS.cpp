//BFS 
#include<stdio.h>
#include<iostream>
#include<queue>
#include<vector>
#include<string.h>
#include<stdlib.h>
#include<time.h>
using namespace std;
const int MAXN = 362880+5;
int f[10];
int kx[MAXN][10];
int jc(int x)
{
	if(x==0)
	return 1;
	if(f[x]!=0)
	return f[x];
	else
	return f[x]=x*jc(x-1);
}
int kt(int x[])
{
	int res=1,len=9;
	for(int i=0;i<len;i++)
	{
		int tmp=0;
		for(int j=i+1;j<len;j++)
		{
			if(x[i]>x[j]) tmp++;
		}
		res+=tmp*jc(len-i-1);
	}
	return res;
}
void nkt(int x[],int k)
{
	k--;
	int pos=k;
	if(kx[pos][0]!=0)
	{
		for(int i=0;i<9;i++)
		x[i]=kx[pos][i+1];
		return;
	}
	kx[k][0]=1;
	vector<int>vec;
	for(int i=1;i<=9;i++) vec.push_back(i);
	for(int i=1;i<=9;i++)
	{
		int t=k/jc(9-i);
		k%=jc(9-i);
		kx[pos][i]=vec[t];
		vec.erase(vec.begin()+t);
	}
	for(int i=0;i<9;i++)
	x[i]=kx[pos][i+1];
}
int v[MAXN],l[MAXN],ans[MAXN],t=0,fa[MAXN];
int end;
int to[9][5]={
	2,1,3,0,0,
	3,0,2,4,0,
	2,1,5,0,0,
	3,0,4,6,0,
	4,1,3,5,7,
	3,2,4,8,0,
	2,3,7,0,0,
	3,4,6,8,0,
	2,5,7,0,0
};
queue<int>q;
void bfs(int k)
{
	q.push(k);
	int x[10];
	while(!q.empty())
	{
		k=q.front();q.pop();
		if(k==end)
		{
			while(k!=0)
			{
				ans[t++]=k;
				k=fa[k];
			}
			break;
		}
		nkt(x,k);
		int pos;
		for(pos=0;x[pos]!=9;pos++);
		for(int i=1;i<=to[pos][0];i++)
		{
			x[pos]^=x[to[pos][i]]^=x[pos]^=x[to[pos][i]];
			int tmp=kt(x);
			if(v[tmp]==0)
			{
				v[tmp]=1;
				fa[tmp]=k;
				q.push(tmp);
			}
			x[pos]^=x[to[pos][i]]^=x[pos]^=x[to[pos][i]];
		}
	}
}
void print(int k)
{
	int x[10];
	nkt(x,k);
	for(int i=0;i<9;i++)
	{
		printf("%d\t",x[i]);
		if(i%3==2)
		printf("\n");
	}
}
int main()
{
	for(int i=0;i<MAXN;i++)
	v[i]=0;
	int x[10]={1,2,3,8,9,4,7,6,5},flg;
	end=kt(x);
	printf("输入0随机生成，输入1手动输入（1-9排列）\n");
	scanf("%d",&flg);
	if(flg)
	{
		for(int i=0;i<9;i++)
		scanf("%d",&x[i]);
	}
	else
	{
		srand(time(NULL));
		int k=rand()+1;
		nkt(x,k);
		print(k);
	}
	int beg=kt(x);
	v[beg]=1;
	bfs(beg);
	if(t==0)
	{
		printf("无解\n");
		return 0;
	}
	else
	printf("总步数为%d\n",t);
	for(int i=t-1;i>=0;i--)
	{
		printf("第%d步\n",t-i);
		print(ans[i]);
	}
}
