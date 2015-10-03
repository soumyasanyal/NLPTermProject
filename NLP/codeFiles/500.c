void quick_sort (int *a, int n) {
    if (n &lt; 2)
        return;
    int p = a[n / 2];
    int *l = a;
    int *r = a + n - 1;
    while (l &lt;= r) {
        while (*l &lt; p)
            l++;
        while (*r &gt; p)
            r--;
        if (l &lt;= r) {
            int t = *l;
            *l++ = *r;
            *r-- = t;
        }
    }
    quick_sort(a, r - a + 1);
    quick_sort(l, a + n - l);
}

int main () {
    int a[] = {4, 65, 2, -31, 0, 99, 2, 83, 782, 1};
    int n = sizeof a / sizeof a[0];
    quick_sort(a, n);
    return 0;
}

