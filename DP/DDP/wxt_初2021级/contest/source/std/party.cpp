#include <iostream>
#include <cstdio>
#include <cstring>
#define int long long
inline int read();
class Matrix{
    public:
        int map[6][6];
        Matrix(){
            for(int i=1;i<=3;i++){
                for(int j=1;j<=3;j++){
                    map[i][j]=-0x7f7f7f7fll;
                }
            }
        }
};
Matrix operator * (Matrix a,Matrix b){
    Matrix c;
    for(int i=1;i<=3;i++){
        for(int j=1;j<=3;j++){
            for(int k=1;k<=3;k++){
                c.map[i][j]=std::max(c.map[i][j],a.map[i][k]+b.map[k][j]);
            }
        }
    }
    return c;
}
int fir[50005];
int nxt[100005];
int siz[100005];
int f[100005][5];
int DFN[100005];
int dep[100005];
int fa[100005];
int bson[100005];
int id[300005];
int dfn=0;
int top[300005];
int end[300005];
int v[100005];
int b[100005];
int now,n,m;
void add(int a,int b){
    v[++now]=b;
    nxt[now]=fir[a];
    fir[a]=now;
    return ;
}
Matrix zero;
Matrix Val[400005];
Matrix tree[400005];
int le[400005],ri[400005];
void dfs1(int now,int fa){
    siz[now]=1;
    dep[now]=dep[fa]+1;
    ::fa[now]=fa;
    bson[now]=0;
    for(int i=fir[now];i!=-1;i=nxt[i]){
        if(fa==v[i]){
            continue;
        }
        dfs1(v[i],now);
        siz[now]+=siz[v[i]];
        if(siz[v[i]]>siz[bson[now]]){
            bson[now]=v[i];
        }
    }
    return ;
}
void dfs2(int now,int fa,int topf){
    id[now]=++dfn;
    top[now]=topf;
    end[topf]=std::max(end[topf],dfn);
    //init
    DFN[dfn]=now;
    f[now][1]=b[now];
    if(bson[now]!=0){
        dfs2(bson[now],now,topf);
        f[now][0]+=std::max(f[bson[now]][0],f[bson[now]][1]);
    }
    int g=0;
    for(int i=fir[now];i!=-1;i=nxt[i]){
        int &v=::v[i];
        if(v==bson[now]||v==::fa[now]){
            continue;
        }
        dfs2(v,now,v);
        f[now][0]+=std::max(f[v][0],f[v][1]);
        g+=std::max(f[v][0],f[v][1]);
        //init
    }
    Val[now].map[1][1]=Val[now].map[1][2]=g;
    Val[now].map[2][3]=b[now];
    Val[now].map[3][3]=0;
    return ;
}
void build(int l,int r,int now){
    le[now]=l;
    ri[now]=r;
    if(le[now]>ri[now]){
        return ;
    }
    if(le[now]==ri[now]){
        tree[now]=Val[DFN[le[now]]];
        return ;
    }
    int mid=(l+r)/2;
    build(l,mid,now*2);
    build(mid+1,r,now*2+1);
    tree[now]=tree[now*2]*tree[now*2+1];
}
int x;
void update(int l,int r,int now){
    if(l==r){
        tree[now]=Val[DFN[x]];
        return ;
    }
    int mid=(l+r)/2;
    if(x<=mid){
        update(l,mid,now*2);
    }else{
        update(mid+1,r,now*2+1);
    }
    tree[now]=tree[now*2]*tree[now*2+1];
}
int x1,x2;
Matrix query(int l,int r,int now){
    if(x1<=l&&r<=x2){
        return tree[now];
    }
    if(l>x2||x1>r){
        return zero;
    }
    int mid=(l+r)/2;
    if(x2<=mid){
        return query(l,mid,now*2);
    }else if(x1>mid){
        return query(mid+1,r,now*2+1);
    }else{
        return query(l,mid,now*2)*query(mid+1,r,now*2+1);
    }
}
void update2(int now,int to){
    b[now]=to;
    Val[now].map[2][3]=to;
    Matrix t1,t2;
    while(now!=0){
        x1=id[top[now]];
        x2=end[top[now]];
        t1=query(1,n,1);
        x=id[now];
        update(1,n,1);
        x1=id[top[now]];
        x2=end[top[now]];
        t2=query(1,n,1);
        now=fa[top[now]];
        Val[now].map[1][1]+=std::max(t2.map[1][1]-t1.map[1][1],t2.map[2][3]-t1.map[1][1]);
        Val[now].map[1][2]=Val[now].map[1][1];
    }
    return ;
}
signed main(){
	#ifdef ONLINE_JUDGE
	#else
	freopen("party.in","r",stdin);
	freopen("party.out","w",stdout);
	#endif
    memset(zero.map,0,sizeof(zero.map));
    n=read();
    m=read();
    for(int i=1;i<=n;i++){
        fir[i]=-1;
        b[i]=read();
    }
    for(int i=1;i<n;i++){
        int u=read(),v;
        v=read();
        add(u,v);
        add(v,u);
    }
    dfs1(1,0);
    dfs2(1,0,1);
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int x=read();
        int k=read();
        update2(x,k);
        x1=id[1];
        x2=end[1];
        Matrix ans=query(1,n,1);
        printf("%lld\n",std::max(ans.map[1][1],ans.map[2][3]));
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


