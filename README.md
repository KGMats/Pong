# Pong Clone in C with SDL2

<img width="638" height="475" alt="image" src="https://github.com/user-attachments/assets/d9ecf630-81fe-4336-872a-88584861bb9c" />


This project is a classic Pong game created using C and the SDL2 library. It features a simple graphical interface, two-player gameplay controlled by the mouse, and a scoring system.

This project was developed as a simple game to demonstrate the use of the SDL2 library for graphics, event handling, and text rendering.

## Key Features

  * **Graphical User Interface:** A clean and simple game interface built with the SDL2 library.
  * **Two-Player Gameplay:** Control the paddles on either side of the screen using your mouse.
  * **Scoring System:** Keeps track of the score for each player, displayed at the top of the screen.
  * **Basic Physics:** The ball realistically bounces off the paddles and the top and bottom walls.
  * **Custom Font Rendering:** Uses the `SDL2_ttf` library to display scores with a classic DOS-style font.

## Requirements

To build and run this project, you will need:

  * A C compiler (like `gcc`)
  * The `SDL2` library
  * The `SDL2_ttf` library for font rendering

## Installation

1.  **Clone the repository:**

    ```bash
    git clone https://github.com/KGMats/Pong/
    cd Pong
    ```

2.  **Install the dependencies:**
    On a Debian-based Linux distribution (like Ubuntu), you can install the required libraries with the following command:

    ```bash
    sudo apt-get install libsdl2-dev libsdl2-ttf-dev
    ```

3.  **Compile the game:**
    A `Makefile` is included for easy compilation. Simply run the `make` command in the project directory.

    ```bash
    make
    ```

    This will create an executable file named `pong`.

## How to Play

### 1\. Run the Game

To start the game, run the compiled executable from your terminal:

```bash
./pong
```

### 2\. Gameplay

  * The game is paused by default when it starts. **Click the left mouse button** to unpause the ball.
  * Move your mouse on the **left side of the screen** to control the left paddle.
  * Move your mouse on the **right side of the screen** to control the right paddle.
  * The objective is to hit the ball past your opponent's paddle to score a point.

### 3\. Debugging

A debug target is available in the `Makefile` to compile the game with debugging symbols.

```bash
make debug
```

## Project Structure

```
.
├── pong.c              # Main C source code for the game.
├── Makefile            # Makefile for compiling the project.
└── ModernDOS8x16.ttf   # The font file used for rendering the score.
```
