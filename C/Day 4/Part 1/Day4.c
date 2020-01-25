#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RANGE_MIN 264793
#define RANGE_MAX 803935

int is_valid_password(int password);
int has_double_character(int password);
int is_always_increasing(int password);

int main()
{
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
    sprintf(passwordString, "%d", password);

    for(int i = 0; i < strlen(passwordString); i++) {
        for(int j = 0; j < strlen(passwordString) - i - 1; j++) {
            if(passwordString[j] == passwordString[j + 1]) {
                return 1;
            }
        }
    }

    return 0;
}

int is_always_increasing(int password)
{
    char passwordString[100];
    sprintf(passwordString, "%d", password);

    for(int i = 0; i < strlen(passwordString); i++) {
        for(int j = 0; j < strlen(passwordString) - i - 1; j++) {
            if(passwordString[j] > passwordString[j + 1] && passwordString[j] != passwordString[j + 1]) {
                return 0;
            }
        }
    }

    return 1;
}