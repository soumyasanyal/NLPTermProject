long long unsigned fib(unsigned n) {    return n &lt; 2 ? n : fib(n - 1) + fib(n - 2);
}
