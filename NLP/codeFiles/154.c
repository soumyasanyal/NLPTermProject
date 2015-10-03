int isPrime(int n){	if (n%2==0) return n==2;
	if (n%3==0) return n==3;
	int d=5;
	while(d*d&lt;=n){
		if(n%d==0) return 0;
		d+=2;
		if(n%d==0) return 0;
		d+=4;}
	return 1;}

main() {int i,d,p,r,q=929;
	if (!isPrime(q)) return 1; 
	r=q;
	while(r&gt;0) r&lt;&lt;=1;
	d=2*q+1;
	do { 	for(p=r, i= 1; p; p&lt;&lt;= 1){
			i=((long long)i * i) % d;
			if (p &lt; 0) i *= 2;
			if (i &gt; d) i -= d;}
		if (i != 1) d += 2*q;
		else break;
	} while(1);
	printf(&quot;2^%d - 1 = 0 (mod %d)\n&quot;, q, d);}
