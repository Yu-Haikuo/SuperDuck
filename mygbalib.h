#include "sprites.h"
#define INPUT                      (KEY_MASK & (~REG_KEYS))

int palette[] = {
RGB(0,0,0), // pure black 0
RGB(31,31,31), // pure white 1
RGB(0,31,31), // light blue 2
RGB(26,26,26), // light grey 3
RGB(9,9,9), // darkest grey 4
RGB(31,31,0), // pure yellow 5
RGB(31,0,0), // pure red 6
RGB(0,0,31), // pure blue 7
RGB(11,8,3), // dark brown 8
RGB(27,27,27), // lightest grey 9
RGB(16,16,16), // dark grey 10
RGB(31,17,17), // light red 11
RGB(31,24,24), // lighter red 12
RGB(27,0,0), // dark red 13
RGB(0,16,0), // darkest green 14
RGB(0,31,0), // pure green 15
RGB(16,31,16), // light green 16
RGB(23,31,23) // lightest green 17
};

void buttonA() {
    
}

void buttonB() {
    
}

void buttonSel(int *pointer) {
    // Set difficulty to 1.
    *pointer = 1;
}

void buttonS(int *pointer) {
    // Set difficulty to 2.
    *pointer = 2;
}

void buttonR() {
    
}

void buttonL() {
    
}

void buttonU() {
    
}

void buttonD() {
    
}

/*
void checkButtonAtStart(int *pointer) {
    u16 buttons = INPUT;
    if ((buttons & KEY_SELECT) == KEY_SELECT)
    {
        // buttonSel(pointer);
		*pointer = 1;
    }
    if ((buttons & KEY_START) == KEY_START)
    {
        // buttonS(pointer);
		*pointer = 2;
    }
}
*/

/*
void checkButtonDuringRuntime(void)
{
	// Gift function to show you how a function that can be called upon button interrupt to detect which button was pressed and run a specific function for each button could look like. You would have to define each buttonA/buttonB/... function yourself.
    u16 buttons = INPUT;
    
    if ((buttons & KEY_A) == KEY_A)
    {
        buttonA();
    }
    if ((buttons & KEY_B) == KEY_B)
    {
        buttonB();
    }
    if ((buttons & KEY_SELECT) == KEY_SELECT)
    {
        buttonSel();
    }
    if ((buttons & KEY_START) == KEY_START)
    {
        buttonS();
    }
    if ((buttons & KEY_RIGHT) == KEY_RIGHT)
    {
        buttonR();
    }
    if ((buttons & KEY_LEFT) == KEY_LEFT)
    {
        buttonL();
    }
    if ((buttons & KEY_UP) == KEY_UP)
    {
        buttonU();
    }
    if ((buttons & KEY_DOWN) == KEY_DOWN)
    {
        buttonD();
    }
}
*/


void fillPalette(void)
{
    int     i;

	// Fill the palette in GBA memory
    for (i = 0; i < NCOLS; i++)
        spritePal[i] = palette[i];
}


void fillSprites(void)
{
    int     i;

	// Load all sprites in GBA memory
    for (i = 0; i < 128*16*16; i++)
        spriteData[i] = (sprites2[i*2+1] << 8) + sprites2[i*2];

	// draw all sprites on screen, but all of them outside of the screen (starting at position (240,160) the bottom right corner of the GBA screen)
    for(i = 0; i < 128; i++)
        drawSprite(0, i, 240,160);
}


void drawSprite(int numb, int N, int x, int y)
{
	// Same as CA2, make specific sprite (based on its name/numb) appear on screen, as slide number N (each sprite needs a different, arbitrary, N >= 0)
    *(unsigned short *)(0x7000000 + 8*N) = y | 0x2000;
    *(unsigned short *)(0x7000002 + 8*N) = x | 0x4000;
    *(unsigned short *)(0x7000004 + 8*N) = numb*8;
}


/*
void drawLaser(void)
{
	// Gift function showing you how to draw an example sprite defined in sprite.h on screen, using drawSprite()
	// Note that this code uses largeer sprites with a palette, so the main code needs to be initialized in graphical mode 2, using:
    //		*(unsigned short *) 0x4000000 = 0x40 | 0x2 | 0x1000;
	// at the beginning of main() in main.c

    switch(lPlat) {
        case 16:
        {
            drawSprite(LASER, NPLATS*3 + 5 + NROCK + NMET, LaserX, LaserY);
            break;
        }
        case 9:
        {
            drawSprite(LASER, NPLATS*2 + 5 + NROCK + NMET, LaserX, LaserY);
            break;
        }
        default:
            break;
    }
}
*/
