#include&lt;stdio.h&gt;#include&lt;stdlib.h&gt;
#include&lt;string.h&gt;

int isBal(char*s,int l){
    signed c=0;
    while(l--)
	if(s[l]==']') ++c;
	else if(s[l]=='[') if(--c&lt;0) break;
    return !c;
}

void shuffle(char*s,int h){
    int x,t,i=h;
    while(i--){
	t=s[x=rand()%h];
	s[x]=s[i];
	s[i]=t;
    }
}

void genSeq(char*s,int n){
    if(n){
	memset(s,'[',n);
	memset(s+n,']',n);
	shuffle(s,n*2);
    }
    s[n*2]=0;
}

void doSeq(int n){
    char s[64],*o=&quot;False&quot;;
    genSeq(s,n);
    if(isBal(s,n*2)) o=&quot;True&quot;;
    printf(&quot;'%s': %s\n&quot;,s,o);
}

int main(){
    int n=0;
    while(n&lt;9) doSeq(n++);
    return 0;
}
