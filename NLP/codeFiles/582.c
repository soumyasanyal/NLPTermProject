#include &lt;sys/types.h&gt;#include &lt;dirent.h&gt;
#include &lt;regex.h&gt;
#include &lt;stdio.h&gt;

enum {
    WALK_OK = 0,
    WALK_BADPATTERN,
    WALK_BADOPEN,
};

int walker(const char *dir, const char *pattern)
{
    struct dirent *entry;
    regex_t reg;
    DIR *d; 

    if (regcomp(&amp;reg, pattern, REG_EXTENDED | REG_NOSUB))
        return WALK_BADPATTERN;
    if (!(d = opendir(dir)))
        return WALK_BADOPEN;
    while (entry = readdir(d))
        if (!regexec(&amp;reg, entry-&gt;d_name, 0, NULL, 0))
            puts(entry-&gt;d_name);
    closedir(d);
    regfree(&amp;reg);
    return WALK_OK;
}

int main()
{
    walker(&quot;.&quot;, &quot;.\\.c$&quot;);
    return 0;
}
