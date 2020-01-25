#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <ctype.h>

#define FILE_PATH "Day6.txt"
#define MAX_CHARACTERS 2000
#define SIZE 2000

typedef struct Orbital {
    char identifier[100];
    int numberOfChildren;
    struct Orbital* parent;
    struct Orbital* children[200];
} Planet;

int calculate_direct_and_indirect_orbits();
int calculate_number_of_orbitals(FILE* inputFile);
void intialize_hash_table(Planet* planetHashTable, int orbitals);
void load_planets_to_table(FILE* inputFile, Planet* planetHashTable);
void split_orbital(char* orbitalInfo, char* planets[2]);
int hash_planet_identifier(Planet planet);
int compute_hash(char* key);
int calculate_direction_and_indirect_orbits_for_children(Planet planet, int counter);

int main()
{
    printf("%i\n", calculate_direct_and_indirect_orbits());
}

int calculate_direct_and_indirect_orbits()
{
    FILE *inputFile = fopen(FILE_PATH, "r");
    Planet *planetHashTable = malloc(SIZE * sizeof(Planet));

    intialize_hash_table(planetHashTable, SIZE);
    load_planets_to_table(inputFile, planetHashTable);

    return calculate_direction_and_indirect_orbits_for_children(planetHashTable[compute_hash("COM")], 0);
}

void intialize_hash_table(Planet *planetHashTable, int orbitals)
{
    for(int i = 0; i < orbitals; i++) {
        Planet planet;
        planet.numberOfChildren = 0;
        planet.parent = NULL;
        strcpy(planet.identifier, "");

        planetHashTable[i] = planet;
    }

    return;
}

void load_planets_to_table(FILE* inputFile, Planet* planetHashTable)
{
    char inputLine[MAX_CHARACTERS];
    char* planets[2];
    Planet *parent;
    Planet *child;
    int parentHash = 0;
    int childHash = 0;

    while(fgets(inputLine, MAX_CHARACTERS, inputFile) != NULL) {
        split_orbital(inputLine, planets);

        parentHash = compute_hash(planets[0]);
        childHash = compute_hash(planets[1]);
        parent = &planetHashTable[parentHash];
        child = &planetHashTable[childHash];

        strcpy(parent->identifier, planets[0]);
        strcpy(child->identifier, planets[1]);

        child->parent = parent;
        parent->children[parent->numberOfChildren] = child;
        parent->numberOfChildren += 1;
    }

    return;
}

void split_orbital(char* orbitalInfo, char* planets[2])
{
    char* token = strtok(orbitalInfo, ")");
    int counter = 0;
    char new[10];

    while(token != NULL) {
        planets[counter] = token;

        if(strlen(planets[counter]) > 0 && counter > 0) {
            planets[counter][strlen(planets[counter]) - 1] = '\0';
            planets[counter][strlen(planets[counter]) - 1] = '\0';
        }

        ++counter;
        token = strtok(NULL, ")");
    }

    return;
}

int hash_planet_identifier(Planet planet)
{
    return compute_hash(planet.identifier);
}

int compute_hash(char *key)
{
    int result = 0;

    while(*key) {
        if(isalpha(*key) && isupper(*key)) {
            result += (int) *key;
        }

        key++;
    }

    return (result % SIZE);
}