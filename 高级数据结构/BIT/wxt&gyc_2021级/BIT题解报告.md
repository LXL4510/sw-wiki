# BIT题解报告

## 【模板】树状数组 1

### 简述题意

你有一个序列，需要进行在线单点修改和区间查询最大值。

### 分析

树状数组模板题，树状数组可以维护从 $1$ 号点到任意点的区间和，区间和明显具有差分性质，所以任意一段区间的问题可以转化为从 $1$ 号点出发的区间问题，套模板即可。

### 代码实现

```cpp
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
inline int read();
int a[500005];
int tree[500005];
int lowbit(int x){
    return x&-x;
}
int n,m;
int ques(int x){
    int ans=0;
    while(x>0){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}
void change(int x,int k){
    while(x<=n){
        tree[x]+=k;
        x+=lowbit(x);
    }
    return ;
}
signed main(){
    #ifdef ONLINE_JUDGE=LUOGU
    #else
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    #endif
    n=read();m=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        a[i]+=a[i-1];
    }
    for(int i=1;i<=n;i++){
        tree[i]=a[i]-a[i-lowbit(i)];
    }
    for(int i=1;i<=m;i++){
        int op=read();
        int x=read();
        int y=read();
        if(op==1){
            change(x,y);
        }else{
            printf("%lld\n",ques(y)-ques(x-1));
        }
    }
    return 0;
}
inline int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){
        c=='-'?f=-1:1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+(c^48);
        c=getchar();
    }
    return f*x;
}
/*
Anything about this program:
Type:

Description:

Example:
    1:
        In:

        Out:
More:

*/
```

## [CQOI2006]简单题

### 题目简述

有一个 $01$ 串，初始全部为 $0$ ，你需要维护的操作是反转某一个区间（ $0$ 变成 $1$ ，反之亦然），并且在线查询某个下标位置的元素状态。

### 题目分析

#### 大致思路

很明显，目前状态与他被反转的次数有关，翻转偶数次则不变，奇数次则改变，于是维护反转次数即可。

但是这个问题与我们的前面一道题不一样，是区间修改，单点查询。如何转化呢？很容易注意到前面用到了前缀和，这里运用差分即可。

#### 差分

为了处理一个区间加上同一个数的操作，考虑不变的量其实是区间内相邻元素的差，所以维护相邻元素差即可。

具体的，对于原来的序列 $A$，考虑生成新的序列 $B$，$B_i=A_i-A_{i-1}$。

实际上在区间 $[l,r)$ 加上一个数 $k$，实际上是将 $B_r$ 减去 $k$ ，$B_l$ 加上 $k$。

差分实际上是前缀和的逆运算。

### 代码实现

```cpp
#include <iostream>
#include <cstdio>
inline int read();
int n;
int tree[100005];
int lowbit(int x){
    return x&(-x);
}
void add(int x,int y){
    while(x<=n){
        tree[x]+=y;
        x+=lowbit(x);
    }
    return ;
}
int query(int x){
    int ans=0;
    while(x>0){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}
int main(){
    #ifdef ONLINE_JUDGE
    #else
    freopen("easy.in","r",stdin);
    freopen("easy.out","w",stdout);
    #endif
    n=read();
    int m=read();
    for(int i=1;i<=m;i++){
        int op=read();
        switch(op){
            case 1:{
                int l=read(),r;
                r=read();
                add(r+1,-1);
                add(l,1);
                break;
            }
            case 2:{
                int t=read();
                printf("%d\n",query(t)%2);
                break;
            }
        }
    }
    return 0;
}
inline int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){
        c=='-'?f=-1:1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+(c^48);
        c=getchar();
    }
    return f*x;
}
/*
Anything about this program:
Type:

Description:

Example:
    1:
        In:

        Out:
More:

*/
```

## 机房摸鱼问题

### 问题简述

