#include <iostream>
#include <cstdio>
#include <cstring>
#define int long long
inline int read();
int a[1000006];
int shu[2000005];
int _bit(int a){
    return (a)&(-a);
}
int query(int i){
    int ans=0;
    while(i>0){
        ans+=shu[i];
        i-=_bit(i);
    }
    return ans;
}
void add(int i,int too){
    while(i<=2000001){
        shu[i]+=too;
        i+=_bit(i);
    }
    return ;
}
int fr[1000006];
int bk[1000006];
void clear(int x){
    while(x<=2000001){
        shu[x]=0;
        x+=_bit(x);
    }
    return ;
}
signed main(){
	#ifdef ONLINE_JUDGE
	#else
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
	#endif
    int T=read();
    while(T--){
        int n=read();
        for(int i=1;i<=n;i++){
            a[i]=read();
        }
        for(int i=1;i<=n;i++){
            fr[i]=query(a[i]-1);
            add(a[i],1);
        }
        for(int i=1;i<=n;i++){
            clear(a[i]);
        }
        for(int i=n;i>=1;i--){
            bk[i]=query(a[i]-1);
            add(a[i],1);
        }
        int sum=0;
        for(int i=1;i<=n;i++){
            sum+=fr[i]*bk[i];
        }
        printf("%lld\n",sum);
        for(int i=1;i<=n;i++){
            clear(a[i]);
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


