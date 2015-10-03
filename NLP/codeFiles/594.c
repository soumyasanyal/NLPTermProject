#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;
#include &lt;libxml/parser.h&gt;
#include &lt;libxml/tree.h&gt;

static void print_names(xmlNode *node)
{
  xmlNode *cur_node = NULL;
  for (cur_node = node; cur_node; cur_node = cur_node-&gt;next) {
    if (cur_node-&gt;type == XML_ELEMENT_NODE) {
      if ( strcmp(cur_node-&gt;name, &quot;Student&quot;) == 0 ) {
	xmlAttr *prop = NULL;
	if ( (prop = xmlHasProp(cur_node, &quot;Name&quot;)) != NULL ) {
	  printf(&quot;%s\n&quot;, prop-&gt;children-&gt;content);
	  
	}
      }
    }
    print_names(cur_node-&gt;children);
  }
}

const char *buffer =
  &quot;&lt;Students&gt;\n&quot;
  &quot;  &lt;Student Name=\&quot;April\&quot; Gender=\&quot;F\&quot; DateOfBirth=\&quot;1989-01-02\&quot; /&gt;\n&quot;
  &quot;  &lt;Student Name=\&quot;Bob\&quot; Gender=\&quot;M\&quot;  DateOfBirth=\&quot;1990-03-04\&quot; /&gt;\n&quot;
  &quot;  &lt;Student Name=\&quot;Chad\&quot; Gender=\&quot;M\&quot;  DateOfBirth=\&quot;1991-05-06\&quot; /&gt;\n&quot;
  &quot;  &lt;Student Name=\&quot;Dave\&quot; Gender=\&quot;M\&quot;  DateOfBirth=\&quot;1992-07-08\&quot;&gt;\n&quot;
  &quot;    &lt;Pet Type=\&quot;dog\&quot; Name=\&quot;Rover\&quot; /&gt;\n&quot;
  &quot;  &lt;/Student&gt;\n&quot;
  &quot;  &lt;Student DateOfBirth=\&quot;1993-09-10\&quot; Gender=\&quot;F\&quot; Name=\&quot;&amp;#x00C9;mily\&quot; /&gt;\n&quot;
  &quot;&lt;/Students&gt;\n&quot;;

int main()
{
  xmlDoc *doc = NULL;
  xmlNode *root = NULL;

  doc = xmlReadMemory(buffer, strlen(buffer), NULL, NULL, 0);
  if ( doc != NULL ) {
    root = xmlDocGetRootElement(doc);
    print_names(root);
    xmlFreeDoc(doc);
  }
  xmlCleanupParser();
  return 0;
}
