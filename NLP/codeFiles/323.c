#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

char *menu_select(char **items, char *prompt);

int
main(void)
{
	char *items[] = {&quot;fee fie&quot;, &quot;huff and puff&quot;, &quot;mirror mirror&quot;, &quot;tick tock&quot;, NULL};
	char *prompt = &quot;Which is from the three pigs?&quot;;

	printf(&quot;You chose %s.\n&quot;, menu_select(items, prompt));

	return EXIT_SUCCESS;
}

char *
menu_select(char **items, char *prompt)
{
	char buf[BUFSIZ];
	int i;
	int choice;
	int choice_max;

	if (items == NULL)
		return NULL;

	do {
		for (i = 0; items[i] != NULL; i++) {
			printf(&quot;%d) %s\n&quot;, i + 1, items[i]);
		}
		choice_max = i;
		if (prompt != NULL)
			printf(&quot;%s &quot;, prompt);
		else
			printf(&quot;Choice? &quot;);
		if (fgets(buf, sizeof(buf), stdin) != NULL) {
			choice = atoi(buf);
		}
	} while (1 &gt; choice || choice &gt; choice_max);

	return items[choice - 1];
}
