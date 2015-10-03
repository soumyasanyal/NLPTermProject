#include &lt;stdio.h&gt; // Standard IO
#include &lt;stdlib.h&gt; // other stuff
#include &lt;time.h&gt;
#include &lt;string.h&gt;
int main(int argc, const char *argv[]){
	printf(&quot;Hello, Welcome to rock-paper-scissors\nBy The Elite Noob\n&quot;);
	while(1){ // infinite loop :)
		printf(&quot;\n\nPlease type in 1 for Rock, 2 For Paper, 3 for Scissors, 4 to quit\n&quot;);
		srand(time(NULL));
		int user, comp = (rand()%3)+1;
		char line[255];
		fgets(line, sizeof(line), stdin);	
		while(sscanf(line, &quot;%d&quot;, &amp;user) != 1) { //1 match of defined specifier on input line
  			printf(&quot;You have not entered an integer.\n&quot;);
			fgets(line, sizeof(line), stdin);
		}				
		if(user != 1 &amp;&amp; user != 2 &amp;&amp; user != 3  &amp;&amp; user != 4){printf(&quot;Please enter a valid number!\n&quot;);continue;}
		char umove[10], cmove[10];
		if(comp == 1){strcpy(cmove, &quot;Rock&quot;);}else if(comp == 2){strcpy(cmove, &quot;Paper&quot;);}else{strcpy(cmove, &quot;Scissors&quot;);}
		if(user == 1){strcpy(umove, &quot;Rock&quot;);}else if(user == 2){strcpy(umove, &quot;Paper&quot;);}else{strcpy(umove, &quot;Scissors&quot;);}	
		if(user == 4){printf(&quot;Goodbye! Thanks for playing!\n&quot;);break;}
		if((comp == 1 &amp;&amp; user == 3)||(comp == 2 &amp;&amp; user == 1)||(comp == 3 &amp;&amp; user == 2)){
			printf(&quot;Comp Played: %s\nYou Played: %s\nSorry, You Lost!\n&quot;, cmove, umove);
		}else if(comp == user){
				printf(&quot;Comp Played: %s\nYou Played: %s\nYou Tied :p\n&quot;, cmove, umove);}
		else{
			printf(&quot;Comp Played: %s\nYou Played: %s\nYay, You Won!\n&quot;, cmove, umove);
	}}return 1;}

