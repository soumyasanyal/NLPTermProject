#include &lt;string.h&gt;#include &lt;stdio.h&gt;

int luhn(const char* cc)
{
	const int m[] = {0,2,4,6,8,1,3,5,7,9}; // mapping for rule 3
	int i, odd = 1, sum = 0;

	for (i = strlen(cc); i--; odd = !odd) {
		int digit = cc[i] - '0';
		sum += odd ? digit : m[digit];
	}

	return sum % 10 == 0;
}

int main()
{
	const char* cc[] = {
		&quot;49927398716&quot;,
		&quot;49927398717&quot;,
		&quot;1234567812345678&quot;,
		&quot;1234567812345670&quot;,
		0
	};
	int i;

	for (i = 0; cc[i]; i++)
		printf(&quot;%16s\t%s\n&quot;, cc[i], luhn(cc[i]) ? &quot;ok&quot; : &quot;not ok&quot;);

	return 0;
}
