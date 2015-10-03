struct link *first;// ...
struct link *iter;
for(iter = first; iter != NULL; iter = iter-&gt;next) {
  // access data, e.g. with iter-&gt;data
}
