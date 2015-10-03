intgcd(int u, int v) {
  if (v)
    return gcd(v, u % v);
  else 
    return u &lt; 0 ? -u : u; /* abs(u) */
}
