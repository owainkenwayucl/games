#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void main(argv) {
  int t;
  int x, y, w, h;
  int n, c, e, rc, tries;
  bool running, waiting;
  clock_t start, stop;
  double elapsed, penalty;

  srand(time(NULL));
  w = 80; // width
  h = 24; // height - skip last line as printing to 80,25 causes line feed.
  running = true;

  clrscr();
  _setcursortype(_NOCURSOR);
  penalty = 0;
  c = 0; // How many completed

  cprintf("Press the key that matches the character shown,\r\n");
  cprintf("Press 0 to exit.\r\nPress any key to contine.\n");
  t = getch();

  clrscr();
  start = clock();
  while (running) {
    // timing
    x = rand() % w;
    y = rand() % h;
    gotoxy(x+1,y+1);
    n = (rand() % 26) + 97;
    rc = (rand() % 6) + 9;
    textcolor(rc);
    putch(n); 

    waiting = true;
    tries = 0;
    while (waiting) {
       t = getch();
       if (t == n) {
          waiting = false;
          c = c + 1;
          textcolor(8);
          gotoxy(x+1,y+1);
          putch(n); 
       } 
       else if (t == 48) {  // exit on 0 keypress
          running = false;
          waiting = false;
          textcolor(7);     // reset text colour
          gotoxy(x+1,y+1);  // 
          putch(n);         // 

       }
       else {
          tries = tries + 1;
          penalty = penalty + (tries*(0.5));
          if ((tries %2) == 1) {
            textcolor(15);
          } 
          else {
            textcolor(7);
          }
          gotoxy(x+1,y+1);
          putch(n); 
       }
    }
  }    
  stop = clock();
  elapsed = (double)(stop - start) / (double) CLOCKS_PER_SEC;
  clrscr();
  textcolor(7);
  cprintf("Completed %d in %g seconds including %g seconds of penalties.\n", c, elapsed+penalty, penalty);
}
