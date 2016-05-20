#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 3000 + 10;
struct E {
  int to, next, v;
  E(int t = (int)NULL, int n = (int)NULL, int v = (int)NULL) : to(t), next(n), v(v) {}
} edge[70000 + 10];
int sub = 0, head[MAXN];
inline void AddEdge(int a, int b, int v) {
  edge[sub] = E(b, head[a], v), head[a] = sub++;
}
inline char NC(void) {
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
int n, m, d[MAXN], a[MAXN][MAXN], l[MAXN], d1[MAXN], d2[MAXN];
bool vis[MAXN];
int x, y, v;

priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
int main(void) {
  memset(head, -1, sizeof(head));
  read(n), read(m);
  register int i, j;
  for(i = 0; i < m; i++) {
    read(x), read(y), read(v);
    if(x != y) AddEdge(x, y, v);
  }
  for(i = 1; i <= n; i++) {
    read(d[i]);
    for(j = 1; j <= d[i]; j++)
      read(x), a[x][++l[x]] = i;
  }

  memset(d1, 127 / 3, sizeof(d1));
  q.push(make_pair(0, 1));
  d1[1] = 0;
  int now, mx, tmp, t;
  while(!q.empty()) {
    now = q.top().second, q.pop();
    if(vis[now]) continue; vis[now] = true;
    mx = max(d1[now], d2[now]);
    for(i = head[now]; i != -1; i = edge[i].next)
      if(mx + edge[i].v < d1[edge[i].to]) {
        d1[edge[i].to] = mx + edge[i].v;
        tmp = max(d1[edge[i].to], d2[edge[i].to]);
        if(!d[edge[i].to]) q.push(make_pair(tmp, edge[i].to));
      }
      for(i = 1; i <= l[now]; i++) {
        t = a[now][i];
        d[t] --; d2[t] = max(d2[t], mx);
        tmp = max(d1[t], d2[t]);
        if(!d[t]) q.push(make_pair(tmp, t));
      }
  }
  printf("%d\n", max(d1[n], d2[n]));
  return 0;
}
