#include &lt;limits.h&gt;	/* INT_MIN */#include &lt;setjmp.h&gt;	/* siglongjmp(), sigsetjmp() */
#include &lt;stdio.h&gt;	/* perror(), printf() */
#include &lt;stdlib.h&gt;	/* exit() */
#include &lt;signal.h&gt;	/* sigaction(), sigemptyset() */

static sigjmp_buf fpe_env;

/*
 * This SIGFPE handler jumps to fpe_env.
 *
 * A SIGFPE handler must not return, because the program might retry
 * the division, which might cause an infinite loop. The only safe
 * options are to _exit() the program or to siglongjmp() out.
 */
static void
fpe_handler(int signal, siginfo_t *w, void *a)
{
	siglongjmp(fpe_env, w-&gt;si_code);
	/* NOTREACHED */
}

/*
 * Try to do x / y, but catch attempts to divide by zero.
 */
void
try_division(int x, int y)
{
	struct sigaction act, old;
	int code;
	/*
	 * The result must be volatile, else C compiler might delay
	 * division until after sigaction() restores old handler.
	 */
	volatile int result;

	/*
	 * Save fpe_env so that fpe_handler() can jump back here.
	 * sigsetjmp() returns zero.
	 */
	code = sigsetjmp(fpe_env, 1);
	if (code == 0) {
		/* Install fpe_handler() to trap SIGFPE. */
		act.sa_sigaction = fpe_handler;
		sigemptyset(&amp;act.sa_mask);
		act.sa_flags = SA_SIGINFO;
		if (sigaction(SIGFPE, &amp;act, &amp;old) &lt; 0) {
			perror(&quot;sigaction&quot;);
			exit(1);
		}

		/* Do division. */
		result = x / y;

		/*
		 * Restore old hander, so that SIGFPE cannot jump out
		 * of a call to printf(), which might cause trouble.
		 */
		if (sigaction(SIGFPE, &amp;old, NULL) &lt; 0) {
			perror(&quot;sigaction&quot;);
			exit(1);
		}

		printf(&quot;%d / %d is %d\n&quot;, x, y, result);
	} else {
		/*
		 * We caught SIGFPE. Our fpe_handler() jumped to our
		 * sigsetjmp() and passes a nonzero code.
		 *
		 * But first, restore old handler.
		 */
		if (sigaction(SIGFPE, &amp;old, NULL) &lt; 0) {
			perror(&quot;sigaction&quot;);
			exit(1);
		}

		/* FPE_FLTDIV should never happen with integers. */
		switch (code) {
		case FPE_INTDIV: /* integer division by zero */
		case FPE_FLTDIV: /* float division by zero */
			printf(&quot;%d / %d: caught division by zero!\n&quot;, x, y);
			break;
		default:
			printf(&quot;%d / %d: caught mysterious error!\n&quot;, x, y);
			break;
		}
	}
}

/* Try some division. */
int
main()
{
	try_division(-44, 0);
	try_division(-44, 5);
	try_division(0, 5);
	try_division(0, 0);
	try_division(INT_MIN, -1);
	return 0;
}
