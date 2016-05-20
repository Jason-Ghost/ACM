#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

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
const int MAXN = 10000 + 10;
int n, ans = 0, a[MAXN], b[MAXN];

int main(void) {
  //freopen("in.txt", "r", stdin);
  read(n);
  register int i, j;
  for(i = 1; i <= n; i++) a[i] = NC() - '0', NC();
  for(i = 0; i <= a[1]; i++) {
    memset(b, 0, sizeof(b));
    b[1] = i, b[2] = a[1] - i;
    for(j = 3; j <= n + 1; j++)
      b[j] = a[j - 1] - b[j - 1] - b[j - 2];
    if(!b[n + 1]) ans ++;
  }
  printf("%d\n", ans);
  return 0;
}
