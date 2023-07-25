#include <cstdio>

struct node{
    int data,tag;
};

struct seq_tree{
    node tree[200010<<2];
    void build(int p,int l,int r,char* arr){
        if(l==r){
            tree[p].data=arr[l];
            return;
        }
        int mid=(l+r)>>1;
        build(p<<1,l,mid,arr);
        build((p<<1)+1,mid+1,r,arr);
        tree[p].data=tree[p<<1].data+tree[(p<<1)+1].data;
        return;
    }

    void update(int p,int s,int t,int l,int r){
        if(l<=s&&t<=r){
            tree[p].data=(t-s+1)-tree[p].data;
            tree[p].tag^=1;
            return;
        }
        int mid=(s+t)>>1;
        push_down(p,s,t,mid);
        if(l<=mid) update(p<<1,s,mid,l,r);
        if(mid<r) update((p<<1)+1,mid+1,t,l,r);
        tree[p].data=tree[p<<1].data+tree[(p<<1)+1].data;
    }

    int getsum(int p,int s,int t,int l,int r){
        if(l<=s&&t<=r) return tree[p].data;
        int mid=(s+t)>>1;
        push_down(p,s,t,mid);
        long long sum=0;
        if(l<=mid) sum+=getsum(p<<1,s,mid,l,r);
        if(mid<r) sum+=getsum((p<<1)+1,mid+1,t,l,r);
        return sum;
    }

    void push_down(int p,int l,int r,int mid){
        if(tree[p].tag){
            tree[p<<1].data=mid-l+1-tree[p<<1].data;
            tree[(p<<1)+1].data=r-mid-tree[(p<<1)+1].data;
            tree[p<<1].tag^=1;
            tree[(p<<1)+1].tag^=1;
            tree[p].tag=0;
        }
        return;
    }
}st;

char arr[200010];

int read(){
    register int x=0;register char f=0,c=getchar();
    while(c<'0'||'9'<c) f=(c=='-'),c=getchar();
    while('0'<=c&&c<='9') x=(x<<3)+(x<<1)+(c&15),c=getchar();
    return f?-x:x;
}

int main(){
    #ifndef ONLINE_JUDGE=LUOGU
    freopen("easy.in","r",stdin);
    freopen("easy.out","w",stdout);
    #endif
    register int i,l,r;
    register char z;
    int n=read();
    int m=read();
    

    st.build(1,1,n,arr);

    for(i=0;i<m;++i){
        z=read();
        l=read();
        if(z==2){
            
        
        printf("%d\n",st.getsum(1,1,n,l,l));
        }
        else{
            r=read();
            st.update(1,1,n,l,r);
        }
    }

    return 0;
}