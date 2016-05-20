#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXM = 200000 * 2 + 10,
          MAXN = 200000 * 2 + 10;
struct E {
  int to, next;
  E(int t = (int)NULL, int n = (int)NULL) : to(t), next(n) {}
} edge[MAXM];
int sub = 0, f[MAXN], n, m, k, a, b, del[MAXN], ans[MAXN], sum = 0, head[MAXN];
bool non_del[MAXN];

inline char NC(void)
{
	static char buf[100000], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
    p2 = (p1 = buf) + fread(buf, 1, 100000, stdin);
    if (p1 == p2) return EOF;
  }
	return *p1++;
}
inline void read(int &x) {
	static char c; c = NC(); x = 0;
	for(; !(c >= '0' && c <= '9'); c = NC());
  for(; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = NC());
}
inline void write(int k) {
	static short ch[32], num;
    num = 0;
    while(k > 0) ch[++num] = k % 10, k /= 10;
    while(num) putchar(ch[num--] + '0');
    putchar('\n');
}  
inline int Getf(int a) {
  if (a != f[a]) f[a] = Getf(f[a]);
  return f[a];
}
inline void AddEdge(int a, int b) {
  edge[sub] = E(b, head[a]), head[a] = sub++;
  edge[sub] = E(a, head[b]), head[b] = sub++;
}
int main(void) {
  //freopen("in.txt", "r", stdin);
  memset(head, -1, sizeof(head));
  read(n), read(m);
  for(int i = 0; i <= n; i++) f[i] = i;
  register int i, j;
  int fi, fj;
  for(i = 0; i < m; i++) read(a), read(b),
    AddEdge(a, b);
  for(read(k), i = 0; i < k; i++)
    read(del[i]), non_del[del[i]] = true;
  for(sum = n - k, i = 0; i < n; i++)
    if(!non_del[i]) {
      fi = Getf(i);
      for(j = head[i]; j != -1; j = edge[j].next)
        if(!non_del[edge[j].to]) {
          fj = Getf(edge[j].to);
          if(fi != fj) sum--, f[fj] = fi;
        }
    }
  ans[k] = sum;
  for(i = k - 1; i >= 0; i --) {
    sum++,  fi = del[i];
    for(j = head[del[i]]; j != -1; j = edge[j].next)
      if(!non_del[edge[j].to]) {
        fj = Getf(edge[j].to);
        if(fi != fj) sum--, f[fj] = fi;
      }
      ans[i] = sum;
      non_del[del[i]] = false;
  }
  for(i = 0; i <= k; i++) printf("%d\n", ans[i]); //write(ans[i]);
  return 0;
}
