#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
#define int long long
inline int read();
int dp[200005];
int sum[200005];
int p[200005];
int lowbit(int x){
	return x&-x;
}
int n;
int fir[200005];
int nxt[200005];
int v[200005];
int l[200005];
int w[200005];
int q[200005];
int dept[200005];
int now;
void add(int x,int y,int z){
	now++;
	v[now]=y;
	w[now]=z;
	nxt[now]=fir[x];
	fir[x]=now;
	return ;
}
long long Y(int j){return dp[dept[j]];}
long long X(int j){return sum[j];}
long long K(int i){return p[dept[i]];}
long long B(int i){return -sum[i]*p[dept[i]]-q[dept[i]];}
long double slope(int i,int j){return (X(i)-X(j)==0)?(1e9):((Y(i)-Y(j))*1.0/(X(i)-X(j)));}
bool check(int a,int b,int c,int d){return slope(a,b)<slope(c,d);}
bool checkslope(int a,int b,long long k){return Y(a)-Y(b)>k*(X(a)-X(b));}
class backu{
	public:
		int tail,pos,point;
		backu(int tt,int pp,int ppp){
			tail=tt;
			pos=pp;
			point=ppp;
			return ;
		}
};
class node{
	public:
		int *head;
		int tail;
		std::stack<backu> backup;
		node(){
			head=NULL;
			tail=0;
			return ;
		}
		void build(int length){
			head=(long long *)malloc((length+2)*sizeof(int));
			return ;
		}
		~node(){
			free(head);
		}
		void back(){
			backu temp=backup.top();
			backup.pop();
			head[temp.pos]=temp.point;
			tail=temp.tail;
			return ;
		}
		void in(int a){
			if(tail==0){
				head[++tail]=a;
				backup.push(backu(0,1,0));
			}else{
				int l=1,r=tail,mid;
				while(l<r){
					mid=(l+r)>>1;
					if(check(head[mid],head[mid+1],head[mid],a)){
						l=mid+1;
					}else{
						r=mid;
					}
				}
				backup.push(backu(tail,l+1,head[l+1]));
				head[l+1]=a;
				tail=l+1;
			}
			return ;
		}
		int Geet(int i){
			if(tail==0){
				return 0;
			}
			int l=1,r=tail,mid;
			while(l<r){
				mid=(l+r)>>1;
				if(checkslope(head[mid],head[mid+1],K(i))){
					l=mid+1;
				}else{
					r=mid;
				}
			}
			return head[l];
		}
}tree[200005];
int getDP(register int pos,int i){
	int ans=0x7fffffffffffffffll;
	pos=n-pos+1;
	while(pos>0){
		int point=tree[pos].Geet(i);
		if(point!=0){
			ans=std::min(ans,Y(point)-K(i)*X(point)-B(i));
		}
		pos-=lowbit(pos);
	}
	return ans;
}
void InsertBIT(register int pos,int point){
	pos=n-pos+1;
	while(pos<=n){
		if(tree[pos].head==NULL)
			tree[pos].build(lowbit(pos));
		tree[pos].in(point);
		pos+=lowbit(pos);
	}
	return;
}
void DeleteBIT(int i){
	i=n-i+1;
	while(i<=n){
		tree[i].back();
		i+=lowbit(i);
	}
	return ;
}
void dfs(int now,int dep){
	dept[dep]=now;
	int head=std::lower_bound(sum+1,sum+dep,sum[dep]-l[now])-sum;
	if(now==1){
		dp[now]=0;
	}
	else{
		dp[now]=getDP(head,dep);
	}
	InsertBIT(dep,dep);
	for(int i=fir[now];i!=-1;i=nxt[i]){
		sum[dep+1]=sum[dep]+w[i];
		dfs(v[i],dep+1);
	}
	DeleteBIT(dep);
	return ;
}
signed main(){
	#ifdef ONLINE_JUDGE
	#else
	freopen("ticket.in","r",stdin);
	freopen("ticket.out","w",stdout);
	#endif
    n=read();
    read();
	for(register int i=1;i<=n;i++){
		fir[i]=-1;
	}
	for(register int i=2;i<=n;++i){
		int t=read();
		int t2=read();
		add(t,i,t2);
		p[i]=read();
		q[i]=read();
		l[i]=read();
    }
	dfs(1,1);
	for(int i=2;i<=n;i++){
		printf("%lld\n",dp[i]);
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

