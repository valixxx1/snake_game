#include "game.h"
#include "apple.h"

void Apple::setpos(int x1, int y1) {
    x = x1;
    y = y1;
}
void Apple::setrandpos(void) {
  x = std::rand() % SIZE;
  y = std::rand() % SIZE;
}
void Apple::draw(void) {
  addch('@' | COLOR_PAIR(1));
  addch(' ');
}
