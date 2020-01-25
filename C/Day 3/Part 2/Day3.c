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

typedef struct {
    int positionX;
    int positionY;
    int steps[2];
    int id;
    int intersection;
    int used;
} Coordinate;

void create_level_map(Coordinate** levelMap);
void fill_level_map(char* characters, Coordinate** levelMap, int counter);
int get_movements_from_string(char* currentMovement);
void substring(char* originalString, char* outputString, int startIndex, int finishIndex);
Coordinate get_deltas_for_direction(char direction);
Coordinate fill_map_in_direction(Coordinate deltaDirection, int times, Coordinate currentPosition, Coordinate** levelMap, int counter);
Coordinate calculate_smallest_distance_from_start(Coordinate** levelMap);
int calculate_total_steps(Coordinate position);
int calculate_rectilinear_distance_from_start(Coordinate position);

int main()
{
    FILE* inputFile = fopen("input.txt", "r");
	Coordinate** levelMap = malloc(COLUMNS * sizeof(Coordinate *));
    int counter = 0;
    char textLine[MAX_CHARACTERS];

    create_level_map(levelMap);
    
    while (fgets(textLine, MAX_CHARACTERS, inputFile) != NULL) {
        fill_level_map(textLine, levelMap, counter);
        ++counter;
    }

    Coordinate coordinate = calculate_smallest_distance_from_start(levelMap);

    printf("%i\n", (coordinate.steps[0] + coordinate.steps[1]));

    fclose(inputFile);
    return 0;
}

void create_level_map(Coordinate** levelMap)
{
	for(int i = 0; i < COLUMNS; i++) {
        levelMap[i] = malloc(ROWS * sizeof(Coordinate));

        for(int j = 0; j < ROWS; j++) {
            Coordinate coordinate;
            coordinate.used = 0;
            coordinate.steps[0] = 0;
            coordinate.steps[1] = 0;
            coordinate.positionX = j;
            coordinate.positionY = i;
            coordinate.intersection = 0;
            levelMap[i][j] = coordinate;
        }
	}

    return;
}

void fill_level_map(char* characters, Coordinate** levelMap, int counter)
{
    char direction;
    char* stringMovements;
    Coordinate currentPosition;
    Coordinate deltaDirection;
    int movements;
    char* currentMovement = strtok(characters, ",");

    currentPosition.positionX = START_X;
    currentPosition.positionY = START_Y;
    currentPosition.intersection = 0;
    currentPosition.steps[0] = 0;
    currentPosition.steps[1] = 0;
    currentPosition.used = 0;

    while(currentMovement != NULL) {
        direction = currentMovement[0];
        movements = get_movements_from_string(currentMovement);
        deltaDirection = get_deltas_for_direction(direction);
        currentPosition = fill_map_in_direction(deltaDirection, movements, currentPosition, levelMap, counter);
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

Coordinate fill_map_in_direction(Coordinate deltaDirection, int times, Coordinate currentPosition, Coordinate** levelMap, int counter)
{
    for(int i = 0; i < times; i++) {
        currentPosition.positionX += deltaDirection.positionX;
        currentPosition.positionY += deltaDirection.positionY;

        Coordinate before = levelMap[currentPosition.positionY][currentPosition.positionX];

        currentPosition.steps[counter] += 1;
        levelMap[currentPosition.positionY][currentPosition.positionX].steps[counter] = currentPosition.steps[counter]; 

        if(counter == 1 && before.used == 1) {
            printf("Insection %i %i %i\n", currentPosition.positionX, currentPosition.positionY, currentPosition.steps[counter]);
            levelMap[currentPosition.positionY][currentPosition.positionX].intersection = 1;
        }else {
            levelMap[currentPosition.positionY][currentPosition.positionX].used = counter + 1;
       
        }
    }

    return currentPosition;
}

Coordinate calculate_smallest_distance_from_start(Coordinate** levelMap)
{
    Coordinate coordinate;
    Coordinate smallestCoordinate;
    int steps;
    int smallestSteps = 2147483647;

    for(int y = 0; y < COLUMNS; y++) {
        for(int x = 0; x < ROWS; x++) {
            if(levelMap[y][x].intersection == 1) {
                coordinate = levelMap[y][x];
                steps = calculate_total_steps(coordinate);

                if(steps < smallestSteps) {
                    smallestSteps = steps;
                    smallestCoordinate = levelMap[y][x];
                }
            }
        }
    }

    return smallestCoordinate;
}

int calculate_total_steps(Coordinate position)
{
    return position.steps[0] + position.steps[1];
}

int calculate_rectilinear_distance_from_start(Coordinate position)
{
    return abs(START_X - position.positionX) + abs(START_Y - position.positionY);
}