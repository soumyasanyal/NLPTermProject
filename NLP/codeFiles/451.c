int a;          // a is globalstatic int p;   // p is &quot;locale&quot; and can be seen only from file1.c

extern float v; // a global declared somewhere else

// a &quot;global&quot; function
int code(int arg)
{
  int myp;        // 1) this can be seen only from inside code
                  // 2) In recursive code this variable will be in a 
                  //    different stack frame (like a closure)
  static int myc; // 3) still a variable that can be seen only from
                  //    inside code, but its value will be kept
                  //    among different code calls
                  // 4) In recursive code this variable will be the 
                  //    same in every stack frame - a significant scoping difference
}

// a &quot;local&quot; function; can be seen only inside file1.c
static void code2(void)
{
  v = v * 1.02;    // update global v
  // ...
}
