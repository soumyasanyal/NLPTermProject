#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

/* func: our one and only data type; it holds either a pointer to 
   a function call, or an integer.  Also carry a func pointer to
   a potential parameter, to simulate closure                   */
typedef struct func_t *func;
typedef struct func_t {
        func (*func) (func, func), _;
        int num;
} func_t;

func new(func(*f)(func, func), func _) {
        func x = malloc(sizeof(func_t));
        x-&gt;func = f;
        x-&gt;_ = _;       /* closure, sort of */
        x-&gt;num = 0;
        return x;
}

func call(func f, func g) {
        return f-&gt;func(f, g);
}

func Y(func(*f)(func, func)) {
        func _(func x, func y) { return call(x-&gt;_, y); }
        func_t __ = { _ };

        func g = call(new(f, 0), &amp;__);
        g-&gt;_ = g;
        return g;
}

func num(int n) {
        func x = new(0, 0);
        x-&gt;num = n;
        return x;
}

func fac(func f, func _null) {
        func _(func self, func n) {
                int nn = n-&gt;num;
                return nn &gt; 1   ? num(nn * call(self-&gt;_, num(nn - 1))-&gt;num)
                                : num(1);
        }

        return new(_, f);
}

func fib(func f, func _null) {
        func _(func self, func n) {
                int nn = n-&gt;num;
                return nn &gt; 1
                        ? num(  call(self-&gt;_, num(nn - 1))-&gt;num +
                                call(self-&gt;_, num(nn - 2))-&gt;num )
                        : num(1);
        }

        return new(_, f);
}

void show(func n) { printf(&quot; %d&quot;, n-&gt;num); }

int main() {
        int i;
        func f = Y(fac);
        printf(&quot;fac: &quot;);
        for (i = 1; i &lt; 10; i++)
                show( call(f, num(i)) );
        printf(&quot;\n&quot;);

        f = Y(fib);
        printf(&quot;fib: &quot;);
        for (i = 1; i &lt; 10; i++)
                show( call(f, num(i)) );
        printf(&quot;\n&quot;);

        return 0;
}
