#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARACTERS 2000
#define SPLITTING_CHARACTER ","

#define UP_DELTA_X 0
#define UP_DELTA_Y -1

#define DOWN_DELTA_X 0
#define DOWN_DELTA_Y 1

#define LEFT_DELTA_X -1
#define LEFT_DELTA_Y 0

#define RIGHT_DELTA_X 1
#define RIGHT_DELTA_Y 0

#define ROWS 30000
#define COLUMNS 30000

#define START_X 15000
#define START_Y 15000

#define DEFAULT '-'
#define FIRST_CHAR 'c'
#define SECOND_CHAR 'd'
#define INTERSECTION_CHAR 'O'

typedef struct {
    int positionX;
    int positionY;
} Coordinate;

void create_level_map(char** levelMap);
void fill_level_map(char* characters, char** levelMap, char value);
int get_movements_from_string(char* currentMovement);
void substring(char* originalString, char* outputString, int startIndex, int finishIndex);
Coordinate get_deltas_for_direction(char direction);
Coordinate fill_map_in_direction(Coordinate deltaDirection, int times, Coordinate currentPosition, char** levelMap, char value);
int calculate_smallest_distance_from_start(char** levelMap);
int calculate_rectilinear_distance_from_start(Coordinate position);
char get_character_from_counter(int counter);

int main()
{
    FILE* inputFile = fopen("input.txt", "r");
    char textLine[MAX_CHARACTERS];
	char** levelMap = malloc(COLUMNS * sizeof(char *));
    int counter = 0;

    create_level_map(levelMap);
    
    while (fgets(textLine, MAX_CHARACTERS, inputFile) != NULL) {
        fill_level_map(textLine, levelMap, get_character_from_counter(counter));
        ++counter;
    }

    printf("%i\n", calculate_smallest_distance_from_start(levelMap));

    fclose(inputFile);
    return 0;
}

void create_level_map(char** levelMap)
{
	for(int i = 0; i < COLUMNS; i++) {
        levelMap[i] = malloc(ROWS * sizeof(char));

        for(int j = 0; j < ROWS; j++) {
            levelMap[i][j] = 0;
        }
	}

    return;
}

void fill_level_map(char* characters, char** levelMap, char value)
{
    char* currentMovement = strtok(characters, ",");
    char direction;
    char* stringMovements;
    Coordinate currentPosition;
    Coordinate deltaDirection;
    int movements;

    currentPosition.positionX = START_X;
    currentPosition.positionY = START_Y;

    while(currentMovement != NULL) {
        direction = currentMovement[0];
        movements = get_movements_from_string(currentMovement);
        deltaDirection = get_deltas_for_direction(direction);
        currentPosition = fill_map_in_direction(deltaDirection, movements, currentPosition, levelMap, value);
        currentMovement = strtok(NULL, ",");
    }

    return;
}

int get_movements_from_string(char* currentMovement)
{
    char* stringMovement;
    substring(currentMovement, stringMovement, 1, strlen(currentMovement));
    return atoi(stringMovement);
}

void substring(char* originalString, char* outputString, int startIndex, int finishIndex)
{
    int counter = 0;

    for(int i = 0; i < strlen(originalString); i++) {
        if(i >= startIndex && i <= finishIndex) {
            outputString[counter] = originalString[i];
            ++counter;
        }
    }

    outputString[counter] = '\0';
    return;
}

Coordinate get_deltas_for_direction(char direction)
{
    Coordinate delta;

    switch(direction) {
        case 'U' : {
            delta.positionX = UP_DELTA_X;
            delta.positionY = UP_DELTA_Y;
            break;
        }
        case 'D' : {
            delta.positionX = DOWN_DELTA_X;
            delta.positionY = DOWN_DELTA_Y;
            break;
        }
        case 'L' : {
            delta.positionX = LEFT_DELTA_X;
            delta.positionY = LEFT_DELTA_Y;
            break;
        }
        case 'R' : {
            delta.positionX = RIGHT_DELTA_X;
            delta.positionY = RIGHT_DELTA_Y;
            break;
        }
    }

    return delta;
}

Coordinate fill_map_in_direction(Coordinate deltaDirection, int times, Coordinate currentPosition, char** levelMap, char value)
{
    for(int i = 0; i < times; i++) {
        currentPosition.positionX += deltaDirection.positionX;
        currentPosition.positionY += deltaDirection.positionY;
        char before = levelMap[currentPosition.positionY][currentPosition.positionX];

        if(before == FIRST_CHAR && value == SECOND_CHAR) {
            levelMap[currentPosition.positionY][currentPosition.positionX] = INTERSECTION_CHAR;
        }else {
            levelMap[currentPosition.positionY][currentPosition.positionX] = value;
        }
    }

    return currentPosition;
}

int calculate_smallest_distance_from_start(char** levelMap)
{
    Coordinate coordinate;
    int distance;
    int smallestDistance = 2147483647;

    for(int y = 0; y < COLUMNS; y++) {
        for(int x = 0; x < ROWS; x++) {
            if(levelMap[y][x] == INTERSECTION_CHAR) {
                coordinate.positionX = x;
                coordinate.positionY = y;
                distance = calculate_rectilinear_distance_from_start(coordinate);

                if(distance < smallestDistance) {
                    smallestDistance = distance;
                }
            }
        }
    }

    return smallestDistance;
}

int calculate_rectilinear_distance_from_start(Coordinate position)
{
    return abs(START_X - position.positionX) + abs(START_Y - position.positionY);
}

char get_character_from_counter(int counter)
{
    switch(counter) {
        case 0 : return FIRST_CHAR;
        case 1 : return SECOND_CHAR;
    }
}