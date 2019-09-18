#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void main(argv) {
  int t, junk, i, j, loc;
  int up, down, left, right, direction;
  int oldx, oldy, x, y, w, h, offset, unit;
  int length, c, speed, speedc, score;
  int head,body,grass,food;
  int headfg, headbg, bodyfg, bodybg, grassbg, grassfg, foodfg, foodbg;
  bool running, waiting, fri;
  clock_t loop_b, loop_e;
  int taken_i, delay, delay_c;
  double taken_d;

  srand(time(NULL));  // initialise RNG
  w = 50;             // width
  h = 25;             // height
  running = true;     // Is the game alive?
  speed = 1;          // Event frequency
  speedc = 0;
  delay = 200000;
  taken_i = 0;
  taken_d = 0;
  unit = 4;
  offset = 6;
  score = 0;

  headfg = 15;
  headbg = 0;
  head = 34;

  bodyfg = 14;
  bodybg = 6;
  body = 219;

  grassfg = 10;
  grassbg = 2;
  grass = 219;

  foodfg = 12;
  foodbg = 12;
  food = 219;

  length = unit;

  int *field = malloc(w*h*sizeof(int));
  int *bgfield = malloc(w*h*sizeof(int));
  int *udf = malloc(w*h*sizeof(int));
  for (i=0; i<w*h; i++) {
    field[i] = 0;
    bgfield[i] = rand() %3;
    udf[i] = 1;
  }


  clrscr();

  textbackground(0);
  textcolor(14);

  gotoxy(w+offset,2);
  cprintf("Caterpillar");
  gotoxy(w+offset, 4);
  cprintf("u,w: up");
  gotoxy(w+offset, 5);
  cprintf("k,d: right");
  gotoxy(w+offset, 6);
  cprintf("h,a: left");
  gotoxy(w+offset, 7);
  cprintf("j,s: down");
  gotoxy(w+offset, 8);
  cprintf("q: quit");

  textcolor(3);
  gotoxy(w+offset, 10);
  cprintf("Score: %d", score);  

  _setcursortype(_NOCURSOR);

  direction = rand() %4;     // 0 = d, 1 = u, 2 = l, 3 = r

  x = rand() % w + 1;
  y = rand() % h + 1;

  field[(x-1) + ((y-1)*w)] = length;

  fri = true;

  while (fri) {
    loc = rand() % (w*h);
    if (field[loc] == 0) {
      field[loc] = -1;
      fri = false;
    }
  }

  while (running) {
    //delay_c = delay;
    delay_c = delay - taken_i;
    gotoxy(w+offset, 14);
    cprintf("Delay_i (usec): %d ", delay_c);  
    if (delay_c < 0) delay_c = 0;
    if (delay_c > delay) delay_c = delay;
    gotoxy(w+offset, 15);
    cprintf("Delay_c (usec): %d ", delay_c);  
    usleep(delay_c);  // Timing

    loop_b = clock();

    speedc +=1;

    if ((speedc % speed) == 0) {   // Fire events
      if (kbhit()) {
        t = getch();

        if (t == 'q') {
          running = false;
          gotoxy(x,y);
          textcolor(7);
          textbackground(0);
          putch(head); 
        } else if (t == 'u') {
          if (direction !=0) direction = 1;
        } else if (t == 'j') {
          if (direction !=1) direction = 0;
        } else if (t == 'h') {
          if (direction !=3) direction = 2;
        } else if (t == 'k') {
          if (direction !=2) direction = 3;
        } else if (t == 'w') {
          if (direction !=0) direction = 1;
        } else if (t == 's') {
          if (direction !=1) direction = 0;
        } else if (t == 'a') {
          if (direction !=3) direction = 2;
        } else if (t == 'd') {
          if (direction !=2) direction = 3;
        }  
        while (kbhit())  {
          junk = getch();
        }
      }
      for (i = 0; i<w*h; i++) {
        if (field[i] > 0) {
          field[i] = field[i] - 1;
          udf[i] = 1;
        }

      }

      switch (direction) {
        case 0:
          y = y + 1;
          if (y > h) {
            y = 1;
          }
          break;
        case 1:
          y = y - 1;
          if (y <= 0) {
            y = h;
          }
          break;
        case 2:
          x = x - 1;
          if (x <= 0) {
            x = w;
          }
          break;
        case 3:
          x = x + 1;
          if (x > w) {
            x = 1;
          }
          break;
      }
      if (field[(((y-1) * w) + (x - 1))] < 0) {
        length += unit;
        score += 1000;
        textbackground(0);
        textcolor(3);
        gotoxy(w+offset, 10);
        cprintf("Score: %d", score);  
        for (i = 0; i<w*h; i++) {
          if (field[i] > 0) {
            field[i] = field[i] + unit;
            //udf[i] = 1;
          }
        }
        field[((y-1) * w) + (x-1)] = length;
        udf[((y-1) * w) + (x-1)] = 1;
        fri = true;   
        while (fri) {
          loc = rand() % (w*h);
          if (field[loc] == 0) {
            field[loc] = -1;
            udf[loc] = 1;
            fri = false;
          }
        }
      } else if (field[(((y-1) * w) + (x - 1))] > 0) {
        running = false;

      }
      field[((y-1) * w) + (x-1)] = length;
      udf[((y-1) * w) + (x-1)] = 1;

      for (i = 0; i<w; i++) {
        for (j = 0; j<h; j++) {
          junk = field[(j*w) + i]; 
          if (udf[(j*w) + i] > 0) {
            gotoxy(i+1, j+1);
            if (junk < 0) {
              textcolor(foodfg);
              textbackground(foodbg);
              putch(food);
            } else if (junk == length) {
              textcolor(headfg);
              textbackground(headbg);
              putch(head);
            } else if (junk == 0) {
              textcolor(grassfg);
              textbackground(grassbg);
              putch(176 + bgfield[j*w+i]);
            } else {
              textcolor(bodyfg);
              textbackground(bodybg);
              putch(body);
            }
            udf[(j*w) + i] = 0;
          }

        }
      }
    }
    loop_e = clock();
    taken_d = ((double)(loop_e - loop_b))/CLOCKS_PER_SEC;
    taken_i = (int)(taken_d * 1000000);
    gotoxy(w+offset, 12);
    textbackground(0);
    textcolor(4);
    cprintf("Loop (usec): %d     ", taken_i);  
  }    
  gotoxy(x,y);
  textcolor(7);
  textbackground(0);
  putch(head); 
  clrscr();
  cprintf("Final Score: %d\n", score);
  free(bgfield);
  bgfield = NULL;
  free(udf);
  udf = NULL;
  free(field);
  field = NULL;
}
