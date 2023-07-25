#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
inline int read();
int a[1000006];
int tree[1000006];
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
	#ifdef ONLINE_JUDGE
	#else
	freopen("query.in","r",stdin);
	freopen("query.out","w",stdout);
	#endif
    int t=read();
    while(t--){
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

