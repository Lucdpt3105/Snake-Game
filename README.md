# 🐍 Console Snake Game in C++

This is a simple **console-based Snake game** written in C++ for Windows. It uses basic libraries like `<iostream>`, `<conio.h>`, and `<thread>` to simulate real-time gameplay in the terminal.

## 🎮 Gameplay

- Use the **W A S D** keys to control the snake:
  - `W`: Move Up
  - `A`: Move Left
  - `S`: Move Down
  - `D`: Move Right
- Eat the fruit (`F`) to gain points (`+10` per fruit).
- Avoid running into walls — if you hit the border, the game ends.
- Press `X` to exit the game early.

## 🧠 Features

- Real-time keyboard input with `_kbhit()` and `_getch()`
- Fruit spawns randomly inside the grid
- Increasing difficulty as score increases (reduced delay per frame)
- Simple clean rendering using ASCII graphics

## 🛠 Requirements

- Windows OS (uses `<conio.h>`)
- C++ compiler (tested with MSVC / g++)
- Run in a terminal or console that supports `system("cls")`

## 🧾 How to Run

1. **Clone the repository**:
   ```bash
   git clone https://github.com/your-username/snake-game-cpp.git
   cd snake-game-cpp
