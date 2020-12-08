//DFS 
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
int v[MAXN],l[MAXN],ans[MAXN],t=99999999;
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
void dfs(int k,int len)
{
	if(len>40) return;
	//printf("%d %d\n",k,len);
	if(k==end)
	{
		//printf("%d\n",len);
		if(len<t)
		{
			t=len;
			for(int i=0;i<len;i++)
			ans[i]=l[i];
		}
		return;
	}
	if(v[k]<=len)
	return;
	v[k]=len;
	int x[10];
	nkt(x,k);
	int pos;
	for(pos=0;x[pos]!=9;pos++);
	for(int i=1;i<=to[pos][0];i++)
	{
		//swap(x+pos,x+to[pos][i]);
		x[pos]^=x[to[pos][i]]^=x[pos]^=x[to[pos][i]];
		l[len]=kt(x);
		dfs(l[len],len+1);
		x[pos]^=x[to[pos][i]]^=x[pos]^=x[to[pos][i]];
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
	v[i]=999999;
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
	l[0]=kt(x);
	dfs(l[0],1);
	if(t==99999999)
	{
		printf("无解\n");
		return 0;
	}
	else
	printf("总步数为%d\n",t);
	for(int i=0;i<t;i++)
	{
		printf("第%d步\n",i+1);
		print(ans[i]);
	}
}
