#define N 100#define MAX_AGE 140
int main()
{
  int ages[N], i;

  for(i=0; i &lt; N; i++) ages[i] = rand()%MAX_AGE;
  counting_sort_mm(ages, N, 0, MAX_AGE);
  for(i=0; i &lt; N; i++) printf(&quot;%d\n&quot;, ages[i]);
  return EXIT_SUCCESS;
}
