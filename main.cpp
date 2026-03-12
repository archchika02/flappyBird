#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <fstream>
#include <string>

using namespace std;

// Game Settings
enum GameState { MENU, LEVELS, HELP, HIGHSCORE, GAMEPLAY, GAMEOVER };
GameState currentState = MENU;

const int WIDTH = 40;
const int HEIGHT = 20;
int PIPE_GAP = 6;
int PIPE_DISTANCE = 18; // Increased slightly for wider pipes
int gameSpeed = 50;

// Difficulty settings
enum Difficulty { EASY, MEDIUM, HARD };
Difficulty currentDifficulty = MEDIUM;

// Global Variables
int birdY = HEIGHT / 2;
int birdX = 5;
int score = 0;
int highScore = 0;
bool gameOver = false;

struct Pipe {
    int x;
    int gapY;
};

vector<Pipe> pipes;

// --- Helper Functions ---

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void loadHighScore() {
    ifstream file("highscore.txt");
    if (file.is_open()) {
        file >> highScore;
        file.close();
    }
}

void saveHighScore() {
    if (score > highScore) {
        highScore = score;
        ofstream file("highscore.txt");
        if (file.is_open()) {
            file << highScore;
            file.close();
        }
    }
}

void applyDifficulty() {
    switch (currentDifficulty) {
        case EASY:
            PIPE_GAP = 8;
            gameSpeed = 70;
            break;
        case MEDIUM:
            PIPE_GAP = 6;
            gameSpeed = 50;
            break;
        case HARD:
            PIPE_GAP = 4;
            gameSpeed = 30;
            break;
    }
}

// --- Screens ---

void drawTitle() {
    system("cls");
    cout << "  +o0>+o0>+o0>   +o0>         +o0>+o0>+o0>+o0>   +o0>+o0>+o0>+o0>   +o0>+o0>+o0>+o0>   +o0>         +o0>" << endl;
    cout << "  +o0>           +o0>         +o0>         +o0>  +o0>         +o0>  +o0>         +o0>  +o0>         +o0>" << endl;
    cout << "  +o0>           +o0>         +o0>         +o0>  +o0>         +o0>  +o0>         +o0>  +o0>         +o0>" << endl;
    cout << "  +o0>+o0>+o0>   +o0>         +o0>+o0>+o0>+o0>   +o0>+o0>+o0>+o0>   +o0>+o0>+o0>+o0>   +o0>+o0>+o0>+o0>" << endl;
    cout << "  +o0>           +o0>         +o0>               +o0>               +o0>               +o0>      +o0>" << endl;
    cout << "  +o0>           +o0>         +o0>               +o0>               +o0>               +o0>      +o0>" << endl;
    cout << "  +o0>           +o0>+o0>+o0> +o0>               +o0>               +o0>               +o0>      +o0>" << endl;
    cout << "\n";
    cout << "                              +o0> +o0> +o0>     +o0>     +o0> +o0> +o0>     +o0> +o0> +o0>" << endl;
    cout << "                              +o0>      +o0>     +o0>     +o0>      +o0>     +o0>      +o0>" << endl;
    cout << "                              +o0>      +o0>     +o0>     +o0>      +o0>     +o0>      +o0>" << endl;
    cout << "                              +o0>+o0>+o0>+o0>   +o0>     +o0>+o0>+o0>+o0>   +o0>+o0>+o0>" << endl;
    cout << "                              +o0>      +o0>     +o0>     +o0>      +o0>     +o0>      +o0>" << endl;
    cout << "                              +o0>      +o0>     +o0>     +o0>      +o0>     +o0>      +o0>" << endl;
    cout << "                              +o0>+o0> +o0>      +o0>     +o0>       +o0>    +o0> +o0> +o0>" << endl;
    cout << "\n +o0> (TEXT BASED VERSION) <0o+\n" << endl;
    cout << "      +o0>  H O M E:" << endl;
    cout << "      --------------------" << endl;
    cout << "      1. START" << endl;
    cout << "      2. LEVELS" << endl;
    cout << "      3. HELP" << endl;
    cout << "      4. HIGHEST SCORE" << endl;
    cout << "      5. EXIT" << endl;
    cout << "\n Selection: ";
}

void drawLevels() {
    system("cls");
    cout << "\n\n          +o0>  L E V E L S:" << endl;
    cout << "          --------------------" << endl;
    cout << "          1. EASY" << endl;
    cout << "          2. MEDIUM" << endl;
    cout << "          3. HARD" << endl;
    cout << "\n Current: " << (currentDifficulty == EASY ? "EASY" : (currentDifficulty == MEDIUM ? "MEDIUM" : "HARD")) << endl;
    cout << "\n +o0> Press SPACE BAR to go HOME." << endl;
}

void drawHelp() {
    system("cls");
    cout << "\n\n               I N S T R U C T I O N S" << endl;
    cout << "          ------------------------------------" << endl;
    cout << "\n          +o0>  Controls: Press 'u' to fly up." << endl;
    cout << "\n          +o0>  Goal: Fly through the holes between the pipes." << endl;
    cout << "                When you pass through a hole, you get 1 point." << endl;
    cout << "                Don't hit the pipes or the ground!  <0o+" << endl;
    cout << "\n\n +o0> Press SPACE BAR to go HOME." << endl;
}

