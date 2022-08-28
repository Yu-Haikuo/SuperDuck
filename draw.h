
#ifndef draw_h
#define draw_h

unsigned short* videoBuffer = (unsigned short*)0x6000000;

void drawPixelInMode3(int x, int y, unsigned short color) {
    videoBuffer[y * 240 + x] = color;
}

// Get a pixel from font[], then draw it if it is 1.
void drawSingleCharacter(int left, int top, char letter, unsigned short color) {
    int x, y;
    int draw;

    // Each letter has size of 8 * 8
    for(y = 0; y < 8; y++) {
        for (x = 0; x < 8; x++) {
            // Letter starts from 32, each letter's size is 64.
            draw = font[(letter-32) * 64 + y * 8 + x];
            if (draw) { // If draw = 1, then draw it.
                drawPixelInMode3(left + x, top + y, color);
            }
        }
    }
}

// While str is not empty, continue to fetch character from str to draw.
void drawEntireString(int left, int top, char *str, unsigned short color) {
    int pos = 0;
    while (*str) {
        drawSingleCharacter(left + pos, top, *str++, color);
        pos += 8; // Width for each letter is 8.
    }
}

// Clear screen. 
void clearScreen(unsigned short color) {
	int i, j, k, l, draw;
	for (i = 0; i < 20; i++) { // top
		for (j = 0; j < 30; j++) { // left
			for (k = 0; k < 8; k++) { // y
				for (l = 0; l < 8; l++) { // x
					draw = fullOccupiedCharacter[k * 8 + l];
					if (draw) {
						drawPixelInMode3(j * 8 + l, i * 8 + k, color);
					}
				}
			}
		}
	}
}

#endif /* draw_h */
