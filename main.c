// -----------------------------------------------------------------------------
// C-Skeleton to be used with HAM Library from www.ngine.de
// -----------------------------------------------------------------------------
//#include <mygba.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <unistd.h>
#include "gba.h"
#include "mygbalib.h"
#include "sprites.h"
#include "fonts.h"
#include "draw.h"
#include "event.h"
#include "objects.h"
#include "algorithm.h"

#define KEYCNT *(volatile u16*)0x4000132

Duck duck;
Object object[10];

// We will shuffle it later to pick up one as the target and nine as the obstacles. 
int objectIndexArray[20] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29};

int difficulty = 0;
int isFirstTimeRunning = 1;
int isMissionCharAssigned = 0;
int gameStarted = 0;
int isFirstTimeToStart = 1;
int timeLeft = 15;

// int isGameEnsdded = 0;
// Another an interesting point here! If I uncomment and initialize this variable, the game will not run normally. 
// All letters will start to drop in the same line. I guess it is because I am using too many global variables, and 
// the creation of isGameEnded may just overwrite some other bits that are important to other functions. 

int is_Selected_ButtonPushed = 0;
int is_Start_ButtonPushed = 0;
int is_Up_ButtonPushed = 0;
int is_Down_ButtonPushed = 0;
int is_Left_ButtonPushed = 0;
int is_Right_ButtonPushed = 0;
int is_A_ButtonPushed = 0;
int is_B_ButtonPushed = 0;
int is_L_ButtonPushed = 0;
int is_R_ButtonPushed = 0;

// unsigned short* videoBuffer = (unsigned short*)0x6000000;

// -----------------------------------------------------------------------------
// Project Entry Point
// -----------------------------------------------------------------------------

// Define interrupt handler function here. 
void interruptHandler() {
    REG_IME = 0x00;
	if ((REG_IF & INT_BUTTON) == INT_BUTTON) {
        u16 buttons = INPUT;
        int isInput_L_OR_R = ((buttons & KEY_L) == KEY_L) || ((buttons & KEY_R) == KEY_R);
        switch (isInput_L_OR_R)
        {
        case 1:
            checkButtonAtStart();
            break;
        
        default:
            checkButtonDuringRuntime();
            break;
        }
        checkButtonAtStart();
    }

    if ((REG_IF & INT_TIMER0) == INT_TIMER0) {
        if (gameStarted) {
            timeLeft--;
        }
    }

    if ((REG_IF & INT_TIMER1) == INT_TIMER1) {
        int i;

        if (gameStarted) {
            // This is what really makes differences for different level of difficulty. It sets different speed of moving for objects. 
            // And yes it is super easy to create level 3, 4, 5 and so on! Most of the code can just be reused! 
            switch (difficulty) 
            {
            case 1:
                for (i = 0; i < 10; i++) {
                    object[i].y = (object[i].y + 1) % 134;
                }
                break;

            case 2: 
                for (i = 0; i < 10; i++) {
                    object[i].y = (object[i].y + 3) % 134;
                }
                break;

            default:
                break;
            }
        }
    }

    REG_IF = REG_IF;
    REG_IME = 0x01;
}


