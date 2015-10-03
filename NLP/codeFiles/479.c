void insert_append (link *anchor, link *newlink) {  newlink-&gt;next = anchor-&gt;next;
  anchor-&gt;next = newlink;
}
