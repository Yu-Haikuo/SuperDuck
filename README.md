# SuperDuck
## Brief Description

Super Duck is an adventure **Gameboy Advance game** in which the player is acting as a duck who needs to find her target character among the letters that move up and down within a limited time. 

In the beginning, the player uses button `L` or `R` to choose different difficulty levels. After the player confirms his/her choice, there will be a mission briefing that introduces the mission character. When the player presses `START` to enter the game, a lovely duck will appear at the top left of the window, and the other ten letters move from top to bottom. In level two letters are moving at a higher speed, and the given time is also reduced. 

The player uses arrow keys to control the movement of the duck to avoid hitting obstacles and approach the desired character. Once the duck hits the obstacles three times or the game times out, there will be a game lost page that allows the player to replay the game. After the player successfully approaches the target, the game will print a welcome message, and then directs the player to difficulty level two or the final thank you page. The player is also able to restart a new mission at any time by pressing `L` or `R` during game runtime or when the game ends.

## TeTechnical Aspects Behind

### Main Code Structure and Logic

The whole program consists of a `main.c` file and several `header files`. In the main file, there are several variables, structures, and `objectIndexArray[10]` defined outside the main function as global variables, global structures, and global array. There are also three functions – `interruptHandler()`, `checkButtonAtStart()` and `checkButtonDuringRuntime()` defined in `main.c` as they have to interact with global variables. In the main function, the first thing is to print home screen messages and set `INT_BUTTON`, `INT_TIMER0`, and `INT_TIMER1` interrupts. 

The whole game will be running in a `while (1)` loop. The main function watches and takes global variable difficulty into a `switch` statement, which branches into two cases – **difficulty level 1** and **difficulty level 2**. Each case has the same structure. In each case, the program will first determine whether it is the first time to run this game, or the game is a restarted one and then do the necessary settings. 

After that, it will determine if it is the first time to start the game and if yes, in the same statement the program will determine and assign the randomized mission character. Then, when the game starts (the player presses `START` button), it will do the initialization and keep updating several variables, sprites, duck, and objects, and then print duck, objects, time left, and health status out on screen. 

Meanwhile, if the game times out, or the poor duck hits obstacles three times and her health becomes zero, the game will stop running and print a failure message. If the duck finishes the mission, the program will go to the next difficulty level, or go to the final thank you page according to the current level player is at. The player can also press `L` or `R` button at any time to restart a game with a new randomized character.

### GBA Capabilities Used

- **Interrupt –** `INT_BUTTON`, `INT_TIMER0`, `INT_TIMER1`, and `Interrupt Handler Function`. 
- **Sprites –** `fillPalette()`, `fillSprites()`, and `drawSprite()`.
- **DrawText –** `drawPixelInMode3()`, `drawSingleCharacter()`, `drawEntireString()`, `clearScreen()`. 
- **Algorithm –** `swap()`, `abs()`, `shuffle()`.
- **Other C language capabilities** such as `struct` and `pointer`.

## Screenshots

<p align="center">
    <img height="212" width="242" src="https://github.com/Yu-Haikuo/SuperDuck/blob/main/Images/Capture4.PNG">
    <img height="212" width="242" src="https://github.com/Yu-Haikuo/SuperDuck/blob/main/Images/Capture5.PNG">
    <img height="212" width="242" src="https://github.com/Yu-Haikuo/SuperDuck/blob/main/Images/Capture11.PNG">
</p>

<p align="center">
    <img height="212" width="242" src="https://github.com/Yu-Haikuo/SuperDuck/blob/main/Images/Capture8.PNG">
    <img height="212" width="242" src="https://github.com/Yu-Haikuo/SuperDuck/blob/main/Images/Capture9.PNG">
    <img height="212" width="242" src="https://github.com/Yu-Haikuo/SuperDuck/blob/main/Images/Capture7.PNG">
</p>
