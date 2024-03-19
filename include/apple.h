/* apple.h
 * This is an interface of the class Apple
 * Made by valixxx1 (2024)
 * License - MIT*/
#ifndef APPLE_H
#define APPLE_H
class Apple
{
public:
  int x = 0;
  int y = 0;

  void setpos(int x1, int y1);
  void setrandpos(void);
  void draw(void);
};
#endif
