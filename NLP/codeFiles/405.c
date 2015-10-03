int main(){
  size_t i;
  double d = 7.0;
  quaternion_t *q[3];
  quaternion_t *r  = quaternion_new();

  quaternion_t *qd = quaternion_new_set(7.0, 0.0, 0.0, 0.0);
  q[0] = quaternion_new_set(1.0, 2.0, 3.0, 4.0);
  q[1] = quaternion_new_set(2.0, 3.0, 4.0, 5.0);
  q[2] = quaternion_new_set(3.0, 4.0, 5.0, 6.0);

  printf(&quot;r = %lf\n&quot;, d);
  
  for(i = 0; i &lt; 3; i++) {
    printf(&quot;q[%u] = &quot;, i);
    quaternion_print(q[i]);
    printf(&quot;abs q[%u] = %lf\n&quot;, i, quaternion_norm(q[i]));
  }

  printf(&quot;-q[0] = &quot;);
  quaternion_neg(r, q[0]);
  quaternion_print(r);

  printf(&quot;conj q[0] = &quot;);
  quaternion_conj(r, q[0]);
  quaternion_print(r);

  printf(&quot;q[1] + q[2] = &quot;);
  quaternion_add(r, q[1], q[2]);
  quaternion_print(r);

  printf(&quot;q[2] + q[1] = &quot;);
  quaternion_add(r, q[2], q[1]);
  quaternion_print(r);
  

  printf(&quot;q[0] * r = &quot;);
  quaternion_mul_d(r, q[0], d);
  quaternion_print(r);

  printf(&quot;q[0] * (r, 0, 0, 0) = &quot;);
  quaternion_mul(r, q[0], qd);
  quaternion_print(r);
  

  printf(&quot;q[1] * q[2] = &quot;);
  quaternion_mul(r, q[1], q[2]);
  quaternion_print(r);

  printf(&quot;q[2] * q[1] = &quot;);
  quaternion_mul(r, q[2], q[1]);
  quaternion_print(r);  


  free(q[0]); free(q[1]); free(q[2]); free(r);
  return EXIT_SUCCESS;
}
