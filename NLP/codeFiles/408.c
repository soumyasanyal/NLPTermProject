int main(){
	int i, n;
	queue q = q_new();

	for (i = 0; i &lt; 100000000; i++) {
		n = rand();
		if (n &gt; RAND_MAX / 2) {
		//	printf(&quot;+ %d\n&quot;, n);
			enqueue(q, n);
		} else {
			if (!dequeue(q, &amp;n)) {
			//	printf(&quot;empty\n&quot;);
				continue;
			}
		//	printf(&quot;- %d\n&quot;, n);
		}
	}
	while (dequeue(q, &amp;n));// printf(&quot;- %d\n&quot;, n);

	return 0;
}
