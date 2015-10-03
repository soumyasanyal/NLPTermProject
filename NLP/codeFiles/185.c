int main(){
  int i,j;
  for (j=1; j&lt;1000; j++) {
    for (i=0; i&lt;j, i++) {
      if (exit_early())
        goto out;
      /* etc. */
    }
  }
out:
  return 0;
}
