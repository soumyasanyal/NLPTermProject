typedef struct{        double real;
        double imag;
} Complex;

Complex add(Complex a, Complex b){
        Complex ans;
        ans.real = a.real + b.real;
        ans.imag = a.imag + b.imag;
        return ans;
}

Complex mult(Complex a, Complex b){
        Complex ans;
        ans.real = a.real * b.real - a.imag * b.imag;
        ans.imag = a.real * b.imag + a.imag * b.real;
        return ans;
}

/* it's arguable that things could be better handled if either
   a.real or a.imag is +/-inf, but that's much work */
Complex inv(Complex a){
        Complex ans;
        double denom = a.real * a.real + a.imag * a.imag;
        ans.real =  a.real / denom;
        ans.imag = -a.imag / denom;
        return ans;
}

Complex neg(Complex a){
        Complex ans;
        ans.real = -a.real;
        ans.imag = -a.imag;
        return ans;
}

Complex conj(Complex a){
        Complex ans;
        ans.real =  a.real;
        ans.imag = -a.imag;
        return ans;
}

void put(Complex c)
{ 
        printf(&quot;%lf%+lfI&quot;, c.real, c.imag);
} 

void complex_ops(void)
{ 
  Complex a = { 1.0,     1.0 };
  Complex b = { 3.14159, 1.2 };
  
  printf(&quot;\na=&quot;);   put(a);
  printf(&quot;\nb=&quot;);   put(b);
  printf(&quot;\na+b=&quot;); put(add(a,b));
  printf(&quot;\na*b=&quot;); put(mult(a,b));
  printf(&quot;\n1/a=&quot;); put(inv(a));
  printf(&quot;\n-a=&quot;);  put(neg(a));
  printf(&quot;\nconj a=&quot;);  put(conj(a));  printf(&quot;\n&quot;);
}
