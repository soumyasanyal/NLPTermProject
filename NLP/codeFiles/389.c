int is_prime(unsigned int n){
	unsigned int p;
	if (!(n &amp; 1) || n &lt; 2 ) return n == 2;

	/* comparing p*p &lt;= n can overflow */
	for (p = 3; p &lt;= n/p; p += 2)
		if (!(n % p)) return 0;
	return 1;
}
