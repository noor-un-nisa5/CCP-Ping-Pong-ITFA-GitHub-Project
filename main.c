#include <stdio.h>  // For input/output functions
#include <stdlib.h> // For rand() function
#include <conio.h> // For _kbhit() and _getch() keyboard input
#include <windows.h> // For Sleep() and cursor control
#include <math.h> // For round() function

// Game window size
#define WIDTH 60
#define HEIGHT 20

// Global variables for ball and paddles
float ballX, ballY;         // Use floating-point for smooth movement
int ballDirX, ballDirY;     // Ball direction (-1 or 1)
int paddle1Y, paddle2Y;     // Paddle positions
int score1 = 0, score2 = 0; // Player scores
float ballSpeed = 1.0;      // Ball speed

//function for the intro of the game
void intro() {
    printf("=====================================\n");
    printf("          RETRO PING PONG GAME           \n");
    printf("=====================================\n");
    printf("Controls:\n");
    printf(" Player 1: W = Up,  S = Down\n");
    printf(" Player 2: I = Up,  K = Down\n");
    printf("-------------------------------------\n");
    printf("Press any key to start the game...\n");
    getch(); // wait for user
}

// Function to hide the console cursor
void setupCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = FALSE; // Hide cursor
    cursorInfo.dwSize = 1; //Minimizing Cursor Size
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// Initialize game: ball position, directions, and paddles
void setup() {
    ballX = WIDTH / 2.0; // Start ball at center X
    ballY = HEIGHT / 2.0;  // Start ball at center Y
    ballDirX = (rand() % 2 == 0) ? 1 : -1; // Random left or right
    ballDirY = (rand() % 2 == 0) ? 1 : -1; // Random up or down
    paddle1Y = paddle2Y = HEIGHT / 2 - 2; // Both paddles centered
    ballSpeed = 1.0; // Reset ball speed
}

// Draw everything on screen
void draw() {
    COORD cursor = {0, 0}; // Reset cursor to top-left corner
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
// Draw the game screen (row by row)
    for (int y = 0; y < HEIGHT; y++) {
    	    // Draw left & right borders
        for (int x = 0; x < WIDTH; x++) {
            if (x == 0 || x == WIDTH - 1) {
                printf("|");
             // Draw top & bottom borders
            } else if (y == 0 || y == HEIGHT - 1) {
                printf("-");
             // Draw the ball
            } else if (x == (int)round(ballX) && y == (int)round(ballY)) {
                printf("O");
            // Draw Player 1 paddle
            } else if (x == 2 && y >= paddle1Y && y < paddle1Y + 4) {
                printf("|");
            // Draw Player 2 paddle
            } else if (x == WIDTH - 3 && y >= paddle2Y && y < paddle2Y + 4) {
                printf("|");
            // Empty space
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    // Display scores
    printf("Player 1: %d\tPlayer 2: %d\n", score1, score2);
}

// Handle keyboard input for paddles
void input() {  
    if (_kbhit()) { // Check if key is pressed
        char key = _getch(); // Read the key
        if (key == 'w' && paddle1Y > 1) paddle1Y--;  // "w" key for upward movement -player 1
        if (key == 's' && paddle1Y < HEIGHT - 5) paddle1Y++; // "s" key for downward movement - player 1
        if (key == 'i' && paddle2Y > 1) paddle2Y--; // "i" key for upward movement - player 2
        if (key == 'k' && paddle2Y < HEIGHT - 5) paddle2Y++; // "k" key for downward movement - player 2
    }
}

// Game physics and movement logic
void logic() {
	// Move ball according to direction and speed
    ballX += ballDirX * ballSpeed;
    ballY += ballDirY * ballSpeed;

    // Top and bottom wall collisions
    if (ballY <= 1) {
        ballY = 1;       // Correct position
        ballDirY *= -1;  // Reverse direction
    }
    if (ballY >= HEIGHT - 2) {
        ballY = HEIGHT - 2; // Correct position
        ballDirY *= -1;     // Reverse direction
    }

    // Paddle collisions
    if ((int)round(ballX) == 3 && ballY >= paddle1Y && ballY < paddle1Y + 4) {
        ballDirX *= -1; // Reverse direction
        ballX = 3;      // Correct position
        ballSpeed += 0.1; // Increase speed
        if (ballSpeed > 3.0) ballSpeed = 3.0; // Limit maximum speed
    }

    if ((int)round(ballX) == WIDTH - 4 && ballY >= paddle2Y && ballY < paddle2Y + 4) {
        ballDirX *= -1; // Reverse direction
        ballX = WIDTH - 4; // Correct position
        ballSpeed += 0.1; // Increase speed
        if (ballSpeed > 3.0) ballSpeed = 3.0; // Limit maximum speed
    }

    // Scoring conditions
    if ((int)round(ballX) <= 0) {
        score2++;
        setup();
    }
    if ((int)round(ballX) >= WIDTH - 1) {
        score1++;
        setup(); //Reset ball
    }
}

int main() {
    setupCursor();
    setup();

    while (score1 < 5 && score2 < 5) {
        draw();
        input();
        logic();
        Sleep(30);
    }

    system("cls");

    if (score1 == 5)
        printf("Player 1 Wins!\n");
    else
        printf("Player 2 Wins!\n");

    return 0;
}