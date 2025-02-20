#include <bits/stdc++.h>

#define N 100007
// dp[i][0] - maximum number of points for numbers <= i if not taking a_i
// dp[i][1] - maximum number of points for numbers <= i if taking a_i

using namespace std;
int main() {
	int n; 
	scanf("%d", &n);
	long long count[N] = { 0 };
	int maxi = -1;
	
	for (int i = 0; i < n; i++) {
		int a;
		scanf("%d", &a);
		count[a]++;
		maxi = max(a, maxi);
	}
	long long prev_in = 0;
	long long prev_ex = 0, prev_ex_new;

	
	for (int i = 1; i <= maxi; i++) {
		prev_ex_new = max(prev_ex, prev_in);
		prev_in = count[i] * i + prev_ex;
		prev_ex = prev_ex_new;
	}
	printf("%lld\n",max(prev_ex, prev_in));
	return 0;
}