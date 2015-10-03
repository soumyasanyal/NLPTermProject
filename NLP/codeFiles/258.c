	if (x &gt; 0) goto positive;	else goto negative;

positive:
	printf(&quot;pos\n&quot;); goto both;

negative:
	printf(&quot;neg\n&quot;);

both:
	...

