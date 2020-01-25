#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define INPUT_FILE "Day2.txt"
#define MAX_CHARACTERS 2000

int calculate_number_of_integers(char* characters);
void split_upon_commas(char* characters, int* numbers);
void run_operations(int currentPosition, int* numbers);
void handle_addition(int currentPosition, int* numbers);
void handle_multiplication(int currentPosition, int* numbers);
void print_final_state(int* numbers, int count);

int main()
{
    FILE *file = fopen(INPUT_FILE, "r");
    char str[MAX_CHARACTERS];
    char initialState[MAX_CHARACTERS];
    char* finalState;
    int* numbers;
    int totalCount;

    if(file == NULL) {
        return 0;
    }

    while (fgets(str, MAX_CHARACTERS, file) != NULL) {
        strcpy(initialState, str);
        totalCount = calculate_number_of_integers(str);
    }

    numbers = malloc(sizeof(int) * totalCount);

    split_upon_commas(initialState, numbers);

    run_operations(0, numbers);

    finalState = malloc(sizeof(char) * 2 * totalCount);
    
    print_final_state(numbers, totalCount);
}

int calculate_number_of_integers(char* characters)
{
    int sum = 0;
    char* currentInteger = strtok(characters, ",");

    while(currentInteger != NULL) {
        currentInteger = strtok(NULL, ",");
        ++sum;
    }

    return sum;
}

void split_upon_commas(char* characters, int* numbers)
{
    char* currentCharacter = strtok(characters, ",");
    int currentInteger;
    int position = 0;

    while(currentCharacter != NULL) {
        numbers[position] = atoi(currentCharacter);
        ++position;
        currentCharacter = strtok(NULL, ",");
    }
    
    return;
}

void run_operations(int currentPosition, int* numbers)
{
    int opCode = numbers[currentPosition];

    if(opCode == 99) {
        return;
    }

    switch(opCode) {
        case 1 : handle_addition(currentPosition, numbers); break;
        case 2 : handle_multiplication(currentPosition, numbers); break;
        default : printf("Something went wrong! Encountered unexpected opcode"); break;
    }

    currentPosition += 4;
    run_operations(currentPosition, numbers);
}

void handle_addition(int currentPosition, int* numbers)
{
    int firstNum = numbers[numbers[currentPosition + 1]];
    int secondNum = numbers[numbers[currentPosition + 2]];
    int finalPosition = numbers[currentPosition + 3];

    numbers[finalPosition] = firstNum + secondNum;
}

void handle_multiplication(int currentPosition, int* numbers)
{
    int firstNum = numbers[numbers[currentPosition + 1]];
    int secondNum = numbers[numbers[currentPosition + 2]];
    int finalPosition = numbers[currentPosition + 3];

    numbers[finalPosition] = firstNum * secondNum;
}

void print_final_state(int* numbers, int count)
{
    for(int i = 0; i < count; i++) {
        printf("%i,", numbers[i]);
    }
}
