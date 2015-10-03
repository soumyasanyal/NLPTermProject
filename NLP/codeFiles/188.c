#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;math.h&gt; /* for NaN */

enum fps_type {
        FPS_CONST = 0,
        FPS_ADD,
        FPS_SUB,
        FPS_MUL,
        FPS_DIV,
        FPS_DERIV,
        FPS_INT,
};

typedef struct fps_t *fps;
typedef struct fps_t {
        int type;
        fps s1, s2;
        double a0;
} fps_t;

fps fps_new()
{
        fps x = malloc(sizeof(fps_t));
        x-&gt;a0 = 0;
        x-&gt;s1 = x-&gt;s2 = 0;
        x-&gt;type = 0;
        return x;
}

/* language limit of C; when self or mutual recursive definition is needed,
 * one has to be defined, then defined again after it's used.  See how
 * sin and cos are defined this way below
 */
void fps_redefine(fps x, int op, fps y, fps z)
{
        x-&gt;type = op;
        x-&gt;s1 = y;
        x-&gt;s2 = z;
}

fps _binary(fps x, fps y, int op)
{
        fps s = fps_new();
        s-&gt;s1 = x;
        s-&gt;s2 = y;
        s-&gt;type = op;
        return s;
}

fps _unary(fps x, int op)
{
        fps s = fps_new();
        s-&gt;s1 = x;
        s-&gt;type = op;
        return s;
}

/* Taking the n-th term of series.  This is where actual work is done. */
double term(fps x, int n)
{
        double ret = 0;
        int i;

        switch (x-&gt;type) {
        case FPS_CONST: return n &gt; 0 ? 0 : x-&gt;a0;
        case FPS_ADD:
                ret = term(x-&gt;s1, n) + term(x-&gt;s2, n); break;

        case FPS_SUB:
                ret = term(x-&gt;s1, n) - term(x-&gt;s2, n); break;

        case FPS_MUL:
                for (i = 0; i &lt;= n; i++)
                        ret += term(x-&gt;s1, i) * term(x-&gt;s2, n - i);
                break;

        case FPS_DIV:
                if (! term(x-&gt;s2, 0)) return NAN;

                ret = term(x-&gt;s1, n);
                for (i = 1; i &lt;= n; i++)
                        ret -= term(x-&gt;s2, i) * term(x, n - i) / term(x-&gt;s2, 0);
                break;

        case FPS_DERIV:
                ret = n * term(x-&gt;s1, n + 1);
                break;

        case FPS_INT:
                if (!n) return x-&gt;a0;
                ret = term(x-&gt;s1, n - 1) / n;
                break;

        default:
                fprintf(stderr, &quot;Unknown operator %d\n&quot;, x-&gt;type);
                exit(1);
        }

        return ret;
}

#define _add(x, y) _binary(x, y, FPS_ADD)
#define _sub(x, y) _binary(x, y, FPS_SUB)
#define _mul(x, y) _binary(x, y, FPS_MUL)
#define _div(x, y) _binary(x, y, FPS_DIV)
#define _integ(x)  _unary(x, FPS_INT)
#define _deriv(x)  _unary(x, FPS_DERIV)

fps fps_const(double a0)
{
        fps x = fps_new();
        x-&gt;type = FPS_CONST;
        x-&gt;a0 = a0;
        return x;
}

int main()
{
        int i;
        fps one = fps_const(1);
        fps fcos = fps_new();           /* cosine */
        fps fsin = _integ(fcos);        /* sine */
        fps ftan = _div(fsin, fcos);    /* tangent */

        /* redefine cos to complete the mutual recursion; maybe it looks
         * better if I said
         *     *fcos = *( _sub(one, _integ(fsin)) );
         */
        fps_redefine(fcos, FPS_SUB, one, _integ(fsin));

        fps fexp = fps_const(1);        /* exponential */
        /* make exp recurse on self */
        fps_redefine(fexp, FPS_INT, fexp, 0);

        printf(&quot;Sin:&quot;);   for (i = 0; i &lt; 10; i++) printf(&quot; %g&quot;, term(fsin, i));
        printf(&quot;\nCos:&quot;); for (i = 0; i &lt; 10; i++) printf(&quot; %g&quot;, term(fcos, i));
        printf(&quot;\nTan:&quot;); for (i = 0; i &lt; 10; i++) printf(&quot; %g&quot;, term(ftan, i));
        printf(&quot;\nExp:&quot;); for (i = 0; i &lt; 10; i++) printf(&quot; %g&quot;, term(fexp, i));

        return 0;
}
