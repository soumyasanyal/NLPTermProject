int main(void) {
  const char *string = &quot;Hello, world!&quot;;
  size_t length = 0;
  
  const char *p = string;
  while (*p++ != '\0') length++;                                         
  
  return 0;
}
