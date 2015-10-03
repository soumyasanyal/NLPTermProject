#include &lt;stdio.h&gt;#include &lt;string.h&gt;
/* note that UID &amp; GID are of type &quot;int&quot; */
typedef char *STRING;
typedef struct{STRING fullname, office, extension, homephone, email; } gecos_t;
typedef struct{STRING account, password; int uid, gid; gecos_t gecos; STRING directory, shell; } passwd_t;

#define GECOS_FMT &quot;%s,%s,%s,%s,%s&quot;
#define PASSWD_FMT &quot;%s:%s:%d:%d:&quot;GECOS_FMT&quot;:%s:%s&quot;

passwd_t passwd_list[]={
  {&quot;jsmith&quot;, &quot;x&quot;, 1001, 1000, /* UID and GID are type int */
    {&quot;Joe Smith&quot;, &quot;Room 1007&quot;, &quot;(234)555-8917&quot;, &quot;(234)555-0077&quot;, &quot;jsmith@rosettacode.org&quot;},
    &quot;/home/jsmith&quot;, &quot;/bin/bash&quot;},
  {&quot;jdoe&quot;, &quot;x&quot;, 1002, 1000,
    {&quot;Jane Doe&quot;, &quot;Room 1004&quot;, &quot;(234)555-8914&quot;, &quot;(234)555-0044&quot;, &quot;jdoe@rosettacode.org&quot;},
    &quot;/home/jdoe&quot;, &quot;/bin/bash&quot;}
};

main(){
/****************************
* Create a passwd text file *
****************************/
  FILE *passwd_text=fopen(&quot;passwd.txt&quot;, &quot;w&quot;);
  int rec_num;
  for(rec_num=0; rec_num &lt; sizeof passwd_list/sizeof(passwd_t); rec_num++)
    fprintf(passwd_text, PASSWD_FMT&quot;\n&quot;, passwd_list[rec_num]);
  fclose(passwd_text);

/********************************
* Load text ready for appending *
********************************/
  passwd_text=fopen(&quot;passwd.txt&quot;, &quot;a+&quot;);
  char passwd_buf[BUFSIZ]; /* warning: fixed length */
  passwd_t new_rec =
      {&quot;xyz&quot;, &quot;x&quot;, 1003, 1000, /* UID and GID are type int */
          {&quot;X Yz&quot;, &quot;Room 1003&quot;, &quot;(234)555-8913&quot;, &quot;(234)555-0033&quot;, &quot;xyz@rosettacode.org&quot;},
          &quot;/home/xyz&quot;, &quot;/bin/bash&quot;};
  sprintf(passwd_buf, PASSWD_FMT&quot;\n&quot;, new_rec);
/* An atomic append without a file lock, 
   Note: wont work on some file systems, eg NFS */
  write(fileno(passwd_text), passwd_buf, strlen(passwd_buf));
  close(passwd_text);

/***********************************************
* Finally reopen and check record was appended *
***********************************************/
  passwd_text=fopen(&quot;passwd.txt&quot;, &quot;r&quot;);
  while(!feof(passwd_text))
    fscanf(passwd_text, &quot;%[^\n]\n&quot;, passwd_buf, &quot;\n&quot;);
  if(strstr(passwd_buf, &quot;xyz&quot;))
    printf(&quot;Appended record: %s\n&quot;, passwd_buf);
}
