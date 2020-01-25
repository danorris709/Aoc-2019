#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_FILE "Day1.txt"
#define MAX_CHARACTERS 1000

int calculate_fuel(int weight);

int main()
{
    FILE *file = fopen(INPUT_FILE, "r");
    char str[MAX_CHARACTERS];
    int sum = 0;
    int currentWeight;
    int currentFuel;

    while (fgets(str, MAX_CHARACTERS, file) != NULL) {
        currentWeight = atoi(str);
        currentFuel = calculate_fuel(currentWeight);
        sum += currentFuel;
    }

    printf("Total fuel: %i", sum);
}

int calculate_fuel(int weight)
{
    int requiredFuel = floor(weight / 3) - 2;

    if(requiredFuel > 0) {
        int x = calculate_fuel(requiredFuel);

        if(x > 0) {
            requiredFuel += x;
        }
    }

    return requiredFuel;
}