int main(void) {

    // switch to video mode 3 (240x160 16-bit)
    REG_DISPCNT = (MODE3 | BG2_ENABLE);
    
    // Draw home screen messages. 
	printHomeScreenMessages();
    
    // INT_BUTTON sends interrupt every time player presses the button. 
    REG_IME = 0x0;
	REG_INT = (int)&interruptHandler;
    REG_IE |= INT_BUTTON;
	KEYCNT |= 0x7FFF;
    REG_IME = 0x1;
    
    // INT_TIMER0 sends interrupt every one second. 
    REG_IME = 0x0;
    REG_INT = (int)&interruptHandler;
    REG_IE |= INT_TIMER0;
    REG_IME = 0x1;
    REG_TM0D = 1432;
    REG_TM0CNT |= TIMER_INTERRUPTS | TIMER_FREQUENCY_256 | TIMER_ENABLE;

    // INT_TIMER1 sends interrupt every 0.3 second. 
    REG_IME = 0x0;
    REG_INT = (int)&interruptHandler;
    REG_IE |= INT_TIMER1;
    REG_IME = 0x1;
    REG_TM1D = 46304;
    REG_TM1CNT |= TIMER_INTERRUPTS | TIMER_FREQUENCY_256 | TIMER_ENABLE;


// Main game starts here. 
// -----------------------------------------------------------------------------
    while(1) {
        switch (difficulty) {
        case 1:
            if (isFirstTimeRunning) { //  This is the first time to run this game. 
                // clearScreen(BLACK);
                isFirstTimeRunning = 0;
                is_L_ButtonPushed = 1;

                // I find out if we only run clearScreen() once, the program runs too quick to 
                // go to the next step and there will be some pixels left on the screen lol. 
                // I also notice I cannot use sleep() inside unistd.h, it seems that ARM is quite different. 

                // Oh no I am too stupid... I don't need the first clearScreen()! 
                clearScreen(BLACK); 

            } else if (is_L_ButtonPushed) { // This is a restart game. 
                // clearScreen(BLACK);  
                is_L_ButtonPushed = 0;
                isMissionCharAssigned = 0;
                gameStarted = 0;
                clearScreen(BLACK);
                
            }
            
            char missionChar;
            int missionCharIndex;

            if (isFirstTimeToStart) {
                printStartMessages();

                if (!isMissionCharAssigned) {
                    int arraySize = sizeof(objectIndexArray) / sizeof(objectIndexArray[0]);
                    shuffle(objectIndexArray, arraySize);

                    int objectSize = sizeof(object) / sizeof(object[1]);
                    objectInit(object, objectSize, objectIndexArray);

                    srand(time(NULL));
                    missionCharIndex = rand() % 10;
                    missionChar = objectIndexArray[missionCharIndex] - 10 + 'A';
                    object[missionCharIndex].isMissionChar = 1;
                    isMissionCharAssigned = 1;
                }
                drawSingleCharacter(212, 76, missionChar, RED);
            }
            
            if (gameStarted) {
                if (isFirstTimeToStart) {
                    clearScreen(BLACK);
                    isFirstTimeToStart = 0;
                    timeLeft = 15;
                    duckInit(&duck);
                }
                // Switch to Video Mode 2. 
                *(unsigned short *) 0x4000000 = 0x40 | 0x2 | 0x1000;

                fillPalette();
                fillSprites();
                printTime(&timeLeft);
                printHealth(&duck);
                drawSprite(30, 13, duck.x, duck.y);

                int i;
                for (i = 0; i < 10; i++) {
                    if (!(object[i].isObjectApproached)) {
                        drawSprite(object[i].index, i+14, object[i].x, object[i].y);
                    }
                }

                // Check if the health reaches zero. 
                if (duck.life == 0) {
                    printFailureMessage();

                    // Reset all parameters. 
                    gameStarted = 0;
                    timeLeft = 15;
                    duckInit(&duck);
                    objectInit(object, 10, objectIndexArray);
                    object[missionCharIndex].isMissionChar = 1;
                }

                // Check if the game times out. 
                if (timeLeft == 0) {
                    printFailureMessage();
                    
                    // Reset all parameters. 
                    gameStarted = 0;
                    timeLeft = 15;
                    duckInit(&duck);
                    objectInit(object, 10, objectIndexArray);
                    object[missionCharIndex].isMissionChar = 1;
                }

                // Check if the duck approaches the desired target. If approached, go to difficulty level 2. 
                if (duckApproachedTarget(&duck, object, 10)) {
                    printSuccessMessage_Level_1();

                    // Reset all parameters. 
                    gameStarted = 0;
                    timeLeft = 15;
                    isFirstTimeRunning = 1;
                    isFirstTimeToStart = 1;
                    isMissionCharAssigned = 0;
                    duckInit(&duck);
                    objectInit(object, 10, objectIndexArray);
                    difficulty = 2;

                }
                
            }

            break;

        case 2:
            if (isFirstTimeRunning) { //  This is the first time to run this game. 
                // clearScreen(BLACK);
                isFirstTimeRunning = 0;
                is_R_ButtonPushed = 1;

                // I find out if we only run clearScreen() once, the program runs too quick to 
                // go to the next step and there will be some pixels left on the screen lol. 
                // I also notice I cannot use sleep() inside unistd.h, it seems that ARM is quite different. 

                // Oh I don't need the first clearScreen()! 
                clearScreen(BLACK); 

            } else if (is_R_ButtonPushed) { // This is a restart game. 
                // clearScreen(BLACK);  
                is_R_ButtonPushed = 0;
                isMissionCharAssigned = 0;
                gameStarted = 0;
                clearScreen(BLACK);
                
            }
            
            // char missionChar;
            // int missionCharIndex;

            if (isFirstTimeToStart) {
                printStartMessages();

                if (!isMissionCharAssigned) {
                    int arraySize = sizeof(objectIndexArray) / sizeof(objectIndexArray[0]);
                    shuffle(objectIndexArray, arraySize);

                    int objectSize = sizeof(object) / sizeof(object[1]);
                    objectInit(object, objectSize, objectIndexArray);

                    srand(time(NULL));
                    missionCharIndex = rand() % 10;
                    missionChar = objectIndexArray[missionCharIndex] - 10 + 'A';
                    object[missionCharIndex].isMissionChar = 1;
                    isMissionCharAssigned = 1;
                }
                drawSingleCharacter(212, 76, missionChar, RED);
            }
            
            if (gameStarted) {
                if (isFirstTimeToStart) {
                    clearScreen(BLACK);
                    isFirstTimeToStart = 0;
                    timeLeft = 10;
                    duckInit(&duck);
                }
                // Switch to Video Mode 2. 
                *(unsigned short *) 0x4000000 = 0x40 | 0x2 | 0x1000;

                fillPalette();
                fillSprites();
                printTime(&timeLeft);
                printHealth(&duck);
                drawSprite(30, 13, duck.x, duck.y);

                int i;
                for (i = 0; i < 10; i++) {
                    if (!(object[i].isObjectApproached)) {
                        drawSprite(object[i].index, i+14, object[i].x, object[i].y);
                    }
                }

                // Check if the health reaches zero. 
                if (duck.life == 0) {
                    printFailureMessage();

                    // Reset all parameters. 
                    gameStarted = 0;
                    timeLeft = 10;
                    duckInit(&duck);
                    objectInit(object, 10, objectIndexArray);
                    object[missionCharIndex].isMissionChar = 1;
                }

                // Check if the game times out. 
                if (timeLeft == 0) {
                    printFailureMessage();
                    
                    // Reset all parameters. 
                    gameStarted = 0;
                    timeLeft = 10;
                    duckInit(&duck);
                    objectInit(object, 10, objectIndexArray);
                    object[missionCharIndex].isMissionChar = 1;
                }

                // Check if the duck approaches the desired target. If approached, end the game! 
                if (duckApproachedTarget(&duck, object, 10)) {
                    printSuccessMessage_Level_2();
                    
                    // Reset all parameters. We still need to reset those so we can press L or R to start a new round. 
                    gameStarted = 0;
                    timeLeft = 10;
                    isFirstTimeRunning = 1;
                    isFirstTimeToStart = 1;
                    isMissionCharAssigned = 0;
                    duckInit(&duck);
                    objectInit(object, 10, objectIndexArray);
                    
                    // isGameEnded = 1; // Cannot use it. See comments above. 
                    difficulty = 0; // Finally, we set it back to 0 to get out of the biggggg switch. It's a big project. Everything ends. Yay :D

                }
            }
            
            break;
            
        default:

            break;
        }
    }
	
	return 0;
}

