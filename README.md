# Flappy Bird C++ CLI

A text-based Flappy Bird game built in C++ specifically for the Windows Command Line. This project uses the Windows Console API to provide a smooth, flicker-free gaming experience with a robust menu system and persistent high scores.

## Screenshots

| Main Menu | Gameplay | Game Over | High Score | Levels | Instruction
| :---: | :---: | :---: | :---: |
| ![Main Menu](https://via.placeholder.com/300x200?text=Main+Menu) | ![Gameplay](https://via.placeholder.com/300x200?text=Gameplay) | ![Game Over](https://via.placeholder.com/300x200?text=Game+Over) | ![High Score](https://via.placeholder.com/300x200?text=High+Score) | ![Levels](https://via.placeholder.com/300x200?text=Levels) | ![Instruction](https://via.placeholder.com/300x200?text=Instruction) |

## Features

- **Full Menu System**: 
    1. **START**: Jump right into the action.
    2. **LEVELS**: Choose your difficulty (EASY, MEDIUM, HARD).
    3. **HELP**: View instructions and controls.
    4. **HIGHEST SCORE**: Check your personal record.
    5. **EXIT**: Close the game.
- **ASCII Art UI**: Beautifully crafted "FLAPPY BIRD" and "GAME OVER" ASCII art.
- **Persistent High Scores**: Your highest score is saved to `highscore.txt` so you can return and beat it.
- **Dynamic Challenges**: Pipes are 3 characters wide and have random gap heights.
- **Flicker-Free Rendering**: Uses `SetConsoleCursorPosition` for a premium feel in the terminal.

## Controls

- **[u]**: Fly up (Flap).
- **[1-5]**: Navigate Menu.
- **[Space]**: Go Home (from any sub-menu screen).
- **[Y/N]**: Restart or Return to Menu on Game Over.

## How to Build and Run (Windows)

### Prerequisites
- **Visual Studio 2022** (with C++ Desktop Development workload) installed.

### Quick Build
1. Clone this repository.
2. Double-click `compile.bat` in the project folder.
3. Once compilation is complete, run `flappybird.exe`.

### Manual Build
Open the **Developer Command Prompt for VS 2022**, navigate to the project directory, and run:
```cmd
cl main.cpp /Fe:flappybird.exe /EHsc
```
OR

### Build with Dev-C++
1. Open **Dev-C++**.
2. Go to `File` > `Open` and select `main.cpp`.
3. Press **F11** (Compile & Run).

> [!NOTE]
> Ensure your Dev-C++ is configured to use a TDM-GCC or MinGW compiler that supports the Windows API.

