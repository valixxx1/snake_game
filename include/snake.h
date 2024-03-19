/* snake.h
 * This is an interface of the class Snake
 * Made by valixxx1 (2024)
 * License - MIT
*/
#ifndef SNAKE_H
#define SNAKE_H
#include "apple.h"
#include "game.h"
class Snake
{
public:
  int snakepos[SIZE*SIZE][2];
  char direct = 'd';
  int length = 3;

  Snake(void);

  void move(void);

  void growup(void);

  bool iscollide(void);

  bool iseating(Apple& apple);

  bool inself(void);

  void drawhead(void);

  void drawsegment(void);
};
#endif
