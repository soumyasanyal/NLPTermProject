#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;stdarg.h&gt;

typedef struct sma_obj {
  double sma;
  double sum;
  int period;
  double *values;
  int lv;
} sma_obj_t;

typedef union sma_result {
  sma_obj_t *handle;
  double sma;
  double *values;
} sma_result_t;

enum Action { SMA_NEW, SMA_FREE, SMA_VALUES, SMA_ADD, SMA_MEAN };
sma_result_t sma(enum Action action, ...)
{
  va_list vl;
  sma_result_t r;
  sma_obj_t *o;
  double v;

  va_start(vl, action);
  switch(action) {
  case SMA_NEW: // args: int period
    r.handle = malloc(sizeof(sma_obj_t));
    r.handle-&gt;sma = 0.0;
    r.handle-&gt;period = va_arg(vl, int);
    r.handle-&gt;values = malloc(r.handle-&gt;period * sizeof(double));
    r.handle-&gt;lv = 0;
    r.handle-&gt;sum = 0.0;
    break;
  case SMA_FREE: // args: sma_obj_t *handle
    r.handle = va_arg(vl, sma_obj_t *);
    free(r.handle-&gt;values);
    free(r.handle);
    r.handle = NULL;
    break;
  case SMA_VALUES: // args: sma_obj_t *handle
    o = va_arg(vl, sma_obj_t *);
    r.values = o-&gt;values;
    break;
  case SMA_MEAN: // args: sma_obj_t *handle
    o = va_arg(vl, sma_obj_t *);
    r.sma = o-&gt;sma;
    break;
  case SMA_ADD: // args: sma_obj_t *handle, double value
    o = va_arg(vl, sma_obj_t *);
    v = va_arg(vl, double);
    if ( o-&gt;lv &lt; o-&gt;period ) {
      o-&gt;values[o-&gt;lv++] = v;
      o-&gt;sum += v;
      o-&gt;sma = o-&gt;sum / o-&gt;lv;
    } else {
      o-&gt;sum -= o-&gt;values[ o-&gt;lv % o-&gt;period];
      o-&gt;sum += v;
      o-&gt;sma = o-&gt;sum / o-&gt;period;
      o-&gt;values[ o-&gt;lv % o-&gt;period ] = v; o-&gt;lv++;
    }
    r.sma = o-&gt;sma;
    break;
  }
  va_end(vl);
  return r;
}
