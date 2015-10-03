#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

#define caesar(x) rot(13, x)
#define decaesar(x) rot(13, x)
#define decrypt_rot(x, y) rot((26-x), y)

void rot(int c, char *str)
{
	int l = strlen(str);
	char alpha[2][27] = { &quot;abcdefghijklmnopqrstuvwxyz&quot;, &quot;ABCDEFGHIJKLMNOPQRSTUVWXYZ&quot;};
	
	int i;
	for (i = 0; i &lt; l; i++)
	{
		if (!isalpha(str[i]) || (str[i] == ' '))
			continue;
		
		str[i] = alpha[isupper(str[i])][((int)(tolower(str[i])-'a')+c)%26];
	}
}


int main()
{
	char str[100] = &quot;This is a top secret text message!&quot;;
	
	printf(&quot;Original: %s\n&quot;, str);
	caesar(str);
	printf(&quot;Encrypted: %s\n&quot;, str);
	decaesar(str);
	printf(&quot;Decrypted: %s\n&quot;, str);
	
	return 0;
}