有一颗有根树，$dis_{i,j}$ 表示 $i$ 和 $j$ 的简单距离。 $fa_i$ 表示 $i$ 的所有父节点的集合。

所以 $dp_i=\min(dp_j+q_i)$  $j$ 满足 $dis_{i,j}\leq p_i ~\&~j \in fa_i $ 。

定义 $dp_1=0$。

求所有的 $dp_i~(i \in[1,n])$ 。

### 问题分析

很明显我们这个是一个树状DP的定义，树状DP实际上是将树拆成很多条链来处理，在一条链上很明显是在查询区间右端点在 $n$ 处，与树状数组不符，但是其实可以非常简单的翻转区间，就成了树状数组的经典应用，另外，进行DFS时，会出现回溯树状数组的需求，不过非常简单，因为每次最多更改  $\log (n)$ 个节点，时间、空间复杂度可以被控制。

### 代码实现

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
#define int long long
inline int read();
int fir[200005];
int nxt[400005];
int v[400005];
int w[400005];
int p[200005];
int q[200005];
int dp[200005];
int seq[200005];
int dis[200005];
int tree[200005];
int n;
class backn{
    public:
        int pos,to;
};
class back{
    public:
        backn b[60];
        int co=0;
};
int lowbit(int x){
    return x&-x;
}
std::stack<back> a;
back add(int x,int y){
    back t;
    while(x<=n){
        // tree[x]=std::min(tree[x],y);
        if(y<tree[x]){
            t.co++;
            t.b[t.co].pos=x;
            t.b[t.co].to=tree[x];
            tree[x]=y;
        }
        x+=lowbit(x);
    }
    return t;
}
int que(int x){
    int _min=0x3f3f3f3f3f3f3f3f;
    while(x>0){
        _min=std::min(_min,tree[x]);
        x-=lowbit(x);
    }
    return _min;
}
int now;
void add(int x,int y,int z){
    now++;
    v[now]=y;
    w[now]=z;
    nxt[now]=fir[x];
    fir[x]=now;
    return ;
}
void dfs(int now,int fa,int dep){
    seq[dep]=now;
    int l=std::lower_bound(dis+1,dis+dep+1,dis[dep]-p[now])-dis;
    dp[now]=que(n-l+1)+q[now];
    if(now==1){
        dp[now]=q[now];
    }
    a.push(add(n-dep+1,dp[now]));
    for(int i=fir[now];i!=-1;i=nxt[i]){
        if(fa==v[i]){
            continue;
        }
        dis[dep+1]=dis[dep]+w[i];
        dfs(v[i],now,dep+1);
    }
    back temp=a.top();
    a.pop();
    for(int i=1;i<=temp.co;i++){
        tree[temp.b[i].pos]=temp.b[i].to;
    }
    return ;
}
signed main(){
    #ifdef ONLINE_JUDGE
    #else
    freopen("fish.in","r",stdin);
    freopen("fish.out","w",stdout);
    #endif
    // freopen(".out","w",stdout);
    n=read();
    for(int i=1;i<=n;i++){
        fir[i]=-1;
        tree[i]=0x3f3f3f3f3f3f3f3f;
    }
    for(int i=2;i<=n;i++){
        p[i]=read();
    }
    for(int i=2;i<=n;i++){
        q[i]=read();
    }
    for(int i=1;i<n;i++){
        int u=read(),v,w;
        v=read();
        w=read();
        add(u,v,w);
        add(v,u,w);
    }
    dfs(1,1,1);
    for(int i=1;i<=n;i++){
        if(dp[i]-q[i]==0x3f3f3f3f3f3f3f3f){
            printf("-1 ");
        }else
            printf("%lld ",dp[i]-q[i]);
    }
    return 0;
}
inline int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){
        c=='-'?f=-1:1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+(c^48);
        c=getchar();
    }
    return f*x;
}
/*
Anything about this program:
Type:

Description:

Example:
    1:
        In:

        Out:
More:

*/
```
