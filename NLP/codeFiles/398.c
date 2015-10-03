/* myname.c */
#include &lt;sys/param.h&gt;
#include &lt;sys/sysctl.h&gt;	/* struct kinfo_proc */
#include &lt;err.h&gt;
#include &lt;fcntl.h&gt;	/* O_RDONLY */
#include &lt;kvm.h&gt;
#include &lt;limits.h&gt;	/* _POSIX2_LINE_MAX */
#include &lt;stdio.h&gt;

int
main(int argc, char **argv) {
	extern char *__progname;	/* from crt0.o */

	struct kinfo_proc *procs;
	kvm_t *kd;
	int cnt;
	char errbuf[_POSIX2_LINE_MAX];

	printf(&quot;argv[0]: %s\n&quot;, argv[0]);
	printf(&quot;__progname: %s\n&quot;, __progname);

	kd = kvm_openfiles(NULL, NULL, NULL, KVM_NO_FILES, errbuf);
	if (kd == NULL)
		errx(1, &quot;%s&quot;, errbuf);
	procs = kvm_getprocs(kd, KERN_PROC_PID, getpid(),
	    sizeof procs[0], &amp;cnt);
	if (procs == NULL)
		errx(1, &quot;%s&quot;, kvm_geterr(kd));
	if (cnt != 1)
		errx(1, &quot;impossible&quot;);

	printf(&quot;p_comm: %s\n&quot;, procs[0].p_comm);

	kvm_close(kd);
	return 0;
}