void drawHighScore() {
    system("cls");
    cout << "\n\n          +o0>  HIGHEST SCORE:    " << highScore << endl;
    cout << "          ----------------------" << endl;
    cout << "\n\n +o0> Press SPACE BAR to go HOME." << endl;
}

void drawGameOver() {
    system("cls");
    cout << "\n\n" << endl;
    cout << "   *****      *     *     * ******     ******  *        * *****     ****"    << endl;
    cout << "   *         * *    * * * * *          *    *   *      *  *         *   *"    << endl;
    cout << "   *  ****  *   *   *  *  * *****      *    *    *    *   ****      ****"   << endl;
    cout << "   *   * *  ******  *     * *          *    *     *  *    *         *    *"    << endl;
    cout << "   ***** * *      * *     * ******     ******      *      *****     *     *" << endl;
    cout << "\n\n          +o0>  YOUR SCORE: " << score << endl;
    cout << "\n          +o0>  Start a new game? (y/n)" << endl;
}

// --- Game Logic ---

void setupGame() {
    srand(time(0));
    birdY = HEIGHT / 2;
    birdX = 5;
    score = 0;
    gameOver = false;
    pipes.clear();
    pipes.push_back({WIDTH, rand() % (HEIGHT - PIPE_GAP - 2) + 1});
    applyDifficulty();
    system("cls");
}

void drawGame() {
    gotoxy(0, 0);
    // Upper Border
    for (int i = 0; i < WIDTH + 2; i++) cout << "-";
    cout << endl;

    for (int i = 0; i < HEIGHT; i++) {
        cout << "|"; // Left Border
        for (int j = 0; j < WIDTH; j++) {
            // Check for Bird
            if (i == birdY && j >= birdX && j < birdX + 4) {
                string bird = "+o0>";
                cout << bird[j - birdX];
                continue;
            }

            // Check for Pipes (Wider pipes: 3 chars)
            bool isPipe = false;
            for (auto& pipe : pipes) {
                if (j >= pipe.x && j < pipe.x + 3) {
                    if (i < pipe.gapY || i >= pipe.gapY + PIPE_GAP) {
                        cout << "|";
                        isPipe = true;
                        break;
                    }
                }
            }

            if (!isPipe) {
                cout << " ";
            }
        }
        cout << "|" << endl; // Right Border
    }

    // Lower Border
    for (int i = 0; i < WIDTH + 2; i++) cout << "-";
    cout << "\n +o0> | --------------------" << endl;
    cout << "\n +o0> Score: " << score << endl;
}

void updateGame() {
    // Gravity
    birdY++;

    // Move Pipes
    for (int i = 0; i < pipes.size(); i++) {
        pipes[i].x--;
    }

    // Add New Pipes
    if (pipes.back().x <= WIDTH - PIPE_DISTANCE) {
        pipes.push_back({WIDTH, rand() % (HEIGHT - PIPE_GAP - 2) + 1});
    }

    // Remove Old Pipes
    if (pipes[0].x + 3 < 0) {
        pipes.erase(pipes.begin());
        score++;
    }

    // Collision Detection (Wider Bird + Wider Pipes)
    if (birdY < 0 || birdY >= HEIGHT) gameOver = true;
    
    for (auto& pipe : pipes) {
        // Bird X range: [birdX, birdX + 3]
        // Pipe X range: [pipe.x, pipe.x + 2]
        if (birdX + 3 >= pipe.x && birdX <= pipe.x + 2) {
            if (birdY < pipe.gapY || birdY >= pipe.gapY + PIPE_GAP) {
                gameOver = true;
            }
        }
    }

    if (gameOver) {
        saveHighScore();
        currentState = GAMEOVER;
    }
}

int main() {
    hideCursor();
    loadHighScore();
    char input;

    while (true) {
        switch (currentState) {
            case MENU:
                drawTitle();
                input = _getch();
                if (input == '1') { setupGame(); currentState = GAMEPLAY; }
                else if (input == '2') currentState = LEVELS;
                else if (input == '3') currentState = HELP;
                else if (input == '4') { loadHighScore(); currentState = HIGHSCORE; }
                else if (input == '5') { system("cls"); cout << "\n\n   Thanks for playing! Bye!" << endl; return 0; }
                break;

            case LEVELS:
                drawLevels();
                input = _getch();
                if (input == '1') currentDifficulty = EASY;
                else if (input == '2') currentDifficulty = MEDIUM;
                else if (input == '3') currentDifficulty = HARD;
                else if (input == ' ') currentState = MENU;
                break;

            case HELP:
                drawHelp();
                input = _getch();
                if (input == ' ') currentState = MENU;
                break;

            case HIGHSCORE:
                drawHighScore();
                input = _getch();
                if (input == ' ') currentState = MENU;
                break;

            case GAMEPLAY:
                if (_kbhit()) {
                    input = _getch();
                    if (input == 'u' || input == 'U') birdY -= 3;
                }
                updateGame();
                if (currentState == GAMEPLAY) { // Still playing
                    drawGame();
                    Sleep(gameSpeed);
                }
                break;

            case GAMEOVER:
                drawGameOver();
                input = _getch();
                if (input == 'y' || input == 'Y') { setupGame(); currentState = GAMEPLAY; }
                else if (input == 'n' || input == 'N') currentState = MENU;
                break;
        }
    }

    return 0;
}
