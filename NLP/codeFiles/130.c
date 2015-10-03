#include &lt;stdio.h&gt;#include &lt;dirent.h&gt;
#include &lt;string.h&gt;

int dir_empty(char *path)
{
	struct dirent *ent;
	int ret = 1;

	DIR *d = opendir(path);
	if (!d) {
		fprintf(stderr, &quot;%s: &quot;, path);
		perror(&quot;&quot;);
		return -1;
	}

	while ((ent = readdir(d))) {
		if (!strcmp(ent-&gt;d_name, &quot;.&quot;) || !(strcmp(ent-&gt;d_name, &quot;..&quot;)))
			continue;
		ret = 0;
		break;
	}

	closedir(d);
	return ret;
}

int main(int c, char **v)
{
	int ret = 0, i;
	if (c &lt; 2) return -1;

	for (i = 1; i &lt; c; i++) {
		ret = dir_empty(v[i]);
		if (ret &gt;= 0)
			printf(&quot;%s: %sempty\n&quot;, v[i], ret ? &quot;&quot; : &quot;not &quot;);
	}

	return 0;
}
