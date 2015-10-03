#include&lt;stdio.h&gt;
int main()
{
	char ch, str[100];
	int i;
	
	do{
		printf(&quot;\nEnter the string :&quot;);
		fgets(str,100,stdin);
		for(i=0;str[i]!=00;i++)
		{
			if(str[i]=='#'||str[i]==';')
			{
				str[i]=00;
				break;
			}
		}
		printf(&quot;\nThe modified string is : %s&quot;,str);
		printf(&quot;\nDo you want to repeat (y/n): &quot;);
		scanf(&quot;%c&quot;,&amp;ch);
		fflush(stdin);
	}while(ch=='y'||ch=='Y');
	
	return 0;
}
