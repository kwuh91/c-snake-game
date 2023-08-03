#include "stdafx.h"
#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include <Windows.h>

int speedx, speedy;

bool gamestop;

const int width = 40;
const int height = 20;

int x, y, bounces;

enum direction {
    STOP = 0, LEFT, RIGHT, UP, DOWN, UPRIGHT, UPLEFT, DOWNRIGHT, DOWNLEFT, FASTER, SLOWER
};
direction dir;
direction mem;

bool end;

void THE_END() {

}

void draw() {
    system("cls");
    if (!end) {
        for (size_t i = 0; i < width + 3; ++i) {
            std::cout << "=";
        }
        std::cout << std::endl;
        for (size_t i = 0; i < height; ++i) {
            for (size_t j = 0; j < width; ++j) {
                if (j == 0) {
                    std::cout << "||";
                }
                if (j == width - 1) {
                    std::cout << "||";
                } else {
                    if (i == y && j == x) {
                        std::cout << "O";
                    } else {
                        std::cout << " ";
                    }
                }
            }
            std::cout << std::endl;
        }
        for (size_t i = 0; i < width + 3; ++i) {
            std::cout << "=";
        }
        std::cout << std::endl;
        std::cout << "WASD and QEZX for control" << std::endl;
        std::cout << "+ to go faster" << std::endl;
        std::cout << "- to go slower" << std::endl;
        std::cout << "0 to quit" << std::endl;
        std::cout << std::endl;
        std::cout << "Bounces: " << bounces << std::endl;
    } else {
        std::cout << "The end" << std::endl;
        std::cout << "You have bounced " << bounces << " times" << std::endl;
        std::cout << std::endl;
        std::cout << "Press any button to quit" << std::endl;
    }
}

void setup() {
    end = false;
    gamestop = false;
    dir = STOP;
    bounces = 0;
    speedx = 2;
    speedy = 1;
    x = width / 2;
    y = height / 2;
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'w':
                dir = UP;
                break;
            case 'q':
                dir = UPLEFT;
                break;
            case 'e':
                dir = UPRIGHT;
                break;
            case 'z':
                dir = DOWNLEFT;
                break;
            case 'x':
                dir = DOWNRIGHT;
                break;
            case '+':
                dir = FASTER;
                break;
            case '-':
                dir = SLOWER;
                break;
            case '0':
                end = true;
                draw();
                gamestop = true;
                break;
        }
    }
}

void logic() {
    switch (dir) {
        case LEFT:
            x -= speedx;
            break;
        case RIGHT:
            x += speedx;
            break;
        case UP:
            y -= speedy;
            break;
        case DOWN:
            y += speedy;
            break;
        case UPLEFT:
            x -= speedx;
            y -= speedy;
            break;
        case UPRIGHT:
            x += speedx;
            y -= speedy;
            break;
        case DOWNLEFT:
            y += speedy;
            x -= speedx;
            break;
        case DOWNRIGHT:
            y += speedy;
            x += speedx;
            break;
        case FASTER:
            speedx += 2;
            ++speedy;
            dir = mem;
            break;
        case SLOWER:
            if (speedx != 0 && speedy != 0) {
                speedx -= 2;
                --speedy;
                dir = mem;
            }
        default:
            break;
    }
    if (x > width - 1 && dir == RIGHT) {
        x = width - 4;
        dir = LEFT;
        mem = LEFT;
        ++bounces;
    } else if (x > width - 1 && dir == DOWNRIGHT) {
        x -= 3;
        dir = DOWNLEFT;
        mem = DOWNLEFT;
        ++bounces;
    } else if (x > width - 1 && dir == UPRIGHT) {
        x -= 3;
        dir = UPLEFT;
        mem = UPLEFT;
        ++bounces;
    } else if (x < 0 && dir == LEFT) {
        x = 3;
        dir = RIGHT;
        mem = RIGHT;
        ++bounces;
    } else if (x < 0 && dir == DOWNLEFT) {
        x += 3;
        dir = DOWNRIGHT;
        mem = DOWNRIGHT;
        ++bounces;
    } else if (x < 0 && dir == UPLEFT) {
        x += 3;
        dir = UPRIGHT;
        mem = UPRIGHT;
        ++bounces;
    }
    if (y > height - 1 && dir == DOWN) {
        y = height - 3;
        dir = UP;
        mem = UP;
        ++bounces;
    } else if (y > height - 1 && dir == DOWNRIGHT) {
        y -= 2;
        dir = UPRIGHT;
        mem = UPRIGHT;
        ++bounces;
    } else if (y > height - 1 && dir == DOWNLEFT) {
        y -= 2;
        dir = UPLEFT;
        mem = UPLEFT;
        ++bounces;
    } else if (y < 0 && dir == UP) {
        y = 2;
        dir = DOWN;
        mem = DOWN;
        ++bounces;
    } else if (y < 0 && dir == UPRIGHT) {
        y += 2;
        dir = DOWNRIGHT;
        mem = DOWNRIGHT;
        ++bounces;
    } else if (y < 0 && dir == UPLEFT) {
        y += 2;
        dir = DOWNLEFT;
        mem = DOWNLEFT;
        ++bounces;
    }
}

int main() {
    setup();
    while (!gamestop) {
        draw();
        input();
        logic();
        Sleep(10);
    }
    getch();
    return 0;
}
