#include &lt;stdio.h&gt; 
typedef enum {
  TRITTRUE,  /* In this enum, equivalent to integer value 0 */
  TRITMAYBE, /* In this enum, equivalent to integer value 1 */
  TRITFALSE  /* In this enum, equivalent to integer value 2 */
} trit;
 
/* We can trivially find the result of the operation by passing
   the trinary values as indeces into the lookup tables' arrays. */
trit tritNot[3] = {TRITFALSE , TRITMAYBE, TRITTRUE};
trit tritAnd[3][3] = { {TRITTRUE, TRITMAYBE, TRITFALSE},
                       {TRITMAYBE, TRITMAYBE, TRITFALSE},
                       {TRITFALSE, TRITFALSE, TRITFALSE} };
 
trit tritOr[3][3] = { {TRITTRUE, TRITTRUE, TRITTRUE},
                      {TRITTRUE, TRITMAYBE, TRITMAYBE},
                      {TRITTRUE, TRITMAYBE, TRITFALSE} };
 
trit tritThen[3][3] = { { TRITTRUE, TRITMAYBE, TRITFALSE},
                        { TRITTRUE, TRITMAYBE, TRITMAYBE},
                        { TRITTRUE, TRITTRUE, TRITTRUE } };
 
trit tritEquiv[3][3] = { { TRITTRUE, TRITMAYBE, TRITFALSE},
                         { TRITMAYBE, TRITMAYBE, TRITMAYBE},
                         { TRITFALSE, TRITMAYBE, TRITTRUE } };

/* Everything beyond here is just demonstration */

const char* tritString[3] = {&quot;T&quot;, &quot;?&quot;, &quot;F&quot;};

void demo_binary_op(trit operator[3][3], char* name)
{
  trit operand1 = TRITTRUE; /* Declare. Initialize for CYA */
  trit operand2 = TRITTRUE; /* Declare. Initialize for CYA */

  /* Blank line */
  printf(&quot;\n&quot;);

  /* Demo this operator */
  for( operand1 = TRITTRUE; operand1 &lt;= TRITFALSE; ++operand1 )
  {
    for( operand2 = TRITTRUE; operand2 &lt;= TRITFALSE; ++operand2 )
    {
      printf(&quot;%s %s %s: %s\n&quot;, tritString[operand1],
                               name,
                               tritString[operand2],
                               tritString[operator[operand1][operand2]]);
    }
  }

}

int main()
{
  trit op1 = TRITTRUE; /* Declare. Initialize for CYA */
  trit op2 = TRITTRUE; /* Declare. Initialize for CYA */
 
  /* Demo 'not' */
  for( op1 = TRITTRUE; op1 &lt;= TRITFALSE; ++op1 )
  {
    printf(&quot;Not %s: %s\n&quot;, tritString[op1], tritString[tritNot[op1]]);
  }
  demo_binary_op(tritAnd, &quot;And&quot;);
  demo_binary_op(tritOr, &quot;Or&quot;);
  demo_binary_op(tritThen, &quot;Then&quot;);
  demo_binary_op(tritEquiv, &quot;Equiv&quot;);

 
  return 0;
}
