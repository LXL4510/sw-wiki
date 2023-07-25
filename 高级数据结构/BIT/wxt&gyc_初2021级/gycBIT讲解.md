# 树状数组 BIT 总结

## 0x00 功能

树状数组，即BIT，用于在 $\mathcal{O}(\log n) $ 的时间复杂度下处理有**结合律**的**前缀查询**，以及**单点修改**。

- 结合律： $\oplus$ 表示一种运算，若对于任意 $x,y,z$ ，有 $\left(x\oplus y\right)\oplus z=x\oplus \left(y\oplus z\right)$ 。

## 0x01 实现

下面讲解都以前缀和为例

### 定义

使用树状结构对每一个区间使用二进制进行划分，如下图：

![](https://oi-wiki.org/ds/images/fenwick.svg)

对于节点 $i,1\leq i\leq size$ 定义其父亲节点为 $i+\operatorname{lowbit}\left(i\right)$ ，并且定义这个节点的权值为 $\operatorname{val}_i=\left(\sum_{j\in son_i}val_j\right)+arr_i$ 。

其中

- $\operatorname{lowbit}\left(x\right)$ 函数
  
  表示 $x$ 二进制最低位 `1` 以及后面的 `0` 组成的数。如 $lowbit\left(10010100_{\left(2\right)}\right)=100_{\left(2\right)}$
  
- $arr$
  
  表示需处理的数组。
  
- $size$
  
  表示需处理的数组大小。
  

### 推论

- 对于节点 $i,1\leq i\lt 2^{n}$ 其祖先必有 $2^n$ 这个节点
  
  证明：我们对于 $i$ 不考虑第二进制下第 $n$ 位的数，即考虑 $i\&\left(2^{n}-1\right)$ ，设其为 $x$ 假设其可以经过 $2^{n-1}$ 这个节点。这时考虑第 $n$ 位的数，若为 $0$ 则加上 $\operatorname{lowbit}\left(2^{n-1}\right)=2^{n-1}$ 则到了 $2^n$ 的节点；若为 $1$ 直接进位到 $2^n$ 。那么对于边界情况当 $i=1$ 时显然有此结论。数学归纳法 Q.E.D.
  
- 对于节点 $i$ 可以管辖的范围为 $\left[i-\operatorname{lowbit}\left(i\right)+1,i\right]$ ，其值为这个区间的 $arr$ 值之和。
  
  证明：对于 $x\in\left[i-\operatorname{lowbit}\left(i\right)+1,i\right]$ 这个节点先不考虑 $\operatorname{lowbit}\left(i\right)$ 这一位和前面的所有数，即考虑 $x\&\left(\operatorname{lowbit}\left(i\right)-1\right)$ 。由于上一条推论以可以知道 $x$ 可以走到 $\operatorname{lowbit}\left(i\right)$ 这个节点，这时加上前面的数就是 $i$ 这个节点，证得对于 $x\in\left[i-\operatorname{lowbit}\left(i\right)+1,i\right]$ 这个节点祖先必有。而这样推之所以正确是因为 $\operatorname{lowbit}\left(x\right)$ 只关注最后一个 $1$ 前面的数并无影响。
  
  Q.E.D.
  
- 对于节点 $i$ 不能管辖 $\left[i-\operatorname{lowbit}\left(i\right)+1,i\right]$ 以外的范围，其值为这个区间的 $arr$ 值之和。
  
  当 $x=i-\operatorname{lowbit}\left(x\right)$ 时，由于上一条推论可知其管辖范围为 $\left[x-\operatorname{lowbit}\left(x\right)+1,x\right]$ 而 $x+\operatorname{lowbit}\left(x\right) \gt i$ ，因为 $i-\operatorname{lowbit}\left(i\right)$ 实际上就是把 $i$ 最后一个 $1$ 去掉，那么 $\operatorname{lowbit}\left(i-\operatorname{lowbit}\left(i\right)\right)$ 就是剩下部分的最后一个 $1$ ，即 $i$ 的倒数第二个 $1$ 显然更大。
  
  当 $x=i-\operatorname{lowbit}\left(i-\operatorname{lowbit}\left(i\right)\right)$ 时，也有 $x+\operatorname{lowbit}\left(x\right) \gt i$ 相当于这时减了最后两个 $1$ ，此时 $\operatorname{lowbit}\left(x\right)$ 就是倒数第三个 $1$ ，显然大于倒数两个的 $1$ 的和，因为位数都不同。
  
  进而继续递归这个过程即可。
  
  当 $x\gt i$ 显然不会有父亲小于 $i$ ，因为 $\operatorname{lowbit}$ 永远大于 $0$ 。
  
  Q.E.D.


### 求解

#### 查询

假设现在我们需要求前缀和到 $x$ 这个点，设 
$ans$ 为返回值：

1. $ans\longleftarrow ans+val_x$ 即将 $\left[x-\operatorname{lowbit}\left(x\right)+1,x\right]$ 这个区间的值。
  
2. $x\longleftarrow x-\operatorname{lowbit}\left(x\right)$ 即将 $x$ 偏移到没去的区间。
  
3. 如果 $x$ 不为 $0$ 则 `goto 1` 。
  

这样就可以把大前缀区间拆成若干个小区间进行求和。

Code:

```cpp
int presum(int x) {
  int ans = 0;
  while (x > 0) {
    ans = ans + c[x];
    x = x - lowbit(x);
  }
  return ans;
}
```

#### 修改

假设要将 $x$ 这个点的值加上 $k$ ，只需要把这个节点的所有父亲加上 $k$ 即可。

Code:

```cpp
void add(int x, int k) {
  while (x <= n) {
    c[x] = c[x] + k;
    x = x + lowbit(x);
  }
}
```

### 时间复杂度

#### 查询

由于一直减去 $\operatorname{lowbit}\left(x\right)$ ，而每次减去会去掉末尾的 $1$ 那么有多少个 $1$ 就会减去多少次，即 $\operatorname{popcount}\left(x\right)$ 次。显然 $\mathcal{O}\left(\operatorname{popcount}\left(n\right)\right)=\mathcal{O}\left(\log n\right)$

#### 修改

同理一直加上 $\operatorname{lowbit}\left(x\right)$ ，而每次加显然也会去掉末尾的 $1$ 显然 $\mathcal{O}\left(\log n\right)$

## 0x02 Tricks

### 单点修改 区间查询

刚才实现的都是 **单点修改 前缀查询** ，若这个运算具有**差分性质**，就可以实现 **单点修改 区间查询** 。

- 差分性质：$\oplus$ 表示一种运算，若对于任意 $x,y$ 。已知 $x\oplus y$ 和 其中一者可求得另一者。

直接维护差分数组即可。

### $\mathcal{O}\left(n\right)$ 建树

建树朴素方法就是每个点加上 $arr_i$ 这样建树方法就是 $\mathcal{O}\left(n\log n\right)$ 。但是实际上可以
$\mathcal{O}\left(n\right)$ 建树。

考虑从儿子节点向上贡献每一个节点的值是由所有与自己直接相连的儿子的值求和得到的。因此可以倒着考虑贡献，即每次确定完儿子的值后，用自己的值更新自己的直接父亲。

Code:

```cpp
// Θ(n) 建树
void init() {
  for (int i = 1; i <= n; ++i) {
    t[i] += a[i];
    int j = i + lowbit(i);
    if (j <= n) t[j] += t[i];
  }
}
```

### $\operatorname{lowbit}\left(x\right)$ 实现细节

利用二进制补码特性 $\operatorname{lowbit}\left(x\right)=x\&-x$ 。

将 $x$ 的二进制所有位全部取反，再加 `1` ，就可以得到 `-x` 的二进制编码。例如，`6` 的二进制编码是 `110` ，全部取反后得到 `001` ，加 `1` 得到 `010` 。

设原先 `x` 的二进制编码是 `(...)10...00` ，全部取反后得到 `[...]01...11` ，加 `1` 后得到 `[...]10...00`，也就是 `-x` 的二进制编码了。这里 `x` 二进制表示中第一个 `1` 是 `x` 最低位的 `1` 。

`(...)` 和 `[...]` 中省略号的每一位分别相反，所以 `x & -x = (...)10...00 & [...]10...00 = 10...00` ，得到的结果就是 lowbit。

### Others

诸如二维BIT，不需要差分的BIT等等不太重要的Trick。可以查看 [树状数组 - OI Wiki](https://oi-wiki.org/ds/fenwick/)

## 谢鸣

本文部分图片/内容/代码摘自 [树状数组 - OI Wiki](https://oi-wiki.org/ds/fenwick/)