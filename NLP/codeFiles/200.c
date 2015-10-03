int gray_encode(int n) {    return n ^ (n &gt;&gt; 1);
}

int gray_decode(int n) {
    int p = n;
    while (n &gt;&gt;= 1) p ^= n;
    return p;
}
