#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;
#include &lt;libxml/parser.h&gt;
#include &lt;libxml/tree.h&gt;

const char *names[] = {
  &quot;April&quot;, &quot;Tam O'Shanter&quot;, &quot;Emily&quot;, NULL
};
const char *remarks[] = {
  &quot;Bubbly: I'm &gt; Tam and &lt;= Emily&quot;,
  &quot;Burns: \&quot;When chapman billies leave the street ...\&quot;&quot;,
  &quot;Short &amp; shrift&quot;, NULL
};

int main()
{
  xmlDoc *doc = NULL;
  xmlNode *root = NULL, *node;
  const char **next;
  int a;

  doc = xmlNewDoc(&quot;1.0&quot;);
  root = xmlNewNode(NULL, &quot;CharacterRemarks&quot;);
  xmlDocSetRootElement(doc, root);

  for(next = names, a = 0; *next != NULL; next++, a++) {
    node = xmlNewNode(NULL, &quot;Character&quot;);
    (void)xmlNewProp(node, &quot;name&quot;, *next);
    xmlAddChild(node, xmlNewText(remarks[a]));
    xmlAddChild(root, node);
  }

  xmlElemDump(stdout, doc, root);

  xmlFreeDoc(doc);
  xmlCleanupParser();
  
  return EXIT_SUCCESS;
}
