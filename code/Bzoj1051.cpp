#include <stack>
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXE = 100000 + 10,
          MAXN = 100000 + 10;
int head[MAXN], sub = 1, n, m, a, b;
struct E {
  int to, next;
} edge[MAXE];
inline void AddEdge(int a, int b) {
  E &e = edge[sub];
  e.to = b, e.next = head[a], head[a] = sub++;
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
stack<int> S, P;
int attain[MAXN], cnt = 1, id = 1, acc[MAXN], reduce[MAXN],
    total = 0, res, result = 0;
void GabowDFS(int w) {
  int v, t;
  acc[w] = cnt++;
  S.push(w), P.push(w);
  for(t = head[w]; t; t = edge[t].next) {
    if(!acc[v = edge[t].to]) GabowDFS(v);
    else if(!attain[v])
      while(acc[P.top()] > acc[v]) P.pop();
  }
  if(P.top() == w) {
    P.pop();
    do {
      attain[v = S.top()] = id;
      S.pop();
    } while(v != w);
    ++id;
  }
}
int main (void) {
  freopen("in.txt", "r", stdin);
  register int i, j;
  read(n), read(m);
  for(i = 0; i < m; i++) {
    read(a), read(b);
    AddEdge(a, b);
  }
  for(i = 1; i <= n; i++) if(!acc[i]) GabowDFS(i);
  for(i = 1; i <= n; i++)
    for(j = head[i]; j; j = edge[j].next)
      if(attain[i] != attain[edge[j].to])
        reduce[attain[i]]++;
  for(i = 1; i < id; i++)
    if(!reduce[i]) total++, res = i;
  if(total == 1) {
    for(i = 1; i <= n; i++)
      if(attain[i] == res) result++;
      printf("%d\n", result);
  } else puts("0");
  return 0;
}
