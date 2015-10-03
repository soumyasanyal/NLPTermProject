#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;math.h&gt;

double *cholesky(double *A, int n) {
    double *L = (double*)calloc(n * n, sizeof(double));
    if (L == NULL)
        exit(EXIT_FAILURE);

    for (int i = 0; i &lt; n; i++)
        for (int j = 0; j &lt; (i+1); j++) {
            double s = 0;
            for (int k = 0; k &lt; j; k++)
                s += L[i * n + k] * L[j * n + k];
            L[i * n + j] = (i == j) ?
                           sqrt(A[i * n + i] - s) :
                           (1.0 / L[j * n + j] * (A[i * n + j] - s));
        }

    return L;
}

void show_matrix(double *A, int n) {
    for (int i = 0; i &lt; n; i++) {
        for (int j = 0; j &lt; n; j++)
            printf(&quot;%2.5f &quot;, A[i * n + j]);
        printf(&quot;\n&quot;);
    }
}

int main() {
    int n = 3;
    double m1[] = {25, 15, -5,
                   15, 18,  0,
                   -5,  0, 11};
    double *c1 = cholesky(m1, n);
    show_matrix(c1, n);
    printf(&quot;\n&quot;);
    free(c1);

    n = 4;
    double m2[] = {18, 22,  54,  42,
                   22, 70,  86,  62,
                   54, 86, 174, 134,
                   42, 62, 134, 106};
    double *c2 = cholesky(m2, n);
    show_matrix(c2, n);
    free(c2);

    return 0;
}
