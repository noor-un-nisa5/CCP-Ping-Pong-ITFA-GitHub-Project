# 🎮 Retro Console Ping Pong Game (C Language)

A lightweight, fast, and classic **Pong game** built using the C programming language.  
This game runs inside the Windows console and uses simple ASCII graphics to show the ball, paddles, and game arena.

---

## 📌 Description

This project is a **2-player Pong game** built in C.  
It uses keyboard inputs to move paddles up and down, updates the ball movement in real-time, detects collisions, and keeps score.  
The game runs in an **infinite loop**, refreshing the screen on each frame to create smooth animation inside the terminal.

Players control their paddles as the ball moves around. If the ball passes a player's paddle, the opponent scores a point.  
The ball also increases speed after each paddle collision, making the game more challenging.

---

## ⭐ Features

- ✔ **Real-time ball movement**
- ✔ **Two-player gameplay**
- ✔ **W/S keys for Player 1**
- ✔ **I/K keys for Player 2**
- ✔ **Ball speed increases on each hit**
- ✔ **Smooth animation using cursor control**
- ✔ **Collision detection for walls and paddles**
- ✔ **Score tracking system**
- ✔ **ASCII graphics (runs on console)**

---

## 🛠 Technologies Used

| Component | Details |
|----------|---------|
| **Language** | C |
| **Libraries** | stdio.h, stdlib.h, conio.h, windows.h, math.h |
| **Platform** | Windows |
| **Compiler** | MinGW-w64 (GCC), MSVC or any Windows C compiler |

These libraries allow:
- `conio.h` → keyboard input  
- `windows.h` → Sleep(), cursor control  
- `math.h` → round()  
- `stdio.h` → printing graphics to console  

---

## ▶ How to Run the Project

### **1. Install a C compiler**
Recommended: **MinGW-w64 (GCC)**  
Download link:  
https://sourceforge.net/projects/mingw-w64/

After installation, make sure `mingw64/bin` is added to your **PATH**.

### **2. Open the project folder in VS Code**

### **3. Compile the code**
Open the terminal in VS Code and type:

```bash
gcc pong.c -o pong.exe

