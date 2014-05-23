#include <ncurses.h>
#include <signal.h>
#include <unistd.h>
#include "tgt.h"

void print_ground(int y);
void print_gtruc(int x, int y);

int main(int argc, char *argv[]) {
  int i, truc_y, ground_y;

  initscr();
  signal(SIGINT, SIG_IGN);
  noecho();
  curs_set(0);
  nodelay(stdscr, TRUE);
  leaveok(stdscr, TRUE);
  scrollok(stdscr, FALSE);

  truc_y   = LINES / 2 - TGT_SIZE - WHL_SIZE;
  ground_y = LINES / 2;

  for(i = -AA_LEN; i < COLS + AA_LEN; i++) {
    clear();
    print_ground(ground_y);
    print_gtruc(i, truc_y);
    refresh();
    usleep(40000);
  }
  endwin();

  return 0;
}

void print_ground(int y) {
  int x;

  for(x = 0; x < COLS; x++) {
    mvaddch(y, x, '-');
  }

  return;
}

void print_gtruc(int x, int y) {
  const char *truc[TGT_SIZE]
    = {TGT_00, TGT_01, TGT_02, TGT_03, TGT_04, TGT_05};
  const char *whl[ANM_SIZE][WHL_SIZE]
    = {{WHL_0_00, WHL_0_01, WHL_0_02},
       {WHL_1_00, WHL_1_01, WHL_1_02},
       {WHL_2_00, WHL_2_01, WHL_2_02},
       {WHL_3_00, WHL_3_01, WHL_3_02}};
  static unsigned whl_ang = 0;
  int i;

  for(i = 0; i < TGT_SIZE; i++) {
    mvaddnstr(y + i, x < 0 ? 0 : x,
              truc[i] + (x < 0 ? -x : 0),
              x < 0 ? AA_LEN + x : COLS - x);
  }
  for(i = 0; i < WHL_SIZE; i++) {
    mvaddnstr(y + TGT_SIZE + i, x < 0 ? 0 : x,
              whl[whl_ang % ANM_SIZE][i] + (x < 0 ? -x : 0),
              x < 0 ? AA_LEN + x : COLS - x);
  }
  whl_ang++;

  return; 
}
