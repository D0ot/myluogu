#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 1005
using namespace std;
int n,m,k,x,y,l,sum,ans;
int fa[N];
struct Edge
{
    int u,v,w;
    bool operator <(Edge a) const    //重置运算符的函数写在里面的话必须加const
    {
        return w<a.w;
    }
}edge[N*10];
/*bool operator <(Edge a,Edge b)    //重置运算符的函数写在外面的话不能加const
{
        return a.w<b.w;
}*/
int find(int x)
{
    return fa[x]==x?fa[x]:fa[x]=find(fa[x]);
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
    }
    sort(edge+1,edge+m+1);    //按代价升序排列 
    for(int i=1;i<=m;i++)
    {
        int fx=find(edge[i].u),fy=find(edge[i].v);
        if(fx!=fy)        //如果这两个点不在同一棵树中 
        {
            fa[fx]=fy;
            sum++;        //连一条边，让它们合并成为一棵树 
            ans+=edge[i].w;        //加上合并的代价 
        }
        if(sum==n-k)        //已经连好了k棵树 
        {
            printf("%d",ans);
            return 0;
        }
    }
    puts("No Answer");    //不可能连好 
    return 0;
}