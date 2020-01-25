#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define INPUT_FILE "Day5.txt"
#define MAX_CHARACTERS 5000

int run_computer();
int calculate_number_of_integers(char* characters);
void split_upon_commas(char* characters, int* numbers);
void run_operations(int currentPosition, int* numbers);
int caluclate_modes_and_new_opcode(int opCode, int* modes);
void handle_addition(int currentPosition, int* numbers, int* mode);
int get_modal_value(int* numbers, int position, int mode);
void handle_multiplication(int currentPosition, int* numbers, int* mode);
void handle_input(int currentPosition, int* numbers);
void handle_output(int currentPosition, int* numbers, int* mode);
int handle_jump_if_true(int currentPosition, int* numbers, int* modes);
int handle_jump_if_false(int currentPosition, int* numbers, int* modes);
void handle_less_than_computation(int currentPosition, int* numbers, int* modes);
void handle_equals_computation(int currentPosition, int* numbers, int* modes);

int main()
{
    printf("%i\n", run_computer());

    //printf("%i\n", run_computer());
    // FILE* output = fopen("output.txt", "w");

    // for(int verb = 0; verb < 100; verb++) {
    //     int answer = run_computer(76, verb);

    //     fprintf(output, "Noun %i Verb %i -> Answer: %i\n", 76, verb, answer);
    // }

    // fclose(output);
    return 0;
}

int run_computer()
{
    FILE *file = fopen(INPUT_FILE, "r");
    char str[MAX_CHARACTERS];
    char initialState[MAX_CHARACTERS];
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

    return numbers[0];
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

    int modes[10];
    opCode = caluclate_modes_and_new_opcode(opCode, modes);

    switch(opCode) {
        case 1 : handle_addition(currentPosition, numbers, modes); currentPosition += 4; break;
        case 2 : handle_multiplication(currentPosition, numbers, modes); currentPosition += 4; break;
        case 3 : handle_input(currentPosition, numbers); currentPosition += 2; break;
        case 4 : handle_output(currentPosition, numbers, modes); currentPosition += 2; break;
        case 5 : currentPosition = handle_jump_if_true(currentPosition, numbers, modes); break;
        case 6 : currentPosition = handle_jump_if_false(currentPosition, numbers, modes); break;
        case 7 : handle_less_than_computation(currentPosition, numbers, modes); currentPosition += 4; break;
        case 8 : handle_equals_computation(currentPosition, numbers, modes); currentPosition += 4; break;
        default : {
            printf("Something went wrong! Encountered unexpected opcode %i\n", opCode);
            printf("CURRENT POSITION: %i\n", currentPosition);
            return;
        }
    }

    run_operations(currentPosition, numbers);
    return;
}

int caluclate_modes_and_new_opcode(int opCode, int* modes)
{
    char opCodeString[100];
    char newOpCodeString[100];
    int counter = 0;
    int opCodeCounter = 1;
    int newOpCode;

    sprintf(opCodeString, "%i", opCode);

    if (strlen(opCodeString) > 2) {
        if(strlen(opCodeString) == 3) {
            modes[0] = ((int) opCodeString[0]) - 48;
            modes[1] = 0;
            newOpCodeString[0] = opCodeString[1];
            newOpCodeString[1] = opCodeString[2];
        }else if(strlen(opCodeString) == 4) {
            modes[0] = ((int) opCodeString[1]) - 48;
            modes[1] = ((int) opCodeString[0]) - 48;
            newOpCodeString[0] = opCodeString[2];
            newOpCodeString[1] = opCodeString[3];
        }else if(strlen(opCodeString) == 5) {
            modes[0] = ((int) opCodeString[2]) - 48;
            modes[1] = ((int) opCodeString[1]) - 48;
            modes[2] = ((int) opCodeString[0]) - 48;
            newOpCodeString[0] = opCodeString[3];
            newOpCodeString[1] = opCodeString[4];
        }

        newOpCodeString[2] = '\0';
        newOpCode = atoi(newOpCodeString);
    }else {
        newOpCode = opCode;
        modes[0] = 0;
        modes[1] = 0;
    }

    return newOpCode;
}

void handle_addition(int currentPosition, int* numbers, int* modes)
{
    int opcode = numbers[currentPosition];
    int firstNum = get_modal_value(numbers, currentPosition + 1, modes[0]);
    int secondNum = get_modal_value(numbers, currentPosition + 2, modes[1]);
    int finalPosition = numbers[currentPosition + 3];

    numbers[finalPosition] = firstNum + secondNum;
    return;
}

int get_modal_value(int* numbers, int position, int mode)
{
    int value; 

    switch(mode) {
        case 0 : value = numbers[numbers[position]]; break;
        case 1  : value = numbers[position]; break;
    }

    return value;
}

void handle_multiplication(int currentPosition, int* numbers, int* modes)
{
    int opcode = numbers[currentPosition];
    int firstNum = get_modal_value(numbers, currentPosition + 1, modes[0]);
    int secondNum = get_modal_value(numbers, currentPosition + 2, modes[1]);
    int finalPosition = numbers[currentPosition + 3];

    numbers[finalPosition] = firstNum * secondNum;
    return;
}

void handle_input(int currentPosition, int* numbers)
{
    int input;
    printf("Input the number to be saved to position %i: \n", numbers[currentPosition + 1]);
    scanf("%i", &input);
    printf("\n");

    numbers[numbers[currentPosition + 1]] = input;
    return;
}

void handle_output(int currentPosition, int* numbers, int* modes)
{
    int value = get_modal_value(numbers, currentPosition + 1, modes[0]);
    
    printf("The value at position %i is: %i\n", numbers[currentPosition + 1], value);
    return;
}

int handle_jump_if_true(int currentPosition, int* numbers, int* modes)
{
    int firstNum = get_modal_value(numbers, currentPosition + 1, modes[0]);
    int secondNum = get_modal_value(numbers, currentPosition + 2, modes[1]);

    if(firstNum != 0) {
        currentPosition = secondNum;
    }else {
        currentPosition += 3;
    }

    return currentPosition;
}

int handle_jump_if_false(int currentPosition, int* numbers, int* modes)
{
    int firstNum = get_modal_value(numbers, currentPosition + 1, modes[0]);
    int secondNum = get_modal_value(numbers, currentPosition + 2, modes[1]);

    if(firstNum == 0) {
        currentPosition = secondNum;
    }else {
        currentPosition += 3;
    }

    return currentPosition;
}

void handle_less_than_computation(int currentPosition, int* numbers, int* modes)
{
    int firstNum = get_modal_value(numbers, currentPosition + 1, modes[0]);
    int secondNum = get_modal_value(numbers, currentPosition + 2, modes[1]);
    int finalPosition = numbers[currentPosition + 3];

    if(firstNum < secondNum) {
        numbers[finalPosition] = 1;
    }else {
        numbers[finalPosition] = 0;
    }
}

void handle_equals_computation(int currentPosition, int* numbers, int* modes)
{
    int firstNum = get_modal_value(numbers, currentPosition + 1, modes[0]);
    int secondNum = get_modal_value(numbers, currentPosition + 2, modes[1]);
    int finalPosition = numbers[currentPosition + 3];

    if(firstNum == secondNum) {
        numbers[finalPosition] = 1;
    }else {
        numbers[finalPosition] = 0;
    }
}