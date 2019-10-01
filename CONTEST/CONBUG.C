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
  h = 24; // height
  running = true;

  clrscr();
  _setcursortype(_NOCURSOR);
  while (running) {
    // timing
    x = rand() % w;
    y = rand() % h;
    //x = 79;
    //y = 24;
    if (kbhit()) {
      running = false;
    }
    gotoxy(x+1,y+1);
    n = (rand() % 26) + 97;
    rc = (rand() % 6) + 9;
    textcolor(rc);
    putch(n); 
    usleep(50000);
    gotoxy(x+1,y+1);
    textcolor(8);
    putch(n); 

  }    
  clrscr();
  t=getch();
}
