#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

struct Editer {
	int f[10010];
	string word;
	Editer(string file) { Load(file); }
	void Load(string file) {
		char c;
		freopen(file.c_str(), "r", stdin);
		while((c = getchar()) != EOF) word += c;
	}
	void Output(string file) {
		freopen(file.c_str(), "w", stdout);
		puts(word.c_str());
	}
	void Next(string P,int * F) {
		int m = P.size();
		F[0] = - 1;
		for(register int i = 1, j = 0; i < m; i ++) {
			for(j = F[i - 1]; j != -1 && P[j + 1] != P[i]; j = F[j]);
			if(P[j + 1] == P[i]) j ++;
			F[i] = j;
		}
	}
	int Find(string T, string P, int * F) {
		int n = T.size(), m = P.size(), ans = 0, j = - 1;
		Next(P, F);
		for(register int i = 0; i < n; i ++) {
			while(j != - 1 && P[j + 1] != T[i]) j = F[j];
			if(P[j + 1] == T[i]) j ++;
			if(j + 1 == m) return i - j;
		}
		return -1;
	}
	bool Delete(string from, string to) {
		int a = Find(word, from, f), b = Find(word, to, f) + to.size();
		if(a == -1 || b == -1 || a > b) return false;
		word = word.substr(0, a) + word.substr(b, word.size() - b);
		return true;
	}
	bool Delete(string del) {
		int a = Find(word, del, f);
		if(a == - 1) return false;
		word = word.substr(0, a) + word.substr(a + del.size(), word.size() - a - del.size());
		return true;
	}
	bool Join(string from, string to, string inp) {
		int a = Find(word, from, f), b = Find(word, to, f);
		if(a == -1 || b == -1 || a > b) return false;
		word = word.substr(0, a + from.size()) + inp + word.substr(b, word.size() - b);
		return true;
	}
	string Get(string from, string to) {
		int a = Find(word, from, f), b = Find(word, to, f);
		if(a == -1 || b == -1 || a > b) return false;
		return word.substr(a + from.size(),  b - a - from.size());
	}
	bool Replace(string del, string inp) {
		int a = Find(word, del, f);
		if(a == - 1) return false;
		word = word.substr(0, a) + inp + word.substr(a + del.size(), word.size() - a - del.size());
		return true;
	}
};
int main(int argc, char * argv[]) {
	if(argc == 1) {
		
		printf("Helping Instructions :\n");
		printf("argv[1]: INPUT FILE NAME.  <string>\n");
		printf("argv[2]: CREATE DATE.      <string>\n");
		printf("argv[3]: OUTPUT FILE NAME. <string>\n");
		printf("-----------------------------------\n");
		printf("Copyright@Jason.Ghost : specter.jason@yahoo.com\n");
		
		return 0;
	}
	else if(argc != 4) {
		printf("ARGV IS ERROR!!!!");
		return 0;
	}
	
	cout << "Input old file..." << endl << endl;
	Editer zhi(argv[1]);
	
	string date = string(argv[2]);
	
	cout << "Deleting unnecessary Script from <footer> TO <!-- End Templates --> \n some terrible thing will make you 404\n You don't need praise and discuss for a static screen\nSTATE : " <<
	zhi.Delete("<footer>", "<!-- End Templates -->") << endl << endl;
	
	cout << "Deleting unnecessary Option to use in ZHIHU.com\nSTATE : " <<
	zhi.Delete("<!-- ngIf: !me.authed() && me.$resolved -->", "<!-- end ngIf: !inWrite -->") << endl << endl;
	
	cout << "Deleting more Scripts\nSTATE : " <<
	zhi.Delete("<!-- saved from url", "-->") << endl << endl;
	
	cout << "Replace ZHIHU LOGO point to your index\nSTATE : " <<
	zhi.Replace(		"https://www.zhihu.com", 
						zhi.Get("<a target=\"_blank\" href=\"", 
						"\" class=\"author name ng-binding\">")) << endl << endl;
	cout << "find time-setting position\nSTATE : " <<
	zhi.Join(
						"<time ng-class=\"{short: timeStyle == &#39;short&#39;}\" ui-hover-title=\"", 
						"class=\"published ng-binding ng-isolate-scope hover-title\">", 
						""
			) << endl << endl;
	
	cout << "Set time to your setting\nSTATE : " <<
	zhi.Join(			"class=\"published ng-binding ng-isolate-scope hover-title\">", 
						"</time>", 
						date) << endl << endl;
	
	/*
	cout << "Repoint css to a single place\nSTATE : " <<
	zhi.Join(			"<link rel=\"stylesheet\" href=\"", 
						".main.css\">", 
						"../css/passage"
			) << endl << endl;  */
	cout << "Outputi new file...." << endl << endl;
	zhi.Output(argv[3]);
	return 0;
}