void checkButtonAtStart() {
    u16 buttons = INPUT;
    if ((buttons & KEY_L) == KEY_L)
    {
        clearScreen(BLACK);
        drawEntireString(68, 76, "START LEVEL 1", WHITE);
        difficulty = 1;
        is_L_ButtonPushed = 1;
        clearScreen(BLACK);
    }
    if ((buttons & KEY_R) == KEY_R)
    {
        clearScreen(BLACK);
        drawEntireString(68, 76, "START LEVEL 2", RED);
        difficulty = 2;
        is_R_ButtonPushed = 1;
        clearScreen(BLACK);
    }
}

void checkButtonDuringRuntime(void)
{
	// Gift function to show you how a function that can be called upon button interrupt to detect which button was pressed and run a specific function for each button could look like. You would have to define each buttonA/buttonB/... function yourself.
    u16 buttons = INPUT;
    
    if ((buttons & KEY_A) == KEY_A)
    {

    }
    if ((buttons & KEY_B) == KEY_B)
    {
        
    }
    if ((buttons & KEY_SELECT) == KEY_SELECT)
    {
        
    }
    if ((buttons & KEY_START) == KEY_START)
    {
        gameStarted = 1;
        is_Start_ButtonPushed = 1;
    }
    if ((buttons & KEY_RIGHT) == KEY_RIGHT)
    {
        duck.x = (duck.x + 1) % 224;
        is_Right_ButtonPushed = 1;
    }
    if ((buttons & KEY_LEFT) == KEY_LEFT)
    {
        duck.x = abs(duck.x - 1) % 240;
        is_Left_ButtonPushed = 1;
    }
    if ((buttons & KEY_UP) == KEY_UP)
    {
        duck.y = abs(duck.y - 1) % 160;
        is_Up_ButtonPushed = 1;
    }
    if ((buttons & KEY_DOWN) == KEY_DOWN)
    {
        duck.y = (duck.y + 1) % 134;
        is_Down_ButtonPushed = 1;
    }
}

