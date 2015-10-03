long long unsigned fib(unsigned n) {    long long unsigned last = 0, this = 1, new, i;
    if (n &lt; 2) return n;
    for (i = 1 ; i &lt; n ; ++i) {
        new = last + this;
        last = this;
        this = new;
    }
    return this;
}
