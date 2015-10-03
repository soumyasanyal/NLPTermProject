#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

typedef struct stream_t stream_t, *stream;
struct stream_t {
	/* get funciton is supposed to return a byte value (0-255),
		or -1 to signify end of input */
	int (*get)(stream);
	/* put function does output, one byte at a time */
	int (*put)(stream, int);
};

/* next two structs inherit from stream_t */
typedef struct {
	int (*get)(stream);
	int (*put)(stream, int);
	char *string;
	int pos;
} string_stream;

typedef struct {
	int (*get)(stream);
	int (*put)(stream, int);
	FILE *fp;
} file_stream;

/* methods for above streams */
int sget(stream in)
{
	int c;
	string_stream* s = (string_stream*) in;
	c = (unsigned char)(s-&gt;string[s-&gt;pos]);
	if (c == '\0') return -1;
	s-&gt;pos++;
	return c;
}

int sput(stream out, int c)
{
	string_stream* s = (string_stream*) out;
	s-&gt;string[s-&gt;pos++] = (c == -1) ? '\0' : c;
	if (c == -1) s-&gt;pos = 0;
	return 0;
}

int file_put(stream out, int c)
{
	file_stream *f = (file_stream*) out;
	return fputc(c, f-&gt;fp);
}

/* helper function */
void output(stream out, unsigned char* buf, int len)
{
	int i;
	out-&gt;put(out, 128 + len);
	for (i = 0; i &lt; len; i++)
		out-&gt;put(out, buf[i]);
}

/* Specification: encoded stream are unsigned bytes consisting of sequences.
 * First byte of each sequence is the length, followed by a number of bytes.
 * If length &lt;=128, the next byte is to be repeated length times;
 * If length &gt; 128, the next (length - 128) bytes are not repeated.
 * this is to improve efficiency for long non-repeating sequences.
 * This scheme can encode arbitrary byte values efficiently.
 * c.f. Adobe PDF spec RLE stream encoding (not exactly the same)
 */
void encode(stream in, stream out)
{
	unsigned char buf[256];
	int len = 0, repeat = 0, end = 0, c;
	int (*get)(stream) = in-&gt;get;
	int (*put)(stream, int) = out-&gt;put;

	while (!end) {
		end = ((c = get(in)) == -1);
		if (!end) {
			buf[len++] = c;
			if (len &lt;= 1) continue;
		}

		if (repeat) {
			if (buf[len - 1] != buf[len - 2])
				repeat = 0;
			if (!repeat || len == 129 || end) {
				/* write out repeating bytes */
				put(out, end ? len : len - 1);
				put(out, buf[0]);
				buf[0] = buf[len - 1];
				len = 1;
			}
		} else {
			if (buf[len - 1] == buf[len - 2]) {
				repeat = 1;
				if (len &gt; 2) {
					output(out, buf, len - 2);
					buf[0] = buf[1] = buf[len - 1];
					len = 2;
				}
				continue;
			}
			if (len == 128 || end) {
				output(out, buf, len);
				len = 0;
				repeat = 0;
			}
		}
	}
	put(out, -1);
}

void decode(stream in, stream out)
{
	int c, i, cnt;
	while (1) {
		c = in-&gt;get(in);
		if (c == -1) return;
		if (c &gt; 128) {
			cnt = c - 128;
			for (i = 0; i &lt; cnt; i++)
				out-&gt;put(out, in-&gt;get(in));
		} else {
			cnt = c;
			c = in-&gt;get(in);
			for (i = 0; i &lt; cnt; i++)
				out-&gt;put(out, c);
		}
	}
}

int main()
{
	char buf[256];
	string_stream str_in = { sget, 0,
		&quot;WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW&quot;, 0};
	string_stream str_out = { sget, sput, buf, 0 };
	file_stream file = { 0, file_put, stdout };

	/* encode from str_in to str_out */
	encode((stream)&amp;str_in, (stream)&amp;str_out);

	/* decode from str_out to file (stdout) */
	decode((stream)&amp;str_out, (stream)&amp;file);

	return 0;
}
