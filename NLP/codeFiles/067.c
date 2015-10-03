bool take_it_or_not(){
  int i;
  int cows=0, bulls=0;

  for(i=0; i &lt; 4; i++) {
    if ( number[i] == guess[i] ) {
      bulls++;
    } else if ( strchr(number, guess[i]) != NULL ) {
      cows++;
    }
  }
  move(yp, xp);
  addstr(guess); addch(' ');
  if ( bulls == 4 ) { yp++; return true; }
  if ( (cows==0) &amp;&amp; (bulls==0) ) addch('-');
  while( cows-- &gt; 0 ) addstr(&quot;O&quot;);
  while( bulls-- &gt; 0 ) addstr(&quot;X&quot;);
  yp++;
  if ( yp &gt; LAST_LINE ) {
    yp = LINE_BEGIN;
    xp += 10;
  }
  return false;
}

bool ask_play_again()
{
  int i;

  while(yp-- &gt;= LINE_BEGIN) {
    move(yp, 0); clrtoeol();
  }
  yp = LINE_BEGIN; xp = 0;

  move(21,0); clrtoeol();
  addstr(&quot;Do you want to play again? [y/n]&quot;);
  while(true) {
    int a = getch();
    switch(a) {
    case 'y':
    case 'Y':
      return true;
    case 'n':
    case 'N':
      return false;
    }
  }
}


int main()
{
  bool bingo, again;
  int tries = 0;

  initscr(); cbreak(); noecho();
  clear();

  number[4] = guess[4] = 0;

  mvaddstr(0,0, &quot;I choose a number made of 4 digits (from 1 to 9) without repetitions\n&quot;
                &quot;You enter a number of 4 digits, and I say you how many of them are\n&quot;
                &quot;in my secret number but in wrong position (cows or O), and how many\n&quot;
                &quot;are in the right position (bulls or X)&quot;);
  do {
    move(20,0); clrtoeol(); move(21, 0); clrtoeol();
    srand(time(NULL));
    choose_the_number();
    do {
      ask_for_a_number();
      bingo = take_it_or_not();
      tries++;
    } while(!bingo &amp;&amp; (tries &lt; MAX_NUM_TRIES));
    if ( bingo ) 
      mvaddstrf(20, 0, &quot;You guessed %s correctly in %d attempts!&quot;, number, tries);
    else
      mvaddstrf(20,0, &quot;Sorry, you had only %d tries...; the number was %s&quot;, 
		MAX_NUM_TRIES, number);
    again = ask_play_again();
    tries = 0; 
  } while(again);
  nocbreak(); echo(); endwin();
  return EXIT_SUCCESS;
}
