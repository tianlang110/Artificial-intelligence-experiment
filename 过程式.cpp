//过程式 
#include<stdio.h>
#include<iostream>
#include<queue>
#include<stdlib.h>
#include<time.h>
using namespace std;
int style[9]={1,2,3,6,7,4,5,8,0};
int local;
int i,j;
int number=0;
void judge()//判断空格位置
{
    for(i=0;i<9;i++)
    {
        if(style[i]==0)
        {
            local=i;
            return;
        }
    }
}
void exchange(int x,int y)//交换两个数
{
    int temp;
    temp=style[x];
    style[x]=style[y];
    style[y]=temp;
    local=y;
}
void step1()
{
    int arrayStep11[5]={3,0,1,2,5};
    int arrayStep12[6]={6,7,8,5,2,1};
    if((style[2]!=0)&&style[2]!=1)
        return;
    else
    {
        if(local==2)
        {
            if(style[1]==1)
                exchange(2,5);
            else
                exchange(2,1);
            return;
        }
        else
        {
            if(local==4)
            {
                exchange(4,1);
                i=2;
                while(local!=5)
                {
                    exchange(arrayStep11[i],arrayStep11[i+1]);
                    i++;
                }
                return;
            }
            for(i=0;i<3;i++)
            {
                if(arrayStep11[i]==local)
                {
                    while(local!=5)
                    {
                        exchange(arrayStep11[i],arrayStep11[i+1]);
                        i++;
                    }
                    return;
                }
            }
            for(i=0;i<4;i++)
            {
                if(arrayStep12[i]==local)
                {
                    while(local!=1)
                    {
                        exchange(arrayStep12[i],arrayStep12[i+1]);
                        i++;
                    }
                    return;
                }
            }
        }
    }
    return;
}
void step2()
{
    int arrayStep2[8]={0,3,6,7,8,5,4,1};
    queue<int>q;
    for(i=0;i<8;i++)
    {
        q.push(style[arrayStep2[i]]);
    }
    while(q.front()!=1)
    {
        int tem=q.front();
        q.pop();q.push(tem);
    }
    for(i=0;i<8;i++)
    {
        style[arrayStep2[i]]=q.front();q.pop();
    }
}
void step3()
{
    int arrayStep3[8]={1,4,3,6,7,8,5,2};
    queue<int>q;
    for(i=0;i<8;i++)
    {
        q.push(style[arrayStep3[i]]);
    }
    while(q.front()!=2)
    {
        int tem=q.front();
        q.pop();q.push(tem);
    }
    for(i=0;i<8;i++)
    {
        style[arrayStep3[i]]=q.front();q.pop();
    }
}
void step4()
{
    int arrayStep4[5]={4,6,7,8,5};
    queue<int>q;
    for(i=0;i<5;i++)
    {
        if(style[arrayStep4[i]]!=0)
        q.push(style[arrayStep4[i]]);
    }
    if(style[3]!=0)
    q.push(style[3]);
    while(q.front()!=3)
    {
        int tem=q.front();
        q.pop();q.push(tem);
    }
    style[3]=0;
    for(i=0;i<5;i++)
    {
        style[arrayStep4[i]]=q.front();q.pop();
    }
}
void step5()
{
    style[4]=style[5];
    style[5]=style[2];
    style[2]=3;
}
void step6()
{
    int arrayStep6[6]={5,4,3,6,7,8};
    queue<int>q;
    for(i=0;i<6;i++)
    {
        q.push(style[arrayStep6[i]]);
    }
    while(q.front()!=4)
    {
        int tem=q.front();
        q.pop();q.push(tem);
    }
    for(i=0;i<6;i++)
    {
        style[arrayStep6[i]]=q.front();q.pop();
    }
    return;
}
void step7()
{
    int arrayStep7[3]={4,6,7};
    queue<int>q;
    for(i=0;i<3;i++)
    {
        if(style[arrayStep7[i]]!=0)
        q.push(style[arrayStep7[i]]);
    }
    if(style[3]!=0)
    q.push(style[3]);
    while(q.front()!=5)
    {
        int tem=q.front();
        q.pop();q.push(tem);
    }
    style[3]=0;
    for(i=0;i<3;i++)
    {
        style[arrayStep7[i]]=q.front();q.pop();
    }
}
void step8()
{
    style[4]=style[7];
    style[7]=style[8];
    style[8]=5;
}
void step9()
{
    int arrayStep9[4]={3,6,7,4};
    queue<int>q;
    for(i=0;i<4;i++)
    {
        if(style[arrayStep9[i]]!=0)
        q.push(style[arrayStep9[i]]);
    }
    while(q.front()!=6)
    {
        int tem=q.front();
        q.pop();q.push(tem);
    }
    style[4]=0;
    arrayStep9[0]=7;
    arrayStep9[1]=3;
    arrayStep9[2]=6;
    for(i=0;i<3;i++)
    {
        style[arrayStep9[i]]=q.front();q.pop();
    }
}
void print()
{
    for(j=0;j<9;j++)
    {
        if(style[j]==0)
            printf(" \t");
        else
            printf("%d\t",style[j]);
        if((j+1)%3==0)
            printf("\n");
    }
    printf("************ %d ***********\n",++number);
}
int main()
{
	int flg;
	printf("输入0随机生成，输入1手动输入（0-8排列）\n");
	scanf("%d",&flg);
	if(flg)
	{
		printf("请输入数码\n");
	    for(i=0;i<9;i++)
	    scanf("%d",&style[i]);
	}
    else
    {
    	vector<int>vec;
    	for(int i=0;i<9;i++)
    	vec.push_back(i);
    	srand(time(NULL));
		int k=rand();
		for(int i=0;i<9;i++)
		{
			int p=k%(9-i);
			style[i]=vec[p];
			vec.erase(vec.begin()+p);
			k=rand();
		}
		print();
	}
    judge();
    step1();print();
    step2();print();
    step3();print();
    if(style[2]==0)
    {
        exchange(2,5);
    }
    if(style[2]!=3)
    {
        step4();print();
        step5();print();
    }
    step6();print();
    if(style[8]==0)
    {
        exchange(8,7);
    }
    if(style[8]!=5)
    {
        step7();print();
        step8();print();
    }
    step9();print();
    if(!((style[3]==8)&&(style[6]==7)))
    printf("问题无解\n");
    else
    printf("问题解决完毕\n");
}
