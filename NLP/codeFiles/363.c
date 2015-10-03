int list_cmp(int *a, int la, int *b, int lb){
	int i, l = la;
	if (l &gt; lb) l = lb;
	for (i = 0; i &lt; l; i++) {
		if (a[i] == b[i]) continue;
		return (a[i] &gt; b[i]) ? 1 : -1;
	}
	if (la == lb) return 0;
	return la &gt; lb ? 1 : -1;
}
