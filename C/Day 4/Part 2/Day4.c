#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RANGE_MIN 264793
#define RANGE_MAX 803935

int is_valid_password(int password);
int has_double_character(int password);
int is_always_increasing(int password);
void remove_duplicates(int password, char* newPassword);

int main()
{
    printf("%i\n", is_valid_password(112233));
    printf("%i\n", is_valid_password(123444));
    printf("%i\n", is_valid_password(111122));

    int counter = 0;

    for(int i = RANGE_MIN; i < RANGE_MAX; i++) {
        if(is_valid_password(i) == 1) {
            ++counter;
        }
    }

    printf("%i\n", counter);
}

int is_valid_password(int password)
{
    if(has_double_character(password) == 0) {
        return 0;
    }

    return is_always_increasing(password) == 1;
}

int has_double_character(int password)
{
    char passwordString[100];
    char nextChar;
    int adjacentCounter;
    int counter;
    sprintf(passwordString, "%d", password);

    for(int i = 0; i < strlen(passwordString); i++) {
        adjacentCounter = 0;
        counter = i + 1;
        nextChar = passwordString[i + 1];

        while(counter <= strlen(passwordString) && nextChar == passwordString[i]) {
            ++counter;
            ++adjacentCounter;
            nextChar = passwordString[counter];
        }

        if(adjacentCounter == 1) {
            return 1;
        }

        if(adjacentCounter > 1) {
            i += adjacentCounter;
        }
    }

    return 0;
}

int is_always_increasing(int password)
{
    char passwordString[100];
    sprintf(passwordString, "%d", password);
    char* newPassword = malloc(strlen(passwordString) * sizeof(char));
    int counter = 0;

    remove_duplicates(password, newPassword);

    for(int i = 0; i < strlen(passwordString); i++) {
        for(int j = 0; j < strlen(passwordString) - i - 1; j++) {
            if(passwordString[j] > passwordString[j + 1] && passwordString[j] != passwordString[j + 1]) {
                return 0;
            }
        }
    }

    return 1;
}

void remove_duplicates(int password, char* newPassword)
{
    char passwordString[100];
    char nextChar;
    int adjacentCounter;
    int counter;
    int newCounter = 0;
    sprintf(passwordString, "%d", password);

    for(int i = 0; i < strlen(passwordString); i++) {
        adjacentCounter = 0;
        counter = i + 1;
        nextChar = passwordString[i + 1];

        while(counter <= strlen(passwordString) && nextChar == passwordString[i]) {
            ++counter;
            ++adjacentCounter;
            nextChar = passwordString[counter];
        }

        i += adjacentCounter;
        newPassword[newCounter] = passwordString[i];
        ++newCounter;
    }

    newPassword[newCounter] = '\0';
    return;
}