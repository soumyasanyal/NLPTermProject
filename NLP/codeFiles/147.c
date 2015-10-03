void runCode(char *code){
    int c_len = strlen(code);
    int i, accumulator, bottles;
    for(i=0;i&lt;c_len;i++)
    {
        switch(code[i])
        {
            case 'Q':
                printf(&quot;%s\n&quot;, code);
                break;

            case 'H':
                printf(&quot;Hello, world!\n&quot;);
                break;

            case '9':
                //Nice bottles song alg. from RC :)
                bottles = 99;
                do {
                    printf(&quot;%d bottles of beer on the wall\n&quot;, bottles);
                    printf(&quot;%d bottles of beer\n&quot;, bottles);
                    printf(&quot;Take one down, pass it around\n&quot;);
                    printf(&quot;%d bottles of beer on the wall\n\n&quot;, --bottles);
                } while( bottles &gt; 0 );
                break;

            case '+':
                //Am I the only one finding this one weird? :o
                accumulator++;
                break;
        }
    }
};
