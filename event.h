#ifndef event_h
#define event_h

#include "objects.h"

void printHomeScreenMessages() {
    drawEntireString(2, 2, "ME3241", GREEN);
    drawEntireString(80, 46, "SUPER DUCK", RED);
    drawEntireString(60, 90, "LEVEL 1 PRESS L", BLUE);
    drawEntireString(60, 110, "LEVEL 2 PRESS R", MAGENTA);
    drawEntireString(28, 150, "DEVELOPED BY YU HAIKUO!", WHITE);
}

void printStartMessages() {
    drawEntireString(48, 36, "$$", GREEN);
    drawEntireString(64, 36, "MISSION STARTS", CYAN);
    drawEntireString(176, 36, "$$", GREEN);
    drawEntireString(20, 76, "FIND DESIRED CHARACTER: ", MAGENTA);
    drawEntireString(36, 116, "PRESS       TO ACCEPT", BROWN);
    drawEntireString(84, 116, "START", RED);
}

void printTime(int *timeleft) {
    int onesDigit = *timeleft % 10;
    int tensDigit = (*timeleft / 10) % 10;

    drawSprite(29, 0, 2, 150);  // T
    drawSprite(18, 1, 10, 150); // I
    drawSprite(22, 2, 18, 150); // M
    drawSprite(14, 3, 26, 150); // E
    drawSprite(tensDigit, 4, 42, 150);
    drawSprite(onesDigit, 5, 50, 150);
}

void printHealth(Duck *duck) {
    // I was going to use a heart sprite to show the health status but unfortunately, I guess I don't have enough memory space for it... 
    // You may go to sprites.h and go to line 2638. There would be a detailed explaination. 
    drawSprite(17, 6, 174, 150); // H
    drawSprite(14, 7, 182, 150); // E
    drawSprite(10, 8, 190, 150); // A
    drawSprite(21, 9, 198, 150); // L
    drawSprite(29, 10, 206, 150); // T
    drawSprite(17, 11, 214, 150); // H
    drawSprite(duck->life, 12, 230, 150);
}

void printFailureMessage() {
    // switch to video mode 3 (240x160 16-bit)
    REG_DISPCNT = (MODE3 | BG2_ENABLE);

    // I found another a very interesting thing here. If I do not add clearScreen() here, there would be two defects: 
    // First is the color noise appearing on the screen during switching from video mode 2 to 3. It can be eliminated with clearScreen(). 
    // Second is what really interests me - If I do not add clearScreen(), the lovely duck cannot go back to her original position (0, 0) 
    // while the game restarts IF YOUR FINGER IS STILL ON BUTTON WHEN TIME IS OFF!!! Instead she would go a few steps further based on the 
    // buttons I previously pressed when the game restarts! It seems that there is a backlog in button interrupts when switching the video 
    // mode, and luckily clearScreen() can deal with that!!! :)
    clearScreen(BLACK);

    // Yes in my testing one clearScreen() sometimes is not enough to let the duck go back to her original position... 
    clearScreen(BLACK);

    drawEntireString(48, 48, "YOU      THE GAME!", WHITE);
    drawEntireString(80, 48, "LOST", RED);
    drawEntireString(32, 104, "PRESS START TO RESTART", WHITE);
}

void printSuccessMessage_Level_1() {
    // switch to video mode 3 (240x160 16-bit)
    REG_DISPCNT = (MODE3 | BG2_ENABLE);

    clearScreen(BLACK);
    clearScreen(BLACK);

    drawEntireString(32, 48, "WOW YOU        LEVEL 1", WHITE);
    drawEntireString(96, 48, "PASSED", RED);
    drawEntireString(44, 104, "LET'S GO TO        ", WHITE);
    drawEntireString(140, 104, "LEVEL 2", RED);
}

void printSuccessMessage_Level_2() {
    // switch to video mode 3 (240x160 16-bit)
    REG_DISPCNT = (MODE3 | BG2_ENABLE);

    clearScreen(BLACK);
    clearScreen(BLACK);

    drawEntireString(20, 45, "YAY YOU PASSED ALL LEVELS", RED);
    drawEntireString(28, 97, "$", GREEN);
    drawEntireString(36, 97, "THANK YOU FOR PLAYING", CYAN);
    drawEntireString(204, 97, "$", GREEN);
    drawEntireString(32, 150, "DEVELOPED BY YU HAIKUO", WHITE);
}

#endif /* event_h */