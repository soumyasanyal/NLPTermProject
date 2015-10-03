void number_reversal_game(){
    printf(&quot;Number Reversal Game. Type a number to flip the first n numbers.&quot;);
    printf(&quot;Win by sorting the numbers in ascending order.\n&quot;);
    printf(&quot;Anything besides numbers are ignored.\n&quot;);
    printf(&quot;\t  |1__2__3__4__5__6__7__8__9|\n&quot;);
    int list[9] = {1,2,3,4,5,6,7,8,9};
    shuffle_list(list,9);

    int tries=0;
    unsigned int i;
    int input;

    while(!check_array(list, 9))
    {
        ((tries&lt;10) ? printf(&quot;Round %d :  &quot;, tries) : printf(&quot;Round %d : &quot;, tries));
        for(i=0;i&lt;9;i++)printf(&quot;%d  &quot;,list[i]);
        printf(&quot;  Gimme that number:&quot;);
        while(1)
        {
            //Just keep asking for proper input
            scanf(&quot;%d&quot;, &amp;input);
            if(input&gt;1&amp;&amp;input&lt;10)
                break;

            printf(&quot;\n%d - Please enter a number between 2 and 9:&quot;, (int)input);
        }
        tries++;
        do_flip(list, 9, input);
    }
    printf(&quot;Hurray! You solved it in %d moves!\n&quot;, tries);
}
