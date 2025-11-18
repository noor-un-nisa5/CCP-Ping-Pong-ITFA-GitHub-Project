#include <stdio.h>
#include <stdlib.h>
#include <conio.h>      // Works on Windows with MinGW
#include <windows.h>   // For cursor & Sleep
#include <math.h>

#define WIDTH 60
#define HEIGHT 20

float ballX, ballY;         
int ballDirX, ballDirY;     
int paddle1Y, paddle2Y;     
int score1 = 0, score2 = 0; 
float ballSpeed = 1.0;      

void setupCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = FALSE;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void setup() {
    ballX = WIDTH / 2.0;
    ballY = HEIGHT / 2.0;
    ballDirX = (rand() % 2 == 0) ? 1 : -1;
    ballDirY = (rand() % 2 == 0) ? 1 : -1;
    paddle1Y = paddle2Y = HEIGHT / 2 - 2;
    ballSpeed = 1.0;
}

void draw() {
    COORD cursor = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == 0 || x == WIDTH - 1) {
                printf("|");
            } else if (y == 0 || y == HEIGHT - 1) {
                printf("-");
            } else if (x == (int)round(ballX) && y == (int)round(ballY)) {
                printf("O");
            } else if (x == 2 && y >= paddle1Y && y < paddle1Y + 4) {
                printf("|");
            } else if (x == WIDTH - 3 && y >= paddle2Y && y < paddle2Y + 4) {
                printf("|");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("Player 1: %d\tPlayer 2: %d\n", score1, score2);
}

void input() {
    if (_kbhit()) {
        char key = _getch();
        if (key == 'w' && paddle1Y > 1) paddle1Y--;
        if (key == 's' && paddle1Y < HEIGHT - 5) paddle1Y++;
        if (key == 'i' && paddle2Y > 1) paddle2Y--;
        if (key == 'k' && paddle2Y < HEIGHT - 5) paddle2Y++;
    }
}

void logic() {
    ballX += ballDirX * ballSpeed;
    ballY += ballDirY * ballSpeed;

    if (ballY <= 1) {
        ballY = 1;
        ballDirY *= -1;
    }
    if (ballY >= HEIGHT - 2) {
        ballY = HEIGHT - 2;
        ballDirY *= -1;
    }

    if ((int)round(ballX) == 3 && ballY >= paddle1Y && ballY < paddle1Y + 4) {
        ballDirX *= -1;
        ballX = 3;
        ballSpeed += 0.1;
        if (ballSpeed > 3.0) ballSpeed = 3.0;
    }

    if ((int)round(ballX) == WIDTH - 4 && ballY >= paddle2Y && ballY < paddle2Y + 4) {
        ballDirX *= -1;
        ballX = WIDTH - 4;
        ballSpeed += 0.1;
        if (ballSpeed > 3.0) ballSpeed = 3.0;
    }

    if ((int)round(ballX) <= 0) {
        score2++;
        setup();
    }
    if ((int)round(ballX) >= WIDTH - 1) {
        score1++;
        setup();
    }
}

int main() {
    setupCursor();
    setup();
    while (1) {
        draw();
        input();
        logic();
        Sleep(30);
    }
    return 0;
}
