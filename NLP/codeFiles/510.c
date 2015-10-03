#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

/* to read expanded code, run through cpp | indent -st */
#define DECL_STACK_TYPE(type, name)					\
typedef struct stk_##name##_t{type *buf; size_t alloc,len;}*stk_##name;	\
stk_##name stk_##name##_create(size_t init_size) {			\
	stk_##name s; if (!init_size) init_size = 4;			\
	s = malloc(sizeof(struct stk_##name##_t));			\
	if (!s) return 0;						\
	s-&gt;buf = malloc(sizeof(type) * init_size);			\
	if (!s-&gt;buf) { free(s); return 0; }				\
	s-&gt;len = 0, s-&gt;alloc = init_size;				\
	return s; }							\
int stk_##name##_push(stk_##name s, type item) {			\
	type *tmp;							\
	if (s-&gt;len &gt;= s-&gt;alloc) {					\
		tmp = realloc(s-&gt;buf, s-&gt;alloc*2*sizeof(type));		\
		if (!tmp) return -1; s-&gt;buf = tmp;			\
		s-&gt;alloc *= 2; }					\
	s-&gt;buf[s-&gt;len++] = item;					\
	return s-&gt;len; }						\
type stk_##name##_pop(stk_##name s) {					\
	type tmp;							\
	if (!s-&gt;len) abort();						\
	tmp = s-&gt;buf[--s-&gt;len];						\
	if (s-&gt;len * 2 &lt;= s-&gt;alloc &amp;&amp; s-&gt;alloc &gt;= 8) {			\
		s-&gt;alloc /= 2;						\
		s-&gt;buf = realloc(s-&gt;buf, s-&gt;alloc * sizeof(type));}	\
	return tmp; }							\
void stk_##name##_delete(stk_##name s) {				\
	free(s-&gt;buf); free(s); }

#define stk_empty(s) (!(s)-&gt;len)
#define stk_size(s) ((s)-&gt;len)

DECL_STACK_TYPE(int, int)

int main(void)
{
	int i;
	stk_int stk = stk_int_create(0);

	printf(&quot;pushing: &quot;);
	for (i = 'a'; i &lt;= 'z'; i++) {
		printf(&quot; %c&quot;, i);
		stk_int_push(stk, i);
	}

	printf(&quot;\nsize now: %d&quot;, stk_size(stk));
	printf(&quot;\nstack is%s empty\n&quot;, stk_empty(stk) ? &quot;&quot; : &quot; not&quot;);

	printf(&quot;\npoppoing:&quot;);
	while (stk_size(stk))
		printf(&quot; %c&quot;, stk_int_pop(stk));
	printf(&quot;\nsize now: %d&quot;, stk_size(stk));
	printf(&quot;\nstack is%s empty\n&quot;, stk_empty(stk) ? &quot;&quot; : &quot; not&quot;);

	/* stk_int_pop(stk); &lt;-- will abort() */
	stk_int_delete(stk);
	return 0;
}
