#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;math.h&gt;

enum Action { STDDEV, MEAN, VAR, COUNT };

typedef struct stat_obj_struct {
   double sum, sum2;
   size_t num;
   Action action; 
} sStatObject, *StatObject;

StatObject NewStatObject( Action action )
{
  so = malloc(sizeof(sStatObject));
  so-&gt;sum = 0.0;
  so-&gt;sum2 = 0.0;
  so-&gt;num = 0;
  so-&gt;action = action;
  return so;
}
#define FREE_STAT_OBJECT(so) \
   free(so); so = NULL
double stat_obj_value(StatObject so, Action action)
{
  double num, mean, var, stddev;
    
  if (so-&gt;num == 0.0) return 0.0;
  num = so-&gt;num;
  if (action==COUNT) return num;
  mean = so-&gt;sum/num;
  if (action==MEAN) return mean;
  var = so-&gt;sum2/num - mean*mean;
  if (action==VAR) return var;
  stddev = sqrt(var);
  if (action==STDDEV) return stddev;
  return 0;
}

double stat_object_add(StatObject so, double v)
{
  so-&gt;num++;
  so-&gt;sum += v;
  so-&gt;sum2 += v*v;
  return stat_obj_value(so-&gt;action);
}
