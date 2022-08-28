D
#ifndef objects_h
#define objects_h

typedef struct Duck
{
    int x;
    int y;
    int life;
} Duck;

typedef struct Target
{
    int x;
    int y;
    char character;
    int color;
    int isTargetApproached;
} Target;

typedef struct Object
{
    int x;
    int y;
    int index;
    char character;
    int isMissionChar;
    int isObjectApproached;
} Object;

void duckInit(Duck *duck) {
    duck->x = 0;
    duck->y = 0;
    duck->life = 3;
}

void objectInit(Object *object, int size, int* objectIndexArray) {
    int i;
    srand(time(NULL));

    for (i = 0; i < size; i++) {
        object->index = objectIndexArray[i];
        object->character = objectIndexArray[i] - 10 + 'A';
        object->x = 16 + 22 * i;
        object->y = rand() % 134;
        object->isObjectApproached = 0;
        object->isMissionChar = 0;
        object++;
    }
}

int duckApproachedTarget(Duck *duck, Object *object, int size) {
    int i;

    for (i = 0; i < size; i++) {
        if (duck->x - object->x < 8 && duck->x - object->x > -16 && duck->y - object->y < 8 && duck->y - object->y > -16 && object->isObjectApproached == 0) { // I forgot the last condition! 
            object->isObjectApproached = 1;
            if (object->isMissionChar) {
                return 1;
            } else {
                // duck->life = duck->life - 1; 
                // There is another a very interesting bug. I was thinking of designing a health system to give the poor duck two more chances when hitting 
                // obstacles, but very interesting here - this line of code will be excuted for MULTIPLE TIMES for just one hit!!!!! So the health of the 
                // poor duck will quickly reduce from three to zero once she hits an obstacle... 

                // duck->life = 0;
                // I have to give up the feature of health system, and now the poor duck has to be very careful lol. 

                // No need to give it up now! After adding object->isObjectApproached == 0, the health system works! 
                duck->life = duck->life - 1;
            }
        }
        object++;
    }
    return 0;
}

#endif /* objects_h */
