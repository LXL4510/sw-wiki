#include<cstdio>
#include<algorithm>
// #define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE long long
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){register char s[20];register int i=0;if(x<0){x=-x;putchar('-');}if(x==0){putchar('0');return;}while(x){s[i++]=x%10;x/=10;}while(i){putchar(s[--i]+'0');}return;}

#include<cstring>
#define BIT_DATA_TYPE int
const int BIT_SIZE=2000010;
struct BIT{
    BIT_DATA_TYPE tree[BIT_SIZE];
    int size;

    void build(BIT_DATA_TYPE *data,int datasize){
        size=datasize;
        for(register int i=1;i<=datasize;++i){
            tree[i]+=data[i];
            tree[i+lowbit(i)]+=tree[i];
        }
        return;
    }

    BIT_DATA_TYPE getsum(int l,int r){
        return presum(r)-presum(l-1);
    }

    BIT_DATA_TYPE presum(int pos){
        BIT_DATA_TYPE sum=0;
        while(pos){
            sum+=tree[pos];
            pos-=lowbit(pos);
        }
        return sum;
    }

    void add(BIT_DATA_TYPE data,int pos){
        while(pos<=size){
            tree[pos]+=data;
            pos+=lowbit(pos);
        }
    }

    BIT_DATA_TYPE lowbit(BIT_DATA_TYPE x){
        return x&-x;
    }

    void clear(int pos){
        while(pos<=size){
            tree[pos]=0;
            pos+=lowbit(pos);
        }
    }
}bit;

int arr[1000010];
long long ans[1000010];

int main(){
	#ifndef ONLINE_JUDGE
	freopen("seq.in", "r", stdin);
	freopen("seq.out", "w", stdout);
	#endif

    register int T=read(),n,i,maxv;
    register long long res;
    while(T--){
        maxv=res=0;
        n=read();
        for(i=0;i<n;++i) arr[i]=read(),maxv=std::max(maxv,arr[i]);
        bit.size=maxv;
        for(i=0;i<n;++i){
            ans[i]=bit.presum(arr[i]-1);
            bit.add(1,arr[i]);
        }
        for(i=0;i<n;++i) bit.clear(arr[i]);
        for(i=n-1;~i;--i){
            res+=ans[i]*bit.presum(arr[i]-1);
            bit.add(1,arr[i]);
        }
        for(i=0;i<n;++i) bit.clear(arr[i]);
        print(res);putchar('\n');
    }

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}