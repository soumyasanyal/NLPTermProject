int main(){
	int i, j, n = 12;
 
	for (j = 1; j &lt;= n; j++) printf(&quot;%3d%c&quot;, j, j - n ? ' ':'\n');
	for (j = 0; j &lt;= n; j++) printf(j - n ? &quot;----&quot; : &quot;+\n&quot;);

	for (i = 1; i &lt;= n; printf(&quot;| %d\n&quot;, i++))
		for (j = 1; j &lt;= n; j++)
			printf(j &lt; i ? &quot;    &quot; : &quot;%3d &quot;, i * j);
 
	return 0;
}
