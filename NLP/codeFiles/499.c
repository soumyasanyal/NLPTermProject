int main(int argc, char **argv){
    //Just need some random numbers. I chose &lt;100
    int list[9];
    int i;
    srand(time(NULL));
    for(i=0;i&lt;9;i++)
        list[i]=rand()%100;


    //Print list, run code and print it again displaying number of moves
    printf(&quot;\nOriginal: &quot;);
    print_array(list, 9);

    int moves = pancake_sort(list, 9, 1);

    printf(&quot;\nSorted: &quot;);
    print_array(list, 9);
    printf(&quot;  - with a total of %d moves\n&quot;, moves);
}
