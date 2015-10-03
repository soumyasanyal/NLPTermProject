void bitwise(int a, int b){
  printf(&quot;a and b: %d\n&quot;, a &amp; b);
  printf(&quot;a or b: %d\n&quot;, a | b);
  printf(&quot;a xor b: %d\n&quot;, a ^ b);
  printf(&quot;not a: %d\n&quot;, ~a);
  printf(&quot;a &lt;&lt; n: %d\n&quot;, a &lt;&lt; b); /* left shift */
  printf(&quot;a &gt;&gt; n: %d\n&quot;, a &gt;&gt; b); /* on most platforms: arithmetic right shift */
  /* convert the signed integer into unsigned, so it will perform logical shift */
  unsigned int c = a;
  printf(&quot;c &gt;&gt; b: %d\n&quot;, c &gt;&gt; b); /* logical right shift */
  /* there are no rotation operators in C */
  return 0;
}
