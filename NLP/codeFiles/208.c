intgcd_bin(int u, int v) {
  int t, k;

  u = u &lt; 0 ? -u : u; /* abs(u) */
  v = v &lt; 0 ? -v : v; 
  if (u &lt; v) {
    t = u;
    u = v;
    v = t;
  }
  if (v == 0)
    return u;

  k = 1;
  while (u &amp; 1 == 0 &amp;&amp; v &amp; 1 == 0) { /* u, v - even */
    u &gt;&gt;= 1; v &gt;&gt;= 1;
    k &lt;&lt;= 1;
  }

  t = (u &amp; 1) ? -v : u;
  while (t) {
    while (t &amp; 1 == 0) 
      t &gt;&gt;= 1;

    if (t &gt; 0)
      u = t;
    else
      v = -t;

    t = u - v;
  }
  return u * k;        
}
