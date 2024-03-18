#include "../include/game.h"
#include "../include/snake.h"
#include "../include/apple.h"
  Snake::Snake(void) {
    /* init X positions*/
    snakepos[0][0] = SIZE / 2;
    snakepos[1][0] = SIZE / 2;
    snakepos[2][0] = SIZE / 2;

    /* init Y positions*/
    snakepos[0][1] = SIZE / 2 - 2;
    snakepos[1][1] = SIZE / 2 - 1;
    snakepos[2][1] = SIZE / 2;
  }

  void Snake::move(void) {
    for (int i = 0; i < length-1; i++) {
      snakepos[i][0] = snakepos[i+1][0];
      snakepos[i][1] = snakepos[i+1][1];
    }
    switch (direct){
      case (int) 'w':
        snakepos[length-1][0]--;
        break;
      case (int) 's':
        snakepos[length-1][0]++;
        break;
      case (int) 'a':
        snakepos[length-1][1]--;
        break;
      default:
        snakepos[length-1][1]++;
    }
  }

  void Snake::growup(void) {
    snakepos[length][0] = snakepos[length-1][0];
    snakepos[length][1] = snakepos[length-1][1];
    switch (direct){
      case (int) 'w':
        snakepos[length][0] = snakepos[length-1][0]-1;
        break;
      case (int) 's':
        snakepos[length][0] = snakepos[length-1][0]+1;
        break;
      case (int) 'a':
        snakepos[length][1] = snakepos[length-1][1]-1;
        break;
      default:
        snakepos[length][1] = snakepos[length-1][1]+1;
    }
    length++;
  }

  bool Snake::iscollide(void) {
    if (direct == 'w' && snakepos[length-1][0] == 0)
      return true;
    else if (direct == 's' && snakepos[length-1][0] == SIZE-1)
      return true;
    else if (direct == 'a' && snakepos[length-1][1] == 0)
      return true;
    else if (direct == 'd' && snakepos[length-1][1] == SIZE-1)
      return true;
    return false;
  }

  bool Snake::iseating(Apple& apple) {
    if (direct == 'w' && snakepos[length-1][0]-1 == apple.x && \
      snakepos[length-1][1] == apple.y)
      return true;
    else if (direct == 's' && snakepos[length-1][0]+1 == apple.x && \
      snakepos[length-1][1] == apple.y)
      return true;
    else if (direct == 'a' && snakepos[length-1][1]-1 == apple.y && \
        snakepos[length-1][0] == apple.x)
        return true;
    else if (direct == 'd' && snakepos[length-1][1]+1 == apple.y && \
        snakepos[length-1][0] == apple.x)
        return true;
    return false;
  }

  bool Snake::inself(void) {
    for (int i = 0; i < length-1; i++) {
      if (direct == 'w' && snakepos[length-1][0]-1 == snakepos[i][0] && \
        snakepos[length-1][1] == snakepos[i][1])
        return true;
      else if (direct == 's' && snakepos[length-1][0]+1 == snakepos[i][0] && \
        snakepos[length-1][1] == snakepos[i][1])
        return true;
      else if (direct == 'a' && snakepos[length-1][1]-1 == snakepos[i][1] && \
        snakepos[length-1][0] == snakepos[i][0])
        return true;
      else if (direct == 'd' && snakepos[length-1][1]+1 == snakepos[i][1] && \
        snakepos[length-1][0] == snakepos[i][0])
        return true;
    }
    return false;
  }

  void Snake::drawhead(void) {
    switch (direct) {
      case (int) 'w':
        addch('^' | COLOR_PAIR(2));
        addch(' ');
        break;
      case (int) 'd':
        addch('>' | COLOR_PAIR(2));
        addch(' ');
        break;
      case (int) 'a':
        addch('<' | COLOR_PAIR(2));
        addch(' ');
        break;
      case (int) 's':
        addch('v' | COLOR_PAIR(2));
        addch(' ');
        break;
    }
  }

  void Snake::drawsegment(void) {
    addch('#' | COLOR_PAIR(2));
    addch(' ');
  }
