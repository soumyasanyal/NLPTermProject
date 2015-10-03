#include &lt;GL/glut.h&gt;#include &lt;GL/gl.h&gt;
#include &lt;stdio.h&gt;
#include &lt;time.h&gt;
 
#define W 320
#define H 240
#define slen W * H / sizeof(int)
 
time_t start, last;
 
void render()
{
	static int frame = 0, bits[slen];
	register int i = slen, r;
	time_t t;
 
	r = bits[0] + 1;
	while (i--) r *= 1103515245, bits[i] = r ^ (bits[i] &gt;&gt; 16);

	glClear(GL_COLOR_BUFFER_BIT);
	glBitmap(W, H, 0, 0, 0, 0, (void*)bits);
	glFlush();

	if (!(++frame &amp; 15)) {
		if ((t = time(0)) &gt; last) {
			last = t;
			printf(&quot;\rfps: %ld  &quot;, frame / (t - start));
			fflush(stdout);
		}
	}
}
 
int main(int argc, char **argv) 
{
	glutInit(&amp;argc, argv);
	glutInitDisplayMode(GLUT_INDEX);
	glutInitWindowSize(W, H);
	glutCreateWindow(&quot;noise&quot;);
	glutDisplayFunc(render);
	glutIdleFunc(render);
 
	last = start = time(0);
 
	glutMainLoop();
	return 0;
}
