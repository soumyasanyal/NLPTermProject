int main(){
	int j;
	ulong fac[10000], n, sum;
 
	sieve();
 
	for (n = 2; n &lt; 33550337; n++) {
		j = get_factors(n, fac) - 1;
		for (sum = 0; j &amp;&amp; sum &lt;= n; sum += fac[--j]);
		if (sum == n) printf(&quot;%lu\n&quot;, n);
	}
 
	return 0;
}
