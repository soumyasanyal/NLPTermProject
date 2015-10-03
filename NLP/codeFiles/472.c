void sierpinski_triangle(int n){
  int i;
  int l = 1&lt;&lt;(n+1);
  char *b = malloc(l+1);

  memset(b, ' ', l);
  b[l] = 0;
  b[l&gt;&gt;1] = '*';

  printf(&quot;%s\n&quot;, b);
  for(i=0; i &lt; l/2-1;i++) {
    rule_90(b);
    printf(&quot;%s\n&quot;, b);
  }

  free(b);
}
