#include <iostream>
#include <ctime>

#ifndef SIZE
    #define SIZE 0x00000008
#endif

class Apple
{
    public:

    int x = 0;
    int y = 0;

    void setpos(int x1, int y1) {
        x = x1;
        y = y1;
    }

    void setrandpos(void) {
        x = rand() % SIZE;
        y = rand() % SIZE;
    }

    void draw(void) {
        std::cout << "@ ";
    }
};

class Snake
{
    public:

    int snakepos[SIZE*SIZE][2];
    char direct = 'd';
    int length = 3;

    Snake(void) {
        /* init X positions*/
        snakepos[0][0] = SIZE / 2;
        snakepos[1][0] = SIZE / 2;
        snakepos[2][0] = SIZE / 2;

        /* init Y positions*/
        snakepos[0][1] = SIZE / 2 - 2;
        snakepos[1][1] = SIZE / 2 - 1;
        snakepos[2][1] = SIZE / 2;
    }

    void move(void) {
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

    void growup(void) {
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

    bool iscollide(void) {
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

    bool iseating(Apple& apple) {
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

    bool inself(void) {
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

    void drawhead(void) {
        switch (direct) {
            case (int) 'w':
                std::cout << "^ ";
                break;
            case (int) 'd':
                std::cout << "> ";
                break;
            case (int) 'a':
                std::cout << "< ";
                break;
            case (int) 's':
                std::cout << "v ";
                break;
        }
    }

    void drawsegment(void) {
        std::cout << "# ";
    }
};

void drawempty(void) {
    std::cout << ". ";
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

void cls(void) {
    system("clear");
}

void initrandom(void) {
    srand((unsigned)time(0));
}

void draw(Apple& apple, Snake& snake)
{
    cls();
    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < SIZE; y++) {
            drawsquare(snake, apple, x, y);
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void changedirect(Snake& snake)
{
    char input;
    std::cin >> input;
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
        default:
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
    initrandom();
    Apple apple;
    Snake snake;
    for (;;) {
        draw(apple,snake);
        changedirect(snake);
        if (snake.iseating(apple)) {
            snake.growup();
            moveapple(apple, snake);
        } else if (snake.iscollide() || snake.inself())
            break;
        else
            snake.move();
    }
    std::cout << "\nGame over\n";
    return 0;
}
