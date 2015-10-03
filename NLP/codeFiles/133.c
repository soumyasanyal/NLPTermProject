/* assign an empty string */char *str = &quot;&quot;;
/* to test a null string */
if (str) { ... }
/* to test if string is empty */
if (str[0] == '\0') { ... }
/* or equivalently use strlen function */
if (strlen(str) == 0) { ... }
/* or compare to a known empty string, same thing. &quot;== 0&quot; means strings are equal */
if (strcmp(str, &quot;&quot;) == 0) { ... } 

