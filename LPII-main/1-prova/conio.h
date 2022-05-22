#ifndef __CONIO_H
#define __CONIO_H

#ifndef __CURSES_H
#include <curses.h>
#endif

#define BLACK         0
#define RED           1
#define GREEN         2
#define BROWN         3
#define BLUE          4
#define MAGENTA       5
#define CYAN          6
#define LIGHTGRAY     7
#define DARKGRAY      8
#define LIGHTRED      9
#define LIGHTGREEN    10
#define YELLOW        11
#define LIGHTBLUE     12
#define LIGHTMAGENTA  13
#define LIGHTCYAN     14
#define WHITE         15

int initconio(void);
int endconio(void);
int clrscr(void);
int clreol(void);
int textcolor(int color);
int textbackground(int color);
int getche(void);
int wherex(void);
int wherey(void);
int gotoxy(int x, int y);
int newline(void);
short cur_pair, cur_bold;

int initconio(void)
{
  short f, b, p;
  initscr();
  start_color();
  noecho();
  p = 1;
  for(f = 0; f < 8; f++)
    for(b = 0; b < 8; b++, p++)
      init_pair(p, f, b);
  cur_pair = 57;
  cur_bold = 0;
  color_set(cur_pair, NULL);
  attroff(A_BOLD);
  return 0;
}

int endconio(void)
{
  endwin();
  return 0;
}

int clrscr(void)
{
  bkgdset(COLOR_PAIR(cur_pair));
  if(cur_bold == 0)
    attroff(A_BOLD);
  else
    attron(A_BOLD);
  clear();
  return 0;
}

int clreol(void)
{
  int cur_x, x, y, maxx;
  color_set(cur_pair, NULL);
  getmaxyx(stdscr, y, maxx);
  cur_x = wherex();
  gotoxy(1, wherey());
  for(x = 1; x <= maxx; x++)
    printw(" ");
  gotoxy(cur_x, wherey() - 1);
  return 0;
}

int textcolor(int color)
{
  short x, y, f, b, p = 1;
  pair_content(cur_pair, &f, &b);
  for(x = 0; x < 8; x++)
    for(y = 0; y < 8; y++, p++)
      if((x == (color%8))&&(y == b))
        cur_pair = p;
  color_set(cur_pair, NULL);
  if(color >= 8)
    cur_bold = 1;
  if(cur_bold == 0)
    attroff(A_BOLD);
  else
    attron(A_BOLD);
  return 0;
}

int textbackground(int color)
{
  short x, y, f, b, p = 1;
  pair_content(cur_pair, &f, &b);
  for(x = 0; x < 8; x++)
    for(y = 0; y < 8; y++, p++)
      if((x == f)&&(y == (color%8)))
        cur_pair = p;
  color_set(cur_pair, NULL);
  return 0;
}

int getche(void)
{
  char c;
  echo();
  c = getch();
  noecho();
  return c;
}

int wherex(void)
{
  int x, y;
  getyx(stdscr, y, x);
  return x + 1;
}

int wherey(void)
{
  int x, y;
  getyx(stdscr, y, x);
  return y + 1;
}

int gotoxy(int x, int y)
{
  move(y - 1, x - 1);
  return 0;
}

int newline(void)
{
  gotoxy(1, wherey() + 1);
  return 0;
}

#endif
