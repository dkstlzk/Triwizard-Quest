#  The Triwizard Tournament — A C Game Trilogy (Raylib)

> Course Project — Introduction to Computer Science (C Programming)

Welcome to The Triwizard Tournament, a fun set of 3 mini-games inspired by the magical world of Harry Potter.

This project is made using C and  basics of Raylib graphics library. The games are played one after another.

---

##  The 3 Challenges

###  1. Get the Dragon’s Egg
In this game, the player must steal a golden egg from a dragon.
The dragon throws fireballs, and the player has only 3 lives — each hit takes one life.
There are 5 locked gates that can only be opened by collecting keys scattered across the area.

To win:
 -Avoid fireballs
 -Collect all 5 keys
 -Reach the golden egg safely

---

###  2. Snitch Escape
In this game, the player moves around a maze to collect all the golden pellets scattered across the map.
But there’s a catch — two Death Eaters are roaming the maze, trying to catch you!

To win:
 -Collect all the pellets
 -Avoid getting caught by the ghosts
 -If a ghost touches you, it's game over.

---

###  3. The Enchanted Maze
In this final game, you’re dropped into a magical maze where the walls keep moving!
Your goal is to find your way to the exit before time runs out.
The exit position is intelligently relocated based on distance and surrounding walls.

---

##  Controls

The game will display the controls at the start, but here's a quick rundown:
- Arrow Keys – Move around  
- Enter – Confirm, continue. 
- ESC – Quit the game anytime  

The controls are consistent across all three mini-games, ensuring a smooth gameplay experience.

---

##  Game Flow

- Start from the main menu, where you can view the instructions.
- Press ENTER to begin the first challenge.
- Play all three games in sequence regardless of individual outcomes.
- After completing all tasks:
  - If you win all three, you win the Triwizard Cup.
  - If you lose any game, you lose the tournament.
- At the end, you’ll have the option to replay the tournament or exit.

---

##  Tech & Tools

- Language: C  
- Library:  [Raylib](https://www.raylib.com/) (Basic Implementation) 
- Concepts Used: Game Loops, State Machines, Linked Lists, Dynamic Memory Allocation, Basic AI Logic
- Platform: Cross-platform (Windows, Linux)  
- Build Tool: GCC

---

##  How to Run

### 🔹 Prerequisites
- **GCC compiler**
- **Raylib** installed on your system  
- Supported OS: **Windows / Linux**

---

###  Windows (MinGW/MSYS2)
Make sure Raylib is installed and available in your compiler path.
Run this command in file directory of project in MINGW64 MSYS2 terminal

```bash
gcc -o game.exe main.c dragons_egg.c snitch_escape.c enchanted_maze.c \ 
    -lraylib -lopengl32 -lgdi32 -lwinmm
./game.exe 
```

###  Linux (Ubuntu/Debian/Arch)

Install Raylib from source or using a PPA (recommended), or follow Raylib’s official build guide: [Raylib](https://www.raylib.com/)
```bash
sudo apt install libraylib-dev
```

After Raylib is installed, compile:
```bash
gcc -o game main.c dragons_egg.c snitch_escape.c enchanted_maze.c \ 
    -lraylib -lGL -lm -lpthread -ldl -lrt
./game
```

---

Ensure all .c files and ALL_GAMES_H.h are in the same directory.

If Raylib is installed in a custom path, you may need to add -I and -L flags.

Close the game window or press ESC to exit.


---

##  Why This?

This project is a fun way to learn game development by working with basic game mechanics, loops, and controls in C. Plus, it's inspired by the magical world of Harry Potter, making it even more exciting. It’s a simple yet challenging way to test your skills!

---

## Learning Outcomes

- Applied modular programming and header-based abstraction in C
- Implemented basic AI movement and pathfinding logic
- Used dynamic memory allocation and linked lists in real-time gameplay
- Designed a state-machine-driven multi-game system 

---
