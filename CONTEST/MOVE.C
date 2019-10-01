#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void main(argv) {
  int t, junk;
  int x, y, w, h;
  int n, c, e, rc, tries, speed, speedc;
  bool running, waiting, fri;
  clock_t start, stop;
  double elapsed, penalty;

  srand(time(NULL));
  w = 78; // width
  h = 23; // height
  running = true;
  speed = 50;
  clrscr();
  _setcursortype(_NOCURSOR);
  x = rand() % w;
  y = rand() % h;
  speedc = 0;
  fri = true;
  while (running) {
    usleep(50000);
    speedc +=1;
    // timing
      gotoxy(x+1,y+1);
      textcolor(8);
      putch(n); 
      if (kbhit()) {
        t = getch();

        if (t == 'q') {
          running = false;
        } else if (t == 'u') {
          y = y - 1;
          if (y < 0) {
            y = h - y - 1;
          }
        } else if (t == 'j') {
          y = (y + 1) % h;
        } else if (t == 'h') {
          x = x - 1;
          if (x < 0) {
            x = w - x - 1;
          }
        } else if (t == 'k') {
          x = (x + 1) % w;
        }  
        while (kbhit())  {
          junk = getch();
        }
      }
      gotoxy(x+1,y+1);
      n = 'X';
      textcolor(7);
      putch(n); 
  }    
  clrscr();
  //t=getch();
}
