#include "../include/apple.h"
#include "../include/snake.h"
#include "../include/game.h"
#include <ncurses.h>

void drawempty(void) {
  addch('.' | COLOR_PAIR(3));
  addch(' ');
}

void drawsquare(Snake& snake, Apple& apple, int x, int y)
{
  if (apple.x == x && apple.y == y) {
    apple.draw();
    goto exit;
  }
  for (int segment = 0; segment < snake.length; segment++) {
    if (snake.snakepos[segment][0] == x && snake.snakepos[segment][1] == y) {
      if (segment == snake.length-1) {
        snake.drawhead();
        goto exit;
      } else {
        snake.drawsegment();
        goto exit;
      }
    }
  }
  drawempty();
  exit: return;
}

void initrandom(void) {
  std::srand((unsigned)std::time(0));
}

void draw(Apple& apple, Snake& snake)
{
  move(0, 0);
  for (int x = 0; x < SIZE; x++) {
    for (int y = 0; y < SIZE; y++) {
      drawsquare(snake, apple, x, y);
    }
  addch('\n');
  }
  addch('\n');
  refresh();
}

void changedirect(Snake& snake)
{
  int input;
  input = getch();
  switch (input) {
    case 'w':
      if (snake.direct != 's')
        snake.direct = 'w';
      break;
    case 'a':
      if (snake.direct != 'd')
        snake.direct = 'a';
      break;
    case 's':
      if (snake.direct != 'w')
        snake.direct = 's';
      break;
    case 'd':
      if (snake.direct != 'a')
        snake.direct = 'd';
    }
}

void moveapple(Apple& apple, Snake& snake)
{
  for (;;) {
    retry:
    apple.setrandpos();
    for (int i = 0; i < snake.length; i++) {
      if (snake.snakepos[i][0] == apple.x && snake.snakepos[i][1] == apple.y) {
        goto retry;
      }
    }
    goto exit;
  }
  exit: return;
}

int main(void)
{
  initscr();
  move(0, 0);
  cbreak();
  noecho();
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
  halfdelay(1);

  initrandom();
  Apple apple;
  Snake snake;
  for (;;) {
    draw(apple,snake);
    for (int i = 0; i < 5; i++) {
      changedirect(snake);
    }
    if (snake.iseating(apple)) {
      snake.growup();
      moveapple(apple, snake);
    } else if (snake.iscollide() || snake.inself())
      break;
    else
      snake.move();
  }
  draw(apple,snake);
  printw("\nGame over\n");
  cbreak();
  getch();
  endwin();
  return 0;
}